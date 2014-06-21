#include "DMutex.h"

#include <assert.h>

CDMutex::CDMutex( 
	int type /*= MUTEX_PROCESS*/,
	const char* pname /*= 0*/,
	int *parg /*= 0*/,
	int mode /*= D_DEFAULT_FILE_MODE */ )
	: m_pLockName( NULL )
{
	int iRet = -1;

	iRet = D_OS::InitMutex(
		&this->m_mutex,
		type,
		pname,
		parg );

	assert( 0 == iRet );
}

CDMutex::~CDMutex()
{
	this->Remove();
}

int CDMutex::Remove()
{
	return D_OS::DestoryMutex( &this->m_mutex );
}

int CDMutex::Lock()
{
	return D_OS::LockMutex( &this->m_mutex );
}

int CDMutex::Lock( CDTimeStamp& timeout )
{
	return D_OS::LockMutex( &this->m_mutex, timeout );
}

int CDMutex::Lock( CDTimeStamp* timeout )
{
	return D_OS::LockMutex( &this->m_mutex, timeout );
}

int CDMutex::TryLock()
{
	return D_OS::TryLockMutex( &this->m_mutex );
}

int CDMutex::UnLock()
{
	return D_OS::UnLockMutex( &this->m_mutex );
}
