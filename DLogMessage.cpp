#include "DLogMessage.h"
#include "DOSProcess.h"
#include "DOSThread.h"

const char* CDLogMessage::LOG_LEVEL_NAME[LOG_LEVEL_SIZE] = 
{
	"",
	"Fatal",
	"Critical",
	"Error",
	"Warning",
	"Notice",
	"Info",
	"Debug",
	"Trace"
};

CDLogMessage::CDLogMessage( 
	const CDString& src,
	const CDString& text,
	ELogLevel level,
	const char* pfile,
	const char* fun,
	int line )
	: m_source( src )
	, m_text( text )
	, m_level( level )
	, m_pid( 0 )
	, m_threadID( 0 )
	, m_line( line )
	, m_file( pfile )
	, m_function( fun )
{
	m_pid = D_OS::GetProcessID();
	m_threadID = D_OS::GetSelfThreadID();
}

CDLogMessage::CDLogMessage( const CDLogMessage& msg )
	: m_source( msg.m_source )
	, m_text( msg.m_text )
	, m_level( msg.m_level )
	, m_pid( msg.m_pid )
	, m_threadID( msg.m_threadID )
	, m_line( msg.m_line )
	, m_function( msg.m_function )
	, m_time( msg.m_time )
{

}

CDLogMessage& CDLogMessage::operator=( const CDLogMessage& msg )
{
	if (&msg != this )
	{
		m_source = msg.m_source;
		m_text = msg.m_text;
		m_level = msg.m_level;
		m_time = msg.m_time;
		m_pid = msg.m_pid;
		m_threadID = msg.m_threadID;
		m_line = msg.m_line;
		m_function = msg.m_function;
	}

	return *this;
}

bool CDLogMessage::operator==( const CDLogMessage& msg )
{
	if ( NULL != m_file 
		&& m_file == msg.GetSourceFile())
	{
		return true;
	}

	return false;
}

const char* CDLogMessage::GetLevelName() const
{
	return GetLevelName( m_level );
}

const char* CDLogMessage::GetLevelName( int level )
{
	if ( level < sizeof( LOG_LEVEL_NAME) / sizeof( LOG_LEVEL_NAME[0])
		&& level > 0 )
	{
		return LOG_LEVEL_NAME[level];
	}

	return LOG_LEVEL_NAME[0];
}




