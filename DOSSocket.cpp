
#include "DOSSocket.h"

#include "DInetAddress.h"

D_OS::CDSocketErrorAutoSave::CDSocketErrorAutoSave()
	: m_iLastError( errno )
{

}

D_OS::CDSocketErrorAutoSave::~CDSocketErrorAutoSave()
{
	errno = m_iLastError;
}

int D_OS::CDSocketErrorAutoSave::GetLastError()
{
	return m_iLastError;
}

extern DUTILITY_API CDString D_OS::IPDigitalToString( DWORD dwIP )
{
#ifdef D_WIN32
	struct in_addr addrIn;
	addrIn.s_addr = dwIP;

	const char* pAddr = ::inet_ntoa( addrIn );
#elif defined( D_LINUX)		// linux  实现
	char szbuff[INET_ADDRSTRLEN];
	const char* pAddr = ::inet_ntop(
		AF_INET,
		&dwIP,
		szbuff,
		sizeof(szbuff) );
#endif

	return CDString(pAddr);
}

extern DUTILITY_API DWORD D_OS::IPStringToDigital( const char* pstrIP )
{
	if ( NULL == pstrIP )
	{
		return INADDR_NONE;
	}

	DWORD dwIP = INADDR_ANY;
#ifdef D_WIN32
	dwIP = ::inet_addr( pstrIP );
#elif defined( D_LINUX)		// linux  实现
	::inet_pton(
		AF_INET,
		pstrIP,
		&dwIP );
#endif

	return dwIP;
}

extern DUTILITY_API int D_OS::SetIOCtrl( DSOCKET handle, int flag, void* pparam )
{
#ifdef D_WIN32
	return ::ioctlsocket(
		handle,
		flag,
		reinterpret_cast<DWORD*>(pparam) );
#elif defined( D_LINUX)		// linux  实现
	return ::ioctl(
		handle,
		flag,
		pparam );
#endif
}

