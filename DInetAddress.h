

#ifndef _D_INET_ADDRESS_H_
#define _D_INET_ADDRESS_H_

#include "DBase.h"

class DUTILITY_API CDInetAddress
{
public:
	CDInetAddress();

	CDInetAddress( const char* phostnameAndPort );

	CDInetAddress( 
		const char* phostname,
		WORD port );

	~CDInetAddress();

public:
	DResult Set( const char* phostname, WORD port );

	// 127.0.0.1:1224
	DResult Set( const char* phostnameAndPort );

	DResult Set( DWORD dwIP );

	DResult SetPort( WORD port );

	WORD GetPort() const;

	CDString GetStrIP() const;

	DWORD GetSize() const;

	const D_SOCKADDR* GetRawAddress() const;

public:
	bool operator == ( const CDInetAddress& other ) const;

	bool operator <  ( const CDInetAddress& other ) const;

private:
	DResult SetIP( const char* pszIP );

	DResult SetIP( DWORD dwIP, bool bnetworkOrder = false );

private:
	D_SOCKADDR					m_sockAddr;
};


#endif // _D_INET_ADDRESS_H_
