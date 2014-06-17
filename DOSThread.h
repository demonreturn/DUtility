

#ifndef _D_OS_THREAD_H_
#define _D_OS_THREAD_H_

#include "DBase.h"
#include "DTimeStamp.h"

namespace D_OS
{
	inline int CreateThread(
		LPVOID pparms,
		D_THREAD_FUNC func,
		long flags,
		DWORD* pthreadID,
		DHANDLE* pthreadHandle = 0,
		long npriority = 0,
		LPVOID stack = NULL,
		DWORD stacksize = 0 )
	{
#ifdef D_WIN32
		*pthreadHandle = (HANDLE)_beginthreadex(
			NULL,
			stacksize,
			func,
			pparms,
			flags,
			(unsigned int*) *pthreadID );

		if ( D_INVALID_HANDLE == *pthreadHandle )
		{
			return -1;
		}

#elif defined( D_LINUX)		// linux  实现
		pthread_attr_t attr;
		int iresult = ::pthread_attr_init( &attr );
		if ( 0 != iresult )
		{
			return -1;
		}

		iresult = ::pthread_attr_setdetachstate(
			&attr,
			PTHREAD_CREATE_JOINABLE );

		if ( 0 != iresult )
		{
			::pthread_attr_destroy( &attr );
			return -1;
		}

		iresult = ::pthread_create(
			pthreadID,
			&attr,
			func,
			pparms );

		if ( 0 != iresult )
		{
			::pthread_attr_destroy( &attr );
			return -1;
		}

		::pthread_attr_destroy( &attr );

		*pthreadHandle = (*pthreadID);
#endif

		return 0;
	}

	inline DWORD GetSelfThreadID()
	{
#ifdef D_WIN32
		return ::GetCurrentThreadId();
#elif defined( D_LINUX)		// linux  实现
		return ::pthread_self();
#endif
	}

	inline DHANDLE GetSelfThreadHandle()
	{
#ifdef D_WIN32
		return ::GetCurrentThread();
#elif defined( D_LINUX)		// linux  实现
		return ::pthread_self();
#endif
	}

	inline bool IsThreadEqual( DWORD tid1, DWORD tid2 )
	{
#ifdef D_WIN32
		return tid1 == tid2;
#elif defined( D_LINUX)		// linux  实现
		return ::pthread_equal( tid1, tid2 );
#endif
	}

	inline bool IsThreadEqual( DHANDLE h1, DHANDLE h2 )
	{
#ifdef D_WIN32
		return h1 == h2;
#elif defined( D_LINUX)		// linux  实现
		return ::pthread_equal( h1, h2 );
#endif
	}

	inline int SuspendThread( DHANDLE th )
	{
#ifdef D_WIN32
		if ( D_INVALID_HANDLE == th )
		{
			return -1;
		}

		DWORD dwRet = ::SuspendThread( th );

		if ( dwRet == (DWORD)(-1) )
		{
			return -1;
		}
#elif defined( D_LINUX)		// linux  实现
		return -1;
#endif

		return 0;
	}

	inline int ResumeThread( DHANDLE th )
	{
#ifdef D_WIN32
		if ( D_INVALID_HANDLE == th )
		{
			return -1;
		}

		DWORD dwRet = ::ResumeThread( th );

		if ( dwRet == (DWORD)(-1) )
		{
			return -1;
		}
#elif defined( D_LINUX)		// linux  实现
		return -1;
#endif

		return 0;
	}

	inline int JoinThread( DHANDLE th, D_THR_FUNC_RETURN* pstatus )
	{
#ifdef D_WIN32

		if ( D_INVALID_HANDLE == th )
		{
			return -1;
		}

		D_THR_FUNC_RETURN localStatus = 0;
		if ( 0 == pstatus )
		{
			pstatus = &localStatus;
		}

		if ( WAIT_OBJECT_0 == ::WaitForSingleObject( th, INFINITE ) 
			&& FALSE != ::GetExitCodeThread( th, pstatus ) )
		{
			::CloseHandle( th );
			return 0;
		}

		return -1;
#elif defined( D_LINUX)		// linux  实现
		int iRet = ::pthread_join( th, NULL );

		return iRet;
#endif
	}

	inline int WaitThread( DHANDLE th, const CDTimeStamp& ts )
	{
#ifdef D_WIN32
		DWORD ret;

		ret = ::WaitForSingleObject( th, ts.GetMicroseconds() / 1000 );

		switch ( ret )
		{
		case WAIT_OBJECT_0:
			{
				::CloseHandle( th );

				return 0;
			}
			break;

		case WAIT_TIMEOUT:
			return -1;
			break;

		default:
			return -1;
		}
#elif defined( D_LINUX)		// linux  实现
		int ret = ::pthread_join( th, NULL );

		return ret;
#endif

		return 0;
	}

	inline int TerminateThread( DHANDLE th, DWORD dwExitCode )
	{
#ifdef D_WIN32
		BOOL bflag = FALSE;
		bflag = ::TerminateThread( th, dwExitCode );

		if ( FALSE == bflag )
		{
			return -1;
		}

		::CloseHandle( th );

		return 0;
#elif defined( D_LINUX)		// linux  实现
		int ret = ::pthread_detach( th );

		return ret;
#endif
	}

	inline int GetThreadPriority( DHANDLE th, int& priority )
	{
#ifdef D_WIN32
		priority = ::GetThreadPriority( th );

		return 0;
#elif defined( D_LINUX)		// linux  实现
		return -1;
#endif
	}

	inline int SetThreadPriority( DHANDLE th, int priority )
	{
#ifdef D_WIN32
		return ::SetThreadPriority( th, priority );
#elif defined( D_LINUX)		// linux  实现
		return -1;
#endif
	}
}

#endif // _D_OS_THREAD_H_

