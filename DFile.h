
#ifndef _D_FILE_OPERATION_H_
#define _D_FILE_OPERATION_H_

#include "DBase.h"

namespace D_OS
{
	/*
	 * 打开文件
	 */
	extern DUTILITY_API DHANDLE OpenFile(
		const char* pFullPath,
		DWORD dwFlags = O_RDONLY ,
		DWORD dwMode = D_DEFAULT_FILE_MODE,
		DWORD dwFileAttributes = FILE_ATTRIBUTE_NORMAL ,
		LPSECURITY_ATTRIBUTES pSapSecurity = NULL );

	/*
	 * 读取文件
	 */
	extern DUTILITY_API int ReadFile(
		DHANDLE fileHandle,
		LPVOID pBuffer,
		DWORD dwReadSize,
		LPDWORD dwHaveRead );

	/*
	 * 写入文件
	 */
	extern DUTILITY_API int WriteFile(
		DHANDLE handle, 
		const LPVOID pBuffer,
		DWORD dwWriteSize,
		LPDWORD dwHaveWrite );

	/*
	 * 文件指针定位
	 */
	extern DUTILITY_API int SeekFile(
		DHANDLE handle,
		D_OFF_T lDistance,
		DWORD nMoveMethod );

	/*
	 * 文件同步到磁盘
	 */
	extern DUTILITY_API int FlushFile(
		DHANDLE handle );

	/*
	 * 关闭文件
	 */
	extern DUTILITY_API int CloseFile(
		DHANDLE handle );

	/*
	 * 取文件当前位置 从文件开始的位置
	 */
	extern DUTILITY_API D_OFF_T GetFilePosition(
		DHANDLE handle );

	/*
	 * 取文件的大小 创建时间 修改时间 属性
	 */
	extern DUTILITY_API int GetFileAddribute(
		const char* pFullPath,
		File_Attributes& fileAttri );

	/*
	 * 文件读锁, 共享锁, 默认锁获取失败时立即返回,不阻塞
	 * 没有读权限时读锁失败
	 */
	extern DUTILITY_API int ReadLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_FAIL_IMMEDIATELY );

	/*
	 * 文件写锁，独占
	 */
	extern DUTILITY_API int WriteLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize,
		DWORD dwFlags = LOCKFILE_EXCLUSIVE_LOCK );

	/*
	 * 解锁
	 */
	extern DUTILITY_API int UnLockFile(
		DHANDLE handle,
		D_OFF_T offset,
		LONGLONG llLockSize );

	/*
	 * 文件是否存在
	 */
	extern DUTILITY_API bool IsFileExist( const char* pFullPath );

	/*
	 * 删除文件, 删除空目录, 只读文件不能被删, 权限不够
	 */
	extern DUTILITY_API bool DeleteFile( const char* pFullPath );

	/*
	*	取Path所在路径的磁盘剩余空间字节
	* [参数]
	* pPath			:[IN]  文件路径 [ "C:\\", "E:\\" ,"/root/test.txt" , "/" ]
	*/
	extern DUTILITY_API LONGLONG GetDiskFreeSpace( const char* pPath );

	/*
	 * 截断文件, 适用于将文件缩小
	 */
	extern DUTILITY_API int TruncateFile( 
		DHANDLE handle,
		LONGLONG llSize );

	/*
	 * 复制文件, 从pSourceFile到pDestFile, 可选择是否覆盖DestFile
	 */
	extern DUTILITY_API int CopyFile(
		const char* pSrcFile,
		const char* pDstFile,
		bool bFailIfExist = true );
}

#endif	// _D_FILE_OPERATION_H_