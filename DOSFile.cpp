
#include "DOSFile.h"


#ifdef D_WIN32
#include <io.h>
#include <sys/stat.h>
#elif defined( D_LINUX)		// linux  实现
#include <sys/statfs.h>
#endif

extern DUTILITY_API HANDLE D_OS::OpenFile( 
	const char* pFullPath,
	DWORD dwFlags /*= O_RDONLY */,
	DWORD dwMode /*= D_DEFAULT_FILE_MODE*/,
	DWORD dwFileAttributes /*= FILE_ATTRIBUTE_NORMAL */,
	LPSECURITY_ATTRIBUTES pSapSecurity /*= NULL */ )
{
	if ( NULL == pFullPath )
	{
		return D_INVALID_HANDLE;
	}

#ifdef D_WIN32
	DWORD dwAccess = GENERIC_READ;
	DWORD dwShareMode = dwMode;
	DWORD dwCreation = OPEN_EXISTING;
	DWORD dwFlagsAndAttributes = dwFileAttributes;

	//对文件的访问权限标志
	if ( D_BIT_ENABLED( dwFlags, O_WRONLY ) )
	{
		dwAccess = GENERIC_WRITE;
	}
	else if ( D_BIT_ENABLED( dwFlags, O_RDWR ) )
	{
		dwAccess = GENERIC_READ | GENERIC_WRITE;
	}
	//文件打开/创建标志
	if ( D_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_EXCL ), ( O_CREAT | O_EXCL ) ) )
		//if ( (nFlags & (_O_CREAT | _O_EXCL) ) == (_O_CREAT | _O_EXCL) )
	{
		//文件不存在,生成一个新文件
		//文件已存在,创建失败
		dwCreation = CREATE_NEW;
	}
	else if( D_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_TRUNC ), ( O_CREAT | O_TRUNC ) ) )
		//else if ( (nFlags & (_O_CREAT | _O_TRUNC) ) == ((_O_CREAT | _O_TRUNC)) )
	{
		//文件已存在,返回成功 文件被清空
		//文件不存在,生成一个新文件
		dwCreation = CREATE_ALWAYS;
	}
	else if ( D_BIT_ENABLED (dwFlags, O_CREAT) )
	{
		//文件已存在,返回成功
		//文件不存在,生成一个新文件
		dwCreation = OPEN_ALWAYS;
	}
	else if ( D_BIT_ENABLED (dwFlags, O_TRUNC) )
	{
		//文件不存在,返回失败
		dwCreation = TRUNCATE_EXISTING;
	}

	if ( D_BIT_ENABLED( dwFlags, O_TEMPORARY ) )
	{
		//临时文件属性
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE;
	}

	HANDLE handle = ::CreateFileA(
		pFullPath,
		dwAccess,
		dwShareMode,
		pSapSecurity,
		dwCreation,
		dwFlagsAndAttributes,
		NULL );

	if ( INVALID_HANDLE_VALUE == handle )
	{
		return D_INVALID_HANDLE;
	}
	else
	{
		if ( D_BIT_ENABLED( dwFlags, O_APPEND ))
		{
			::SetFilePointer( handle,
				0,
				0,
				FILE_END );
		}
	}

	return handle;
#elif defined( D_LINUX)		// linux  实现
	return (::open(pFullPath,
		dwFlags,
		dwMode ));
#endif
}

extern DUTILITY_API int D_OS::ReadFile( 
	HANDLE fileHandle,
	LPVOID pBuffer,
	DWORD dwReadSize,
	LPDWORD dwHaveRead )
{
	if ( NULL == pBuffer )
	{
		return -1;
	}

#ifdef D_WIN32
	if ( ::ReadFile( fileHandle,
		pBuffer,
		dwReadSize,
		dwHaveRead,
		NULL ))
	{
		return 0;
	}
#elif defined( D_LINUX)		// linux  实现
	ssize_t sz = ::read( fileHandle,
		pBuffer,
		dwReadSize );
	if ( sz >= 0 )
	{
		*dwHaveRead = sz;
		return 0;
	}
#endif
	return -1;
}

