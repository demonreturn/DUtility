

#ifndef _D_SEMAPHORE_H_
#define _D_SEMAPHORE_H_

#include "DBase.h"

namespace D_OS
{
	const DWORD OS_MAX_SEMAPHORE_COUNT = 0x7fffffff;
	const DWORD OS_SEMAPHORE_MODE = 438;		// ÎÄ¼þÊôÐÔrw-r--r--

	int InitSemaphore(
		D_SEMAPHONE*& pSemaphore,
		DWORD dwInitCount,
		DWORD dwMaxCount = OS_MAX_SEMAPHORE_COUNT,
		const char* pszName = NULL );

	int UnInitSemaphore( 
		D_SEMAPHONE* pSemaphore, const char* pszName = NULL );

	int LockSemaphore( D_SEMAPHONE* pSemaphore );

	int UnLockSemaphore( D_SEMAPHONE* pSemaphore );

	int PostNSemphore( D_SEMAPHONE* pSemaphore, DWORD dwCount );
}

#endif	// _D_SEMAPHORE_H_


