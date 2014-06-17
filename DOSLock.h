
#ifndef _D_LOCK_H_
#define _D_LOCK_H_

#include "DBase.h"

class CDTimeStamp;

typedef enum tag_MutexAddr
{
	MUTEX_PROCESS,
	MUTEX_THREAD,
} MutexAddr;

typedef D_THREAD_MUTEX DThreadMutex;

typedef struct tag_DMutex
{
	int type;
	union 
	{
		DThreadMutex thread_mutex;
		DHANDLE proc_mutex;
	};
} DMutex;

namespace D_OS
{
	int InitMutex( DMutex* pMutex,
		int lockScope = MUTEX_THREAD,
		const char* pszName = 0,
		int* mutextype = 0,
		LPSECURITY_ATTRIBUTES sa = 0,
		int locktype = 0 );

	int DestoryMutex( DMutex* pMutex );

	int LockMutex( DMutex* pMutex );

	int LockMutex( DMutex* pMutex, int& abandoned );

	int LockMutex( DMutex* pMutex, const CDTimeStamp& timeout );

	int LockMutex( DMutex* pMutex, const CDTimeStamp* timeout );

	int TryLockMutex( DMutex* pMutex );

	int TryLockMutex( DMutex* pMutex, int& abandoned );

	int UnLockMutex( DMutex* pMutex );

	/*****************************************************************************/
	// A set of wrappers for mutex locks end
	/*****************************************************************************/



	/*****************************************************************************/
	// A set of wrappers for critical section begin
	/*****************************************************************************/

	// win32 下是关键段， LINUX下是互斥量
	int DestroyThreadMutex( DThreadMutex* pThreadMutex );

	int InitThreadMutex( DThreadMutex* pThreadMutex,
		int lockType = 0,
		const char* pszName = 0,
		int* mutexType = 0 );

	int LockThreadMutex( DThreadMutex* pThreadMutex );

	int LockThreadMutex( DThreadMutex* pThreadMutex,
		const CDTimeStamp& timeout );

	int LockThreadMutex( DThreadMutex* pThreadMutex,
		const CDTimeStamp* timeout );

	int TryLockThreadMutex( DThreadMutex* pThreadMutex );

	int UnLockThreadMutex( DThreadMutex* pThreadMutex );

	/*****************************************************************************/
	// A set of wrappers for critical section end
	/*****************************************************************************/


	/*****************************************************************************/
	// A set of wrappers for event start
	/*****************************************************************************/

	int DestroyEvent( DHANDLE* event );

	int InitEvent( DHANDLE* event,
		int manualReset = 0,
		int initialState = 0,
		const char* pszName = 0,
		void* pArg = 0,
		LPSECURITY_ATTRIBUTES sa = 0 );

	int PulseEvent( DHANDLE* event );

	int ResetEvent( DHANDLE* event );

	int SignalEvent( DHANDLE* event );

	int TimeWaitEvent( DHANDLE* event );

	int TimeWaitEvent( DHANDLE* event,
		const CDTimeStamp& timeout );

	/*****************************************************************************/
	// A set of wrappers for event end
	/*****************************************************************************/
}

#endif // _D_LOCK_H_