extern DUTILITY_API int D_OS::WriteFile(
	HANDLE handle,
	const LPVOID pBuffer,
	DWORD dwWriteSize,
	LPDWORD dwHaveWrite )
{
	if ( NULL == dwHaveWrite )
	{
		return -1;
	}
#ifdef D_WIN32
	if ( ::WriteFile( handle,
		pBuffer,
		dwWriteSize,
		dwHaveWrite,
		NULL ))
	{
		return 0;
	}
#elif defined( D_LINUX)		// linux  实现
	ssize_t sz = ::write( handle,
		pBuf,
		dwWriteSize );
	if ( sz >= 0 )
	{
		*dwHaveWrite = sz;
		return 0;
	}
#endif

	return -1;
}

extern DUTILITY_API int D_OS::SeekFile( 
	HANDLE handle,
	D_OFF_T lDistance,
	DWORD nMoveMethod )
{
#ifdef D_WIN32
	LARGE_INTEGER lgDistance;
	lgDistance.QuadPart = lDistance;

	DWORD dwRet = ::SetFilePointer( handle, 
		lgDistance.LowPart,
		&(lgDistance.HighPart),
		nMoveMethod );
	if ( dwRet == INVALID_SET_FILE_POINTER 
		&& GetLastError() != NO_ERROR )
	{
		return -1;
	}

	return 0;
#elif defined( D_LINUX)		// linux  实现
	D_OFF_T lRet = ::lseek( handle,
		lDistance,
		nMoveMethod );

	if ( -1 != lRet )
	{
		return 0;
	}
#endif

	return -1;
}

