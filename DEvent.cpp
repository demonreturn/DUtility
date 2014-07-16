
#include "DEvent.h"
#include <cassert>

CDEvent::CDEvent( 
	INT nManualReset /*= MANUAL_STATE_AUTOEVENT*/,
	INT nInitialState /*= INITIIAL_STATE_NOSIGNAL*/,
	LPCSTR pszName /*= 0*/,
	LPVOID pArg /*= 0 */ )
{
#ifdef D_WIN32
	int iRet = D_OS::InitEvent(
		&this->m_eventHandle,
		nManualReset,
		nInitialState,
		pszName,
		pArg );

	assert( 0 == iRet );
#elif defined( D_LINUX)		// linux  实现
	
#endif
}

CDEvent::~CDEvent()
{
	this->Remove();
}

int CDEvent::Remove()
{
#ifdef D_WIN32
	int iRet = D_OS::DestroyEvent( &this->m_eventHandle );

	return iRet;
#elif defined( D_LINUX)		// linux  实现
	return 0;
#endif
}

D_EVENT CDEvent::GetHandle() const
{
#ifdef D_WIN32
	return this->m_eventHandle;
#elif defined( D_LINUX)		// linux  实现
	return 0;
#endif
}

int CDEvent::Wait()
{
#ifdef D_WIN32
	return D_OS::TimeWaitEvent( &this->m_eventHandle );
#elif defined( D_LINUX)		// linux  实现
	// TODO
#endif
}

int CDEvent::Wait( const CDTimeValue& timeout )
{
#ifdef D_WIN32
	return D_OS::TimeWaitEvent( &this->m_eventHandle, timeout );
#elif defined( D_LINUX)		// linux  实现
	// TODO
#endif
}

int CDEvent::Signal()
{
#ifdef D_WIN32
	return D_OS::PulseEvent( &this->m_eventHandle );
#elif defined( D_LINUX)		// linux  实现
	// TODO
#endif
}

int CDEvent::Reset()
{
#ifdef D_WIN32
	return D_OS::ResetEvent( &this->m_eventHandle );
#elif defined( D_LINUX)		// linux  实现
	return 0;
#endif
}
