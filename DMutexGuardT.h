
#ifndef _D_MUTEX_GUARD_T_H_
#define _D_MUTEX_GUARD_T_H_

#include "DBase.h"

template< class locktype>
class CDMutexGuardT
{
public:
	CDMutexGuardT( locktype* pMutex = NULL );
	~CDMutexGuardT();

private:
	int Lock();

	int UnLock();

private:

	locktype*					m_pMutex;
};

template< class locktype>
int CDMutexGuardT<locktype>::UnLock()
{
	int iRet = -1;
	if ( NULL != m_pMutex )
	{
		iRet = m_pMutex->UnLock();
	}

	return iRet;
}

template< class locktype>
int CDMutexGuardT<locktype>::Lock()
{
	int iRet = -1;

	if ( NULL != m_pMutex )
	{
		iRet = m_pMutex->Lock();
	}

	return iRet;
}

template< class locktype>
CDMutexGuardT<locktype>::~CDMutexGuardT()
{
	this->UnLock();

}

template< class locktype>
CDMutexGuardT<locktype>::CDMutexGuardT( locktype* pMutex /*= NULL */ )
	: m_pMutex( pMutex )
{
	this->Lock();
}

#endif	// _D_MUTEX_GUARD_T_H_