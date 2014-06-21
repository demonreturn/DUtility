#include "DLogger.h"

#include "DChannel.h"
#include "DLogMessage.h"
#include "DOSMemory.h"
#include "DOSProcess.h"

#include <assert.h>
#include <string>

CDLogger* CDLogger::Instance()
{
	static CDLogger s_logger;

	return &s_logger;
}

CDString GetLoggerToken()
{
	char buffer[256] = { 0 };

	D_OS::Sprintf( buffer, 256, "log_%s_%d", D_OS::GetProcessName(), D_OS::GetProcessID() );

	return CDString( buffer );
}

CDLogger::CDLogger()
	: m_logLevel( GetLoggerToken().c_str(), CDLogMessage::LOG_WARNING )
{

}

void CDLogger::Init( const CDString& strConfig )
{
	Reset();

	CDString::size_type pos = strConfig.find( ';' );

	if ( pos >= strConfig.size() )
	{
		return;
	}

	CDString level = strConfig.substr( 0, pos );
	SetLoggerLevel( level );

	CDString::size_type old = pos + 1;
	while ( ( pos = strConfig.find( ';', old)) < strConfig.size())
	{
		AttachChannel( strConfig.substr( old, pos - old));

		old = ++pos;
	}

	if ( old < strConfig.size() )
	{
		AttachChannel( strConfig.substr(old) );
	}
}

void CDLogger::Register( CDChannel* pchannel )
{
	assert( m_channels.find(pchannel->ChannelName()) == m_channels.end());

	m_channels.insert( Name2ChannelMap::value_type( pchannel->ChannelName(), pchannel));
}

int CDLogger::GetLoggerLevel() const
{
	return m_logLevel;
}

bool CDLogger::SetLoggerLevel( int level )
{
	if ( CDLogMessage::LOG_LEVEL_SIZE <= level ||
		CDLogMessage::LOG_FATAL > level )
	{
		return false;
	}

	m_logLevel = level;

	return true;
}

bool CDLogger::SetLoggerLevel( const CDString& levelName )
{
	int level = GetLevelName( levelName );

	if ( 0 == level )
	{
		return false;
	}

	m_logLevel = level;

	return true;
}

bool CDLogger::AttachChannel( const CDString & channelName )
{
	Name2ChannelMap::iterator itor = m_channels.find( channelName );
	if ( m_channels.end() != itor )
	{
		if ( channelName == itor->second->ChannelName())
		{
			return itor->second->Open();
		}
	}

	return false;
}

void CDLogger::DetachChannel( const CDString& channelName )
{
	Name2ChannelMap::iterator itor = m_channels.find( channelName );
	if ( m_channels.end() != itor )
	{
		if ( itor->second->ChannelName() == channelName )
		{
			itor->second->Close();
		}
	}
}

CDChannel* CDLogger::FindChannel( const CDString& channelName ) const
{
	Name2ChannelMap::const_iterator itor = m_channels.find( channelName );
	if ( m_channels.end() != itor )
	{
		return itor->second;
	}

	return NULL;
}

int CDLogger::GetLevelName( const CDString& levelName )
{
	for (int index = 0; index < CDLogMessage::LOG_LEVEL_SIZE; ++index)
	{
		if ( levelName == CDLogMessage::GetLevelName( index ))
		{
			return index;
		}
	}

	return 0;
}

CDString CDLogger::GetLevelName() const
{
	return CDLogMessage::GetLevelName( m_logLevel );
}

CDLogger::~CDLogger()
{
	Reset();

	m_channels.clear();
}

void CDLogger::Reset()
{
	m_logLevel = CDLogMessage::LOG_ERROR;

	for ( auto itor = m_channels.begin(); itor != m_channels.end(); ++itor )
	{
		itor->second->Close();
	}
}

void CDLogger::LogMsg( const CDLogMessage& msg )
{
	if ( m_logLevel >= msg.GetLevel() )
	{
		Name2ChannelMap::iterator itor = m_channels.begin();
		for (; itor != m_channels.end(); ++itor )
		{
			if ( itor->second->IsOpend() )
			{
				itor->second->Log( msg );
			}
		}
	}
}

CDLogger::ChannelNameVec CDLogger::GetAllChannelNames() const
{
	ChannelNameVec namses;
	namses.reserve( m_channels.size() );

	for ( Name2ChannelMap::const_iterator itor = m_channels.cbegin();
		itor != m_channels.cend(); ++itor )
	{
		namses.push_back( itor->first );
	}

	return namses;
}

CDLogger::ChannelNameVec CDLogger::GetOpendChannelNames() const
{
	ChannelNameVec namses;

	for ( Name2ChannelMap::const_iterator itor = m_channels.cbegin();
		itor != m_channels.cend(); ++itor )
	{
		if ( itor->second->IsOpend() )
		{
			namses.push_back( itor->first );
		}
	}

	return namses;
}

