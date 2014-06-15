
#ifndef _D_FILE_OPERATION_H_
#define _D_FILE_OPERATION_H_

#include "DBase.h"

namespace D_OS
{
	/*
	 * ���ļ�
	 */
	extern DUTILITY_API DHANDLE OpenFile(
		const char* pFullPath,
		DWORD dwFlags = O_RDONLY ,
		DWORD dwMode = D_DEFAULT_FILE_MODE,
		DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL ,
		LPSECURITY_ATTRIBUTES pSapSecurity = NULL );

	/*
	 * ��ȡ�ļ�
	 */
	extern DUTILITY_API int ReadFile(
		DHANDLE fileHandle,
		LPVOID pBuffer,
		DWORD dwReadSize,
		LPDWORD dwHaveRead );

	/*
	 * д���ļ�
	 */
	extern DUTILITY_API int WriteFile(
		DHANDLE handle, 
		const LPVOID pBuffer,
		DWORD dwWriteSize,
		LPDWORD dwHaveWrite );

	/*
	 * �ļ�ָ�붨λ
	 */
	extern DUTILITY_API int SeekFile(
		DHANDLE handle,
		D_OFF_T lDistance,
		DWORD nMoveMethod );

	/*
	 * �ļ�ͬ��������
	 */
	extern DUTILITY_API int FlushFile(
		DHANDLE handle );

	/*
	 * �ر��ļ�
	 */
	extern DUTILITY_API int CloseFile(
		DHANDLE handle );

	/*
	 * ȡ�ļ���ǰλ�� ���ļ���ʼ��λ��
	 */
	extern DUTILITY_API D_OFF_T GetFilePosition(
		DHANDLE handle );

	/*
	 * ȡ�ļ��Ĵ�С ����ʱ�� �޸�ʱ�� ����
	 */
	extern DUTILITY_API int GetFileAddribute(
		const char* pFullPath,
		File_Attributes& fileAttri );

	/*
	 * �ļ�����, ������, Ĭ������ȡʧ��ʱ��������,������
	 * û�ж�Ȩ��ʱ����ʧ��
	 */
	extern DUTILITY_API int ReadLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY );

	/*
	 * �ļ�д������ռ
	 */
	extern DUTILITY_API int WriteLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_EXCLUSIVE_LOCK );

	/*
	 * ����
	 */
	extern DUTILITY_API int UnLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize );

	/*
	 * �ļ��Ƿ����
	 */
	extern DUTILITY_API bool IsFileExist( const char* pFullPath );

	/*
	 * ɾ���ļ�, ɾ����Ŀ¼, ֻ���ļ����ܱ�ɾ, Ȩ�޲���
	 */
	extern DUTILITY_API bool DeleteFile( const char* pFullPath );

	/*
	*	ȡPath����·���Ĵ���ʣ��ռ��ֽ�
	* [����]
	* pPath			:[IN]  �ļ�·�� [ "C:\\", "E:\\" ,"/root/test.txt" , "/" ]
	*/
	extern DUTILITY_API LONGLONG GetDiskFreeSpace( const char* pPath );

	/*
	 * �ض��ļ�, �����ڽ��ļ���С
	 */
	extern DUTILITY_API int TruncateFile( 
		DHANDLE handle,
		LONGLONG llSize );

	/*
	 * �����ļ�, ��pSourceFile��pDestFile, ��ѡ���Ƿ񸲸�DestFile
	 */
	extern DUTILITY_API int CopyFile(
		const char* pSrcFile,
		const char* pDstFile,
		bool bFailIfExist = true );
}

#endif	// _D_FILE_OPERATION_H_