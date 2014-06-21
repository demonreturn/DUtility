
#ifndef _D_CHANNEL_H_
#define _D_CHANNEL_H_

#include "DBase.h"
#include "DFormatter.h"

class CDLogMessage;

class CDChannel
{
public:
	virtual ~CDChannel(){}

	virtual void Log( const CDLogMessage& msg ) = 0;

	virtual const char* ChannelName() const = 0;

	virtual bool Open()
	{
		m_bOpen = true;

		return true;
	}

	virtual void Close()
	{
		m_bOpen = false;
	}

	CDChannel()
		: m_formatter( NULL )
		, m_bOpen( false )
	{

	}

	void SetFormatter( TFormatterPtr pformatter )
	{
		m_formatter = pformatter;
	}

	bool IsOpend() const
	{
		return m_bOpen;
	}

private:
	CDChannel( const CDChannel& );
	CDChannel& operator = ( const CDChannel& );

	TFormatterPtr				m_formatter;
	bool						m_bOpen;
};

#endif	// _D_CHANNEL_H_