
#ifndef _D_LOGGER_H_
#define _D_LOGGER_H_

#include "DBase.h"

#include "DShareVariantT.h"

class CDChannel;
class CDLogMessage;

#include <map>

class CDLogger
{
public:
	class CAutoRegister
	{
	public:
		CAutoRegister( CDChannel* pchannel )
		{
			CDLogger::Instance()->Register( pchannel );
		}
	};

public:
	typedef std::vector<CDString>		ChannelNameVec;

	static CDLogger* Instance();

	void Init( const CDString& strConfig );

	void Register( CDChannel* pchannel );

	int GetLoggerLevel() const;

	bool SetLoggerLevel( int level );

	bool SetLoggerLevel( const CDString& levelName );

	bool AttachChannel( const CDString& channelName );

	void DetachChannel( const CDString& channelName );

	CDChannel* FindChannel( const CDString& channelName ) const;

	void LogMsg( const CDLogMessage& msg );

	CDString GetLevelName() const;

	ChannelNameVec GetAllChannelNames() const;

	ChannelNameVec GetOpendChannelNames() const;

	~CDLogger();

private:

	void Reset();

	static int GetLevelName( const CDString& levelName );

	CDLogger();

	CDLogger( const CDLogger& );

	typedef std::map<CDString,CDChannel*>	Name2ChannelMap;

	Name2ChannelMap				m_channels;

	typedef CDShareVariantT<int>	LOG_LEVEL;
	LOG_LEVEL					m_logLevel;
};

#define D_CHANNEL_REGISTER( channel )\
	static CDLogger::CAutoRegister autoRegister(channel);

#define D_LOG_DEFINED(source, level, data )\
	do																								\
{																								\
	if ( CDLogger::Instance()->GetLoggerLevel() >= level )										\
{																							\
	char pszFormatBuf[D_TRACE_AVAILABLE_DATA_LEN] = {0};									\
	CDTraceFormator traceFormator( pszFormatBuf, D_TRACE_AVAILABLE_DATA_LEN );				\
	traceFormator << data;																	\
	CDLogMessage msg( source, pszFormatBuf, level, __FILE__, __FUNCTION__, __LINE__ );		\
	CDLogger::Instance()->LogMsg( msg );														\
}																							\
} while ( 0 );

#define D_LOG_FATAL_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_FATAL, data)
#define D_LOG_CRITICAL_WITH_SOURCE(source, data)		D_LOG_DEFINED(source, CDLogMessage::LOG_CRITICAL, data)
#define D_LOG_ERROR_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_ERROR, data)
#define D_LOG_WARNING_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_WARNING, data)
#define D_LOG_NOTICE_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_NOTICE, data)
#define D_LOG_INFO_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_INFORMATION, data)
#define D_LOG_DEBUG_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_DEBUG, data)
#define D_LOG_TRACE_WITH_SOURCE(source, data)			D_LOG_DEFINED(source, CDLogMessage::LOG_TRACE, data)




#endif // _D_LOGGER_H_

