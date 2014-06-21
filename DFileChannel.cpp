#include "DFileChannel.h"

#include "DTraceFormater.h"
#include "DLocalDateTime.h"
#include "DLogMessage.h"
#include "DTraceDefine.h"


CDFileChannel::CDFileChannel()
{
}

void CDFileChannel::Log( const CDLogMessage& msg )
{
	if ( !IsOpend() )
	{
		return;
	}

	char pformatBuffer[D_TRACE_AVAILABLE_DATA_LEN] = { 0 };
	CDTraceFormator traceFormater( pformatBuffer, D_TRACE_AVAILABLE_DATA_LEN );
	traceFormater
		<< "["
		<< CDLocalDateTime( msg.GetTime()).ToString()
		<< "pid= " << msg.GetPID()
		<< "tdi= " << msg.GetThreadID()
		<< "] <"
		<< msg.GetLevelName()
		<< "> ["
		<< msg.GetSource() << "]" << msg.GetFunction() << "(), " << msg.GetText();


}

const char* CDFileChannel::ChannelName() const
{
	return "file";
}

static CDFileChannel s_fileChannel;
