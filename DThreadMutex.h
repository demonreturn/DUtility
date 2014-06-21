
#ifndef _D_THREAD_MUTEX_H_
#define _D_THREAD_MUTEX_H_

#include "DBase.h"
#include "DOSLock.h"

class CDThreadMutex
{
public:
	CDThreadMutex( const char* pszName = 0,
		int* pAttributes = 0 );

	virtual ~CDThreadMutex();

public:
	int Lock();

	int UnLock();

	int TryLock();

private:
	int Remove();

	void operator = ( const CDThreadMutex& );
	CDThreadMutex( const CDThreadMutex& );

	DThreadMutex				m_threadMutex;
};

#endif	// _D_THREAD_MUTEX_H_