extern DUTILITY_API int D_OS::GetLocalAddress( 
	DSOCKET handle,
	CDInetAddress& localAddress )
{
	int iSize = (int)localAddress.GetSize();

#ifdef D_WIN32
	int iRet = ::getsockname(
		handle,
		reinterpret_cast<sockaddr*>(
		const_cast<D_SOCKADDR*>(localAddress.GetRawAddress()) ),
		&iSize );
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::getsockname(
		handle,
		reinterpret_cast<sockaddr*>(
		const_cast<D_SOCKADDR*>(localAddress.GetRawAddress()) ),
		reinterpret_cast<socklen_t*>( &iSize ) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef D_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;

}

extern DUTILITY_API int D_OS::GetRemoteAddress( 
	DSOCKET handle, 
	CDInetAddress& remoteAddress )
{
	int iSize = (int)remoteAddress.GetSize();

#ifdef D_WIN32
	int iRet = ::getpeername(
		handle,
		reinterpret_cast<sockaddr*>( const_cast<D_SOCKADDR*>(remoteAddress.GetRawAddress())),
		&iSize );
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::getpeername(
		handle,
		reinterpret_cast<sockaddr*>( const_cast<D_SOCKADDR*>(remoteAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>(&iSize) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef D_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern DUTILITY_API int D_OS::SetSocketOption( 
	DSOCKET handle,
	int iLevel,
	int iOption,
	const void* pOption,
	int iOptionLen )
{
#ifdef D_WIN32
	int iRet = ::setsockopt(
		handle,
		iLevel,
		iOption,
		static_cast<const char*>(pOption),
		iOptionLen );
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::setsockopt(
		handle,
		iLevel,
		iOption,
		pOption,
		iOptionLen );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef D_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern DUTILITY_API int D_OS::GetSocketOption( 
	DSOCKET handle,
	int iLevel,
	int iOption,
	void* pOptionValue,
	int* pOptionLen )
{
#ifdef D_WIN32
	int iRet = ::getsockopt(
		handle,
		iLevel,
		iOption,
		static_cast<char*>(pOptionValue),
		pOptionLen );
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::getsockopt(
		handle,
		iLevel,
		iOption,
		pOptionValue,
		reinterpret_cast<socklen_t*>(pOptionLen) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef D_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern DUTILITY_API int D_OS::CloseSocket( DSOCKET handle )
{
	int iRet = 0;
#ifdef D_WIN32
	iRet = ::closesocket( handle );
#elif defined( D_LINUX)		// linux  实现
	iRet = ::close( handle );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef D_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern DUTILITY_API int D_OS::Send( 
	DHANDLE handle,
	const char* pData,
	DWORD dwLength,
	int iFlag /*= 0 */ )
{
	int iRet = ::send(
		(DSOCKET)handle,
		pData,
		dwLength,
		iFlag );
#ifdef D_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet &&
		errno == EAGAIN )
	{
		errno = EWOULDBLOCK;
	}
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::SendV( 
	DHANDLE handle,
	const iovec pszIov[],
	DWORD dwCount )
{
	int iRet = 0;
#ifdef D_WIN32
	DWORD dwBytesSend = 0;
	iRet = ::WSASend(
		(DSOCKET)handle,
		(WSABUF*)pszIov,
		dwCount,
		&dwBytesSend,
		0,
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesSend;
	}

#elif defined( D_LINUX)		// linux  实现
	iRet = ::writev(
		handle,
		pszIov,
		dwCount );
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::Recv( 
	DHANDLE handle,
	char* pBuffer,
	DWORD dwLength,
	int iFlag /*= 0 */ )
{
	if ( NULL == pBuffer )
	{
		return SOCKET_ERROR;
	}

	int iRet = ::recv(
		(DSOCKET)handle,
		pBuffer,
		dwLength,
		iFlag );
#ifdef D_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet &&
		errno == EAGAIN )
	{
		errno = EWOULDBLOCK;
	}
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::RecvV( 
	DHANDLE handle,
	iovec szIov[],
	DWORD dwCount )
{
	if ( NULL == szIov )
	{
		return SOCKET_ERROR;
	}

	int iRet = 0;
#ifdef D_WIN32
	DWORD dwBytesRecv = 0;
	DWORD dwFlag = 0;

	iRet = ::WSARecv(
		(DSOCKET)handle,
		(WSABUF*) szIov,
		dwCount,
		&dwBytesRecv,
		&dwFlag,
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesRecv;
	}
#elif defined( D_LINUX)		// linux  实现
	iRet = ::readv(
		handle,
		szIov,
		dwCount );
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::Bind( 
	DHANDLE handle,
	const CDInetAddress& localAddreess )
{
#ifdef D_WIN32
	int iRet = ::bind(
		(DSOCKET)handle,
		reinterpret_cast<const sockaddr*>(localAddreess.GetRawAddress()),
		localAddreess.GetSize() );
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::bind(
		(DSOCKET)handle,
		reinterpret_cast<const sockaddr*>(localAddreess.GetRawAddress()),
		static_cast<socklen_t>(localAddreess.GetSize() ));
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::ShutDown( DHANDLE handle, int iFlag )
{
	int iRet = ::shutdown(
		(DSOCKET)handle,
		iFlag );

#ifdef D_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::SendUdp( 
	DHANDLE handle,
	const char* pData,
	DWORD dwLength,
	const CDInetAddress& peerAddress,
	int iFlag /*= 0 */ )
{
#ifdef D_WIN32
	int iRet = ::sendto(
		(DSOCKET)handle,
		pData,
		dwLength,
		iFlag,
		reinterpret_cast<const sockaddr*>( peerAddress.GetRawAddress()),
		peerAddress.GetSize() );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::sendto(
		(DSOCKET)handle,
		pData,
		dwLength,
		iFlag,
		reinterpret_cast<const sockaddr*>( peerAddress.GetRawAddress()),
		static_cast<socklen_t>(peerAddress.GetSize()) );
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::SendUdpV( 
	DHANDLE handle,
	const iovec pszIov[],
	DWORD dwCount,
	const CDInetAddress& peerAddress )
{
	int iRet = 0;
#ifdef D_WIN32
	DWORD dwBytesSend = 0;
	iRet = ::WSASendTo(
		(DSOCKET)handle,
		(WSABUF*)pszIov,
		dwCount,
		&dwBytesSend,
		0,
		reinterpret_cast<const sockaddr*>(peerAddress.GetRawAddress()),
		peerAddress.GetSize(),
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesSend;
	}
#elif defined( D_LINUX)		// linux  实现
	msghdr msgData;
	msgData.msg_iov = (iovec*)pszIov;
	msgData.msg_iovlen = dwCount;	
	msgData.msg_name = (struct sockaddr*)peerAddress.GetRawAddress();
	msgData.msg_namelen = peerAddress.GetSize();
	msgData.msg_control = 0;
	msgData.msg_controllen = 0;
	msgData.msg_flags = 0;

	iResult = ::sendmsg(
		Handle, 
		&msgData, 
		0 );
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::RedvUDP( 
	DHANDLE handle,
	char* pBuffer, 
	DWORD dwLength,
	CDInetAddress& peerAddress,
	int iFlag /*= 0 */ )
{
	int iSize = (int)peerAddress.GetSize();

#ifdef D_WIN32
	int iRet = ::recvfrom(
		(DSOCKET)handle,
		pBuffer,
		dwLength,
		iFlag,
		reinterpret_cast<sockaddr*>( const_cast<D_SOCKADDR*>(peerAddress.GetRawAddress())),
		&iSize );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::recvfrom(
		(DSOCKET)handle,
		pBuffer,
		dwLength,
		iFlag,
		reinterpret_cast<sockaddr*>( const_cast<D_SOCKADDR*>(peerAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>( &iSize ) );
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::Connect( 
	DHANDLE handle,
	const CDInetAddress& peerAddress )
{
	int iRet = ::connect(
		(DSOCKET)handle,
		reinterpret_cast<const struct sockaddr*>( peerAddress.GetRawAddress()),
		(int)peerAddress.GetSize() );
#ifdef D_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet )
	{
		if ( EINPROGRESS == errno )
		{
			errno = EWOULDBLOCK;
		}
	}
#endif

	return iRet;
}

extern DUTILITY_API int D_OS::Listen( 
	DHANDLE handle,
	const CDInetAddress& peerAddress )
{
	int iRet = ::listen(
		(DSOCKET)handle,
		SOMAXCONN );

#ifdef D_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( D_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet )
	{
		if ( EINPROGRESS == errno )
		{
			errno = EWOULDBLOCK;
		}
	}
#endif

	return iRet;
}

extern DUTILITY_API DHANDLE D_OS::Accept( 
	DHANDLE handle,
	CDInetAddress& peerAddress )
{
	int iSize = peerAddress.GetSize();
#ifdef D_WIN32
	handle = (DHANDLE)::accept(
		(DSOCKET)handle,
		reinterpret_cast<sockaddr*>(const_cast<D_SOCKADDR*>(peerAddress.GetRawAddress())),
		&iSize );

	if ( D_INVALID_HANDLE == handle )
	{
		errno = ::WSAGetLastError();
	}

#elif defined( D_LINUX)		// linux  实现
	handle = (DHANDLE)::accept(
		(DSOCKET)handle,
		reinterpret_cast<sockaddr*>(const_cast<D_SOCKADDR*>(peerAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>( &iSize ) );

	if ( D_INVALID_HANDLE == handle &&
		EINPROGRESS == errno )
	{
		errno == EWOULDBLOCK;
	}
#endif

	return handle;
}
