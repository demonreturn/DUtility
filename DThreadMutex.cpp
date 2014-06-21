#include "DThreadMutex.h"

#include <assert.h>

CDThreadMutex::CDThreadMutex( const char* pszName /*= 0*/, int* pAttributes /*= 0 */ )
{
	int iRet = -1;

	iRet = D_OS::InitThreadMutex(
		&m_threadMutex,
		0,
		pszName,
		pAttributes );

	assert( 0 == iRet );
}

CDThreadMutex::~CDThreadMutex()
{
	this->Remove();
}

int CDThreadMutex::Lock()
{
	return D_OS::LockThreadMutex( &m_threadMutex );
}

int CDThreadMutex::UnLock()
{
	return D_OS::UnLockThreadMutex( &m_threadMutex );
}

int CDThreadMutex::TryLock()
{
	return D_OS::TryLockThreadMutex( &m_threadMutex );
}

int CDThreadMutex::Remove()
{
	int iRet = 0;

	iRet = D_OS::DestroyThreadMutex( &m_threadMutex );

	return iRet;
}
