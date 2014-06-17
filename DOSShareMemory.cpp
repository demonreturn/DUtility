
#include "DOSShareMemory.h"

#ifdef D_LINUX
#include <sys/mman.h>
#endif

extern DUTILITY_API DHANDLE D_OS::CreateShareMemory(
	DHANDLE hFile,
	DWORD dwSize,
	const char* szName )
{
	if ( NULL == szName )
	{
		return D_INVALID_HANDLE;
	}

	DHANDLE hRet = D_INVALID_HANDLE;
#ifdef D_WIN32
	hRet = ::CreateFileMappingA(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		dwSize,
		szName );

	if ( NULL == hRet )
	{
		return D_INVALID_HANDLE;
	}

	return hRet;
#elif defined( D_LINUX)		// linux  实现
	// 对Linux来说，传入的文件句柄就是共享内存的句柄
	hRet = hFile;
	if ( D_INVALID_HANDLE == hRet )
	{
		// 如果传入的是D_INVALID_HANDLE(-1)，说明没有指定映射文件路径，这时使用系统默认的
		hRet = ::shm_open(
			szName,
			O_CREAT|O_RDWR,
			-1 );

		if ( D_INVALID_HANDLE != hRet )
		{
			// 设置共享内存大小失败
			if ( -1 == ::ftruncate(hResult, dwSize))
			{
				::close( hRet );

				hRet = D_INVALID_HANDLE;
			}
		}
	}
#endif

	return hRet;
}

extern DUTILITY_API DHANDLE D_OS::OpenShareMemory(
	const char* szName,
	const char* szRegularFileName /*= NULL */ )
{
	if ( NULL == szName )
	{
		return D_INVALID_HANDLE;
	}

	DHANDLE hRet = D_INVALID_HANDLE;
#ifdef D_WIN32
	hRet = ::OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		szName );

	if ( NULL == hRet )
	{
		hRet = D_INVALID_HANDLE;
	}
#elif defined( D_LINUX)		// linux  实现
	if ( NULL != szRegularFileName)
	{
		// 使用普通文件作为映射的内容
		hRet = ::open( szRegularFileName, O_RDWR, -1 );
	}
	else
	{
		// 使用系统目录，一般是在/dev/shm目录下
		hRet = ::shm_open( szName, O_RDWR, -1 );
	}
#endif

	return hRet;
}

extern DUTILITY_API void* D_OS::MapViewShareMemory( 
	DHANDLE hShareMemory,
	DWORD dwSize )
{
	if ( D_INVALID_HANDLE == hShareMemory )
	{
		return NULL;
	}

	void* pRet = NULL;
#ifdef D_WIN32
	pRet = ::MapViewOfFile(
		hShareMemory,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		dwSize );

#elif defined( D_LINUX)		// linux  实现
	pRet = ::mmap(
		NULL,
		dwSize,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		hShareMemory,
		0 );

	if ( MAP_FAILED == pRet )
	{
		pRet = NULL;
	}
#endif

	return pRet;
}

extern DUTILITY_API BOOL D_OS::FlushShareMemory( 
	void* lpDataToFlush, 
	DWORD dwLength )
{
	if ( NULL == lpDataToFlush )
	{
		return FALSE;
	}

	BOOL bRet = FALSE;
#ifdef D_WIN32
	bRet = ::FlushViewOfFile(
		lpDataToFlush,
		dwLength );

#elif defined( D_LINUX)		// linux  实现
	int iRet = ::msync(
		lpDataToFlush,
		dwLength,
		MS_SYNC );

	bRet = (-1 == iRet) ? FALSE : TRUE;
#endif

	return bRet;
}

extern DUTILITY_API int D_OS::CloseShareMemory( 
	DHANDLE hShareMemory,
	bool bMapToFile,
	void* pHeader,
	DWORD dwLength )
{
	int iRet = D_OK;
#ifdef D_WIN32
	if ( NULL != pHeader 
		&& !::UnmapViewOfFile( pHeader)
		&& D_INVALID_HANDLE != hShareMemory 
		&& !::CloseHandle( hShareMemory ) )
	{
		iRet = D_ERROR_FAILURE;
	}

#elif defined( D_LINUX)		// linux  实现
	if ( D_INVALID_HANDLE != hShareMemory
		&& !bMapToFile
		&&  -1 != close(hShareMemory)
		&& NULL != NULL 
		&& -1 == ::munmap( pHeader, dwLength))
	{
		iRet = D_ERROR_FAILURE;
	}

#endif

	return iRet;
}

extern DUTILITY_API void D_OS::UnLinkShareMemory( 
	const char* szName )
{
#ifdef D_LINUX
	::shm_unlink( szName );
#endif
}
