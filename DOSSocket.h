
#ifndef _D_SOCKET_H_
#define _D_SOCKET_H_

#include "DBase.h"

class  CDInetAddress;

namespace D_OS
{
	/*
	 * 一个用于自动保存errno和重置errno的工具类
	 */

	class CDSocketErrorAutoSave
	{
	public: 
		CDSocketErrorAutoSave();
		~CDSocketErrorAutoSave();

	public:
		int GetLastError();

	private:
		int						m_iLastError;
	};
	
	/*
	 * 把一个4字节的DWORD值转换成符合IPV4规范的地址
	 */
	extern DUTILITY_API CDString IPDigitalToString( DWORD dwIP );

	/*
	 * 把一个符合IPV4规范的地址转换成4字节的DWORD值
	 */
	extern DUTILITY_API DWORD IPStringToDigital( const char* pstrIP );

	/*
	 * 设置socket的I/O模式
	 */
	extern DUTILITY_API int SetIOCtrl(
		DSOCKET handle,
		int flag,
		void* pparam );

	/*
	 * 获取一个已有连接中所绑定的本地地址
	 */
	extern DUTILITY_API int GetLocalAddress(
		DSOCKET handle,
		CDInetAddress& localAddress );

	/*
	 * 获取一个已有连接中所绑定的对端地址
	 */
	extern DUTILITY_API int GetRemoteAddress(
		DSOCKET handle,
		CDInetAddress& remoteAddress );

	/*
	 * 设置socket的属性
	 */
	extern DUTILITY_API int SetSocketOption(
		DSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );

	/*
	 * 获取socket的属性
	 */
	extern DUTILITY_API int GetSocketOption(
		DSOCKET handle,
		int iLevel,
		int iOption,
		void* pOptionValue,
		int* pOptionLen );

	/*
	 * 关闭一个socket
	 */
	extern DUTILITY_API int CloseSocket(DSOCKET handle);

	/*
	 * 发送数据
	 */
	extern DUTILITY_API int Send(
		DHANDLE handle,
		const char* pData,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * 发送数据
	 */
	extern DUTILITY_API int SendV(
		DHANDLE handle,
		const iovec pszIov[],
		DWORD dwCount );

	/* 
	 * 收取数据
	 */
	extern DUTILITY_API int Recv(
		DHANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * 收取数据
	 */
	extern DUTILITY_API int RecvV(
		DHANDLE handle,
		iovec szIov[],
		DWORD dwCount );

	/*
	 * 发送数据, 仅用于UDP
	 */
	extern DUTILITY_API int SendUdp(
		DHANDLE handle,
		const char* pData,
		DWORD dwLength,
		const CDInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * 发送数据, 仅用于UDP
	 */
	extern DUTILITY_API int SendUdpV(
		DHANDLE handle,
		const iovec pszIov[],
		DWORD dwCount,
		const CDInetAddress& peerAddress );

	/*
	 * 收取数据, 仅用于UDP
	 */
	extern DUTILITY_API int RedvUDP(
		DHANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		CDInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * 为一个socket句柄绑定一个本地地址
	 */
	extern DUTILITY_API int Bind(
		DHANDLE handle,
		const CDInetAddress& localAddreess );

	/*
	 * 屏蔽某个socket的某些功能
	 */
	extern DUTILITY_API int ShutDown(
		DHANDLE handle,
		int iFlag );

	/*
	 * 连接
	 */
	extern DUTILITY_API int Connect(
		DHANDLE handle,
		const CDInetAddress& peerAddress );

	/*
	 * 监听
	 */
	extern DUTILITY_API int Listen(
		DHANDLE handle,
		const CDInetAddress& peerAddress );

	/*
	 * 监听
	 */
	extern DUTILITY_API DHANDLE Accept(
		DHANDLE handle,
		CDInetAddress& peerAddress );
}

#endif // _D_SOCKET_H_
