
#ifndef _D_MUTEX_H_
#define _D_MUTEX_H_

#include "DBase.h"

#include "DTimeStamp.h"
#include "DOSLock.h"

class CDMutex
{
public:
	CDMutex(
		int type = MUTEX_PROCESS,
		const char* pname = 0,
		int *parg = 0,
		int mode = D_DEFAULT_FILE_MODE );

	~CDMutex();

	int Lock();

	int Lock( CDTimeStamp& timeout );

	int Lock( CDTimeStamp* timeout );

	int TryLock();

	int UnLock();

	const DMutex& GetMutex() const;

	//void Dump() const

private:
	void operator = ( const CDMutex& );
	CDMutex( const CDMutex& );

	/*
	 * 移除并释放内核对象
	 */
	int Remove();

private:
	DMutex						m_mutex;

	const char*					m_pLockName;
};


#endif	// _D_MUTEX_H_

