#include "DInetAddress.h"
#include "DOSMemory.h"
#include "DOSSocket.h"

#include <string.h>

// 最大端口 65536
const WORD MAX_PORT_NUM = 0Xffff;
const DWORD MAX_IP_AND_PORT_LENGTH = 256;

CDInetAddress::CDInetAddress()
{
	Set( NULL, 0 );
}

CDInetAddress::CDInetAddress( const char* phostnameAndPort )
{
	Set( phostnameAndPort );
}

CDInetAddress::CDInetAddress( const char* phostname, WORD port )
{
	Set( phostname, port );
}

CDInetAddress::~CDInetAddress()
{
}

DResult CDInetAddress::Set( const char* phostname, WORD port )
{
	::memset( &m_sockAddr, 0, sizeof( m_sockAddr) );

	m_sockAddr.sin_family = AF_INET;
	if ( NULL == phostname )
	{
		return D_OK;
	}

	m_sockAddr.sin_port = ::htons( port );

	return SetIP( phostname );
}

DResult CDInetAddress::Set( const char* phostnameAndPort )
{
	if ( NULL == phostnameAndPort )
	{
		return D_ERROR_NULL_POINTER;
	}

	DWORD dwLength = D_OS::Strlen( phostnameAndPort, MAX_IP_AND_PORT_LENGTH );

	WORD wPort = 0;

	// 查找":", ":"之前都算是ip
	char* szFind = const_cast<char*>( ::strchr(phostnameAndPort, ':'));
	if ( NULL == szFind )
	{
		szFind = const_cast<char*>( phostnameAndPort ) + dwLength;
		wPort = 0;

		return D_ERROR_FAILURE;
	}
	else
	{
		// ":"之后的都算是端口
		if ( MAX_PORT_NUM > static_cast<WORD>( ::atoi(szFind+1))
			&& (0 < static_cast<WORD>( ::atoi(szFind+1) )) )
		{
			wPort = static_cast<WORD>(::atoi(szFind + 1));
		}
		else
		{
			return D_ERROR_FAILURE;
		}
	}

	char szBuf[MAX_IP_AND_PORT_LENGTH] = { 0 };
	int iAddrLen = szFind - phostnameAndPort;


	return 0;
}

DResult CDInetAddress::Set( DWORD dwIP )
{
	return 0;
}

DResult CDInetAddress::SetIP( const char* pszIP )
{
	DWORD dwIP = D_OS::IPStringToDigital( pszIP );

	if ( INADDR_NONE != dwIP )
	{
		return SetIP( dwIP, true );
	}

	return D_ERROR_FAILURE;
}

DResult CDInetAddress::SetIP( DWORD dwIP, bool bnetworkOrder /*= false */ )
{
	if ( false == bnetworkOrder )
	{
		m_sockAddr.sin_addr.s_addr = ::htonl( dwIP );
	}
	else
	{
		m_sockAddr.sin_addr.s_addr = dwIP;
	}

	return 0;
}

DResult CDInetAddress::SetPort( WORD port )
{
	m_sockAddr.sin_port = port;

	return 0;
}

WORD CDInetAddress::GetPort() const
{
	return ::ntohs( m_sockAddr.sin_port );
}

CDString CDInetAddress::GetStrIP() const
{
	return D_OS::IPDigitalToString( m_sockAddr.sin_addr.s_addr );
}

DWORD CDInetAddress::GetSize() const
{
	return sizeof( D_SOCKADDR );
}

const D_SOCKADDR* CDInetAddress::GetRawAddress() const
{
	return &m_sockAddr;
}
