
#ifndef _D_SOCKET_H_
#define _D_SOCKET_H_

#include "DBase.h"

class  CDInetAddress;

namespace D_OS
{
	/*
	 * һ�������Զ�����errno������errno�Ĺ�����
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
	 * ��һ��4�ֽڵ�DWORDֵת���ɷ���IPV4�淶�ĵ�ַ
	 */
	extern DUTILITY_API CDString IPDigitalToString( DWORD dwIP );

	/*
	 * ��һ������IPV4�淶�ĵ�ַת����4�ֽڵ�DWORDֵ
	 */
	extern DUTILITY_API DWORD IPStringToDigital( const char* pstrIP );

	/*
	 * ����socket��I/Oģʽ
	 */
	extern DUTILITY_API int SetIOCtrl(
		DSOCKET handle,
		int flag,
		void* pparam );

	/*
	 * ��ȡһ���������������󶨵ı��ص�ַ
	 */
	extern DUTILITY_API int GetLocalAddress(
		DSOCKET handle,
		CDInetAddress& localAddress );

	/*
	 * ��ȡһ���������������󶨵ĶԶ˵�ַ
	 */
	extern DUTILITY_API int GetRemoteAddress(
		DSOCKET handle,
		CDInetAddress& remoteAddress );

	/*
	 * ����socket������
	 */
	extern DUTILITY_API int SetSocketOption(
		DSOCKET handle,
		int iLevel,
		int iOption,
		const void* pOption,
		int iOptionLen );

	/*
	 * ��ȡsocket������
	 */
	extern DUTILITY_API int GetSocketOption(
		DSOCKET handle,
		int iLevel,
		int iOption,
		void* pOptionValue,
		int* pOptionLen );

	/*
	 * �ر�һ��socket
	 */
	extern DUTILITY_API int CloseSocket(DSOCKET handle);

	/*
	 * ��������
	 */
	extern DUTILITY_API int Send(
		DHANDLE handle,
		const char* pData,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * ��������
	 */
	extern DUTILITY_API int SendV(
		DHANDLE handle,
		const iovec pszIov[],
		DWORD dwCount );

	/* 
	 * ��ȡ����
	 */
	extern DUTILITY_API int Recv(
		DHANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		int iFlag = 0 );

	/*
	 * ��ȡ����
	 */
	extern DUTILITY_API int RecvV(
		DHANDLE handle,
		iovec szIov[],
		DWORD dwCount );

	/*
	 * ��������, ������UDP
	 */
	extern DUTILITY_API int SendUdp(
		DHANDLE handle,
		const char* pData,
		DWORD dwLength,
		const CDInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * ��������, ������UDP
	 */
	extern DUTILITY_API int SendUdpV(
		DHANDLE handle,
		const iovec pszIov[],
		DWORD dwCount,
		const CDInetAddress& peerAddress );

	/*
	 * ��ȡ����, ������UDP
	 */
	extern DUTILITY_API int RedvUDP(
		DHANDLE handle,
		char* pBuffer,
		DWORD dwLength,
		CDInetAddress& peerAddress,
		int iFlag = 0 );

	/*
	 * Ϊһ��socket�����һ�����ص�ַ
	 */
	extern DUTILITY_API int Bind(
		DHANDLE handle,
		const CDInetAddress& localAddreess );

	/*
	 * ����ĳ��socket��ĳЩ����
	 */
	extern DUTILITY_API int ShutDown(
		DHANDLE handle,
		int iFlag );

	/*
	 * ����
	 */
	extern DUTILITY_API int Connect(
		DHANDLE handle,
		const CDInetAddress& peerAddress );

	/*
	 * ����
	 */
	extern DUTILITY_API int Listen(
		DHANDLE handle,
		const CDInetAddress& peerAddress );

	/*
	 * ����
	 */
	extern DUTILITY_API DHANDLE Accept(
		DHANDLE handle,
		CDInetAddress& peerAddress );
}

#endif // _D_SOCKET_H_
