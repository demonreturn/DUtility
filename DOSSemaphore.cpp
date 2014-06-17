
#include "DOSSemaphore.h"


int D_OS::InitSemaphore( D_SEMAPHONE*& pSemaphore, DWORD dwInitCount, DWORD dwMaxCount /*= OS_MAX_SEMAPHORE_COUNT*/, const char* pszName /*= NULL */ )
{
#ifdef D_WIN32
	pSemaphore = new D_SEMAPHONE;
	if ( NULL == pSemaphore )
	{
		return D_ERROR_OUT_OF_MEMORY;
	}

	*pSemaphore = ::CreateSemaphoreA(
		NULL,
		dwInitCount,
		dwMaxCount,
		pszName );

	if ( NULL == *pSemaphore )
	{
		return -1;
	}

	return 0;

#elif defined( D_LINUX)		// linux  实现
	if ( NULL == pSemaphore )
	{
		int ret = ::sem_init( pSemaphore, FALSE, dwInitCount );

		return ret;
	}
	else
	{
		pSemaphore = ::sem_open( pszName, O_CREAT, OS_SEMAPHORE_MODE, dwInitCount );

		if ( SEM_FAILED == pSemaphore )
		{
			return -1;
		}
	}
#endif

	return 0;
}

int D_OS::UnInitSemaphore( D_SEMAPHONE* pSemaphore, const char* pszName /*= NULL */ )
{
	if ( NULL == pSemaphore )
	{
		return D_ERROR_NULL_POINTER;
	}

#ifdef D_WIN32
	::CloseHandle( *pSemaphore );
#elif defined( D_LINUX)		// linux  实现
	int ret = -1;

	if ( NULL == pszName )
	{
		ret -1;
	}

#endif

	return 0;
}
