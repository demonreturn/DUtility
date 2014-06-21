
#ifndef _D_FILE_CHANNEL_H_
#define _D_FILE_CHANNEL_H_

#include "DBase.h"
#include "DChannel.h"

class CDFileChannel : public CDChannel
{
public:
	CDFileChannel();

	virtual void Log( const CDLogMessage& msg );

	virtual const char* ChannelName() const;
};


#endif	// _D_FILE_CHANNEL_H_