extern DUTILITY_API int D_OS::FlushFile( HANDLE handle )
{
#ifdef D_WIN32
	if ( ::FlushFileBuffers( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( D_LINUX)		// linux  实现
	return ::fsync( handle );
#endif

	return -1;
}

extern DUTILITY_API int D_OS::CloseFile( HANDLE handle )
{
#ifdef D_WIN32
	if ( ::CloseHandle( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( D_LINUX)		// linux  实现
	return ::close(handle);
#endif

	return -1;
}

extern DUTILITY_API D_OFF_T D_OS::GetFilePosition( 
	HANDLE handle )
{
#ifdef D_WIN32
	LARGE_INTEGER lgIn;
	LARGE_INTEGER lgOut;
	lgIn.QuadPart = 0;

	BOOL bRet = ::SetFilePointerEx( 
		handle,
		lgIn, 
		&lgOut, 
		FILE_CURRENT );

	if ( bRet)
	{
		return lgOut.QuadPart;
	}

	return -1;
#elif defined( D_LINUX)		// linux  实现
	return ::lseek( handle, 0, SEEK_CUR );
#endif

	return -1;
}

extern DUTILITY_API int D_OS::GetFileAddribute( 
	const char* pFullPath,
	File_Attributes& fileAttri )
{
	if ( NULL == pFullPath )
	{
		return -1;
	}

#ifdef D_WIN32
	struct __stat64 fileStat;
	int iRet = ::_stat64( pFullPath,
		&fileStat );

	if ( 0 != iRet )
	{
		return -1;
	}

	fileAttri.llCreateTime = fileStat.st_ctime;
	fileAttri.llFileSize = fileStat.st_size;
	fileAttri.llModifyTime = fileStat.st_mtime;
#elif defined( D_LINUX)		// linux  实现
	struct stat fileStat;

	int iRet = ::stat( pFullPath, 
		&fileStat );
	if ( 0 == iRet )
	{
		fileAttri.llCreateTime = fileStat.st_ctime;
		fileAttri.llFlesize = fileStat.st_size;
		fileAttri.llModifyTime = fileStat.st_mtime;
	}

	return -1;
#endif

	return -1;
}

extern DUTILITY_API int D_OS::ReadLockFile( 
	HANDLE handle,
	D_OFF_T offset,
	LONGLONG llLockSize,
	DWORD dwFlags /*= LOCKFILE_FAIL_IMMEDIATELY */ )
{
#ifdef D_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.hEvent=NULL;
	overLapp.Internal = NULL;
	overLapp.InternalHigh = NULL;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	BOOL bRet = ::LockFileEx( handle,
		dwFlags,
		0,
		lg.LowPart,
		lg.HighPart,
		&overLapp );

	return bRet ? 0 : -1;

#elif defined( D_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_RDLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return iRet != 0 ? -1 : 0;
#endif
}

extern DUTILITY_API int D_OS::WriteLockFile( 
	HANDLE handle,
	D_OFF_T offset,
	LONGLONG llLockSize,
	DWORD dwFlags /*= LOCKFILE_EXCLUSIVE_LOCK */ )
{
#ifdef D_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	DWORD dwWriteFlag = dwFlags | LOCKFILE_EXCLUSIVE_LOCK;

	BOOL bRet = ::LockFileEx( handle,
		dwWriteFlag,
		0,
		lg.LowPart,
		lg.HighPart,
		&overLapp );

	return bRet ? 0 : -1;
#elif defined( D_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_WRLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return iRet != 0 ? -1 : 0;
#endif
}

extern DUTILITY_API int D_OS::UnLockFile(
	HANDLE handle,
	D_OFF_T offset,
	LONGLONG llLockSize )
{
#ifdef D_WIN32
	LARGE_INTEGER lg;
	lg.QuadPart = llLockSize;

	OVERLAPPED overLapp;
	lg.QuadPart = offset;
	overLapp.Offset = lg.LowPart;
	overLapp.OffsetHigh = lg.HighPart;

	BOOL bRet = ::UnlockFileEx( 
		handle, 
		0, 
		lg.LowPart,
		lg.HighPart, 
		&overLapp );

	return bRet ? 0 : -1;
#elif defined( D_LINUX)		// linux  实现
	struct flock fileLock;
	fileLock.l_type = F_UNLCK;
	fileLock.l_whence = SEEK_SET;
	fileLock.l_start = offset;
	fileLock.l_len = llLockSize;

	int iRet = ::fcntl( 
		handle, 
		F_SETLK, 
		&fileLock );

	return (iRet == 0) ? 0 : -1;
#endif
}

extern DUTILITY_API bool D_OS::IsFileExist( 
	const char* pFullPath )
{
	if ( NULL == pFullPath )
	{
		return false;
	}

#ifdef D_WIN32
	int iRet = ::_access( pFullPath, 0 );

	return (iRet == -1) ? false : true;
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::access( pFullPath, F_OK );

	return (iRet == -1) ? false : true;
#endif
}

extern DUTILITY_API bool D_OS::DeleteFile( 
	const char* pFullPath )
{
	if ( NULL == pFullPath )
	{
		return false;
	}

#ifdef D_WIN32
	return ::DeleteFileA( pFullPath ) ? true : false;
#elif defined( D_LINUX)		// linux  实现
	int iRet = ::remove( pFullPath );

	return (0 == iRet) ? true : false;
#endif
}

extern DUTILITY_API LONGLONG D_OS::GetDiskFreeSpace( 
	const char* pPath )
{
#ifdef D_WIN32
	ULARGE_INTEGER lgFreeBytesAvailable;
	ULARGE_INTEGER lgTotalBytes;
	ULARGE_INTEGER lgFreeTotalBytes;

	BOOL bRet = ::GetDiskFreeSpaceExA( pPath, 
		&lgFreeBytesAvailable, 
		&lgTotalBytes, 
		&lgFreeTotalBytes );
	return lgFreeBytesAvailable.QuadPart;

#elif defined( D_LINUX)		// linux  实现
	struct statfs fsInfo;
	int iRet = ::statfs( pPath, 
		&fsInfo );
	//f_bsize : block大小
	//f_bfree : blcok数
	LONGLONG llFreeBytes = fsInfo.f_bsize * fsInfo.f_bfree ;

	return llFreeBytes;
#endif
}

extern DUTILITY_API int D_OS::TruncateFile( 
	HANDLE handle,
	LONGLONG llSize )
{
#ifdef D_WIN32
	int iRet = ::D_OS::SeekFile(
		handle, llSize, D_SEEK_BEGIN );

	if ( iRet != 0 )
	{
		return -1;
	}

	BOOL bRet = ::SetEndOfFile( handle );

	return bRet ? 0 : -1;
#elif defined( D_LINUX)		// linux  实现
	return ::ftruncate( 
		handle, 
		llSize );
#endif
}

extern DUTILITY_API int D_OS::CopyFile( 
	const char* pSrcFile,
	const char* pDstFile,
	bool bFailIfExist /*= true */ )
{
	if ( NULL == pSrcFile || NULL == pDstFile )
	{
		return -1;
	}
#ifdef D_WIN32
	bool bRet = ::CopyFileA(
		pSrcFile,
		pDstFile,
		bFailIfExist ) ? true : false;

	return bRet ? 0 : -1;
#elif defined( D_LINUX)		// linux  实现

	if ( bFailIfExist && IsFileExist( pDstFile ))
	{
		return -;
	}

	FileAttribute fileAttri;
	LONGLONG llFileSize = -1;

	if ( 0 == D_OS::GetFileAddribute( pSrcFile, fileAttri) )
	{
		llFileSize = fileAttri.llFlesize;
	}
	else
	{
		return -1;
	}

	HANDLE hSrcHandle = D_OS::OpenFile( pSrcFile );
	HANDLE hDstHandle = D_OS::OpenFile( pDstFile,
		O_CREAT | O_WRONLY | O_TRUNC );

	if ( D_INVALID_HANDLE == hSrcHandle 
		|| D_INVALID_HANDLE == hDstHandle )
	{
		D_OS::CloseFile( pSrcFile );
		D_OS::CloseFile( pDstFile );
		return -1;
	}

	if ( -1 ==  D_OS::ReadLockFile( hSrcHandle,
		0, llFileSize) )
	{
		D_OS::CloseFile( pSrcFile );
		D_OS::CloseFile( pDstFile );
		return -1;
	}

	//目标文件加写锁
	if ( -1 == D_OS::WriteLockFile( hDstHandle,
		0, llFileSize) )
	{
		D_OS::UnLockFile( hSrcHandle,
			0, llFileSize );

		D_OS::CloseFile( pSrcFile );
		D_OS::CloseFile( pDstFile );
		return -1;
	}

	char tempBuffer[1024];
	DWORD dwHaveRead = 0;
	DWORD dwhaveWrite = 0;
	int iRet = 0;
	bool bFailed = false;

	while ( true )
	{
		dwHaveRead = 0;
		iRet = D_OS::ReadFile( hSrcHandle,
			tempBuffer,
			sizeof( tempBuffer),
			&dwHaveRead );

		if ( -1 == iRet 
			|| 0 == dwHaveRead )
		{

			bFailed = ((0 == dwHaveRead) ? false : true);

			break;
		}

		dwhaveWrite = 0;
		iRet = ::D_OS::WriteFile( hDstHandle, tempBuffer, dwHaveRead, &dwhaveWrite );
		if ( -1 == iRet )
		{
			bFailed = true;
			break;
		}
	}

	D_OS::UnLockFile( hSrcHandle, 0, llFileSize );
	D_OS::UnLockFile( hDstHandle, 0, llFileSize );

	D_OS::CloseFile( hSrcHandle );
	D_OS::CloseFile( hDstHandle );

	if ( bFailed )
	{
		D_OS::DeleteFile( pDstFile );
	}

	return 0;
#endif

	return -1;
}