
#include "DThread.h"
#include "DOSThread.h"


#include "DTrace.h"

CDThread::CDThread()
	: m_id( 0 )
	, m_handle( 0 )
{
}

CDThread::~CDThread()
{
	assert( 0 == m_handle );
	assert( 0 == m_id );
}

bool CDThread::Start()
{
	int iRet = D_OS::CreateThread(CDThread::StartThread, this, 0, &m_id, &m_handle);
	assert( 0 == iRet );

	return (iRet == 0);
}

void CDThread::Join()
{
	if ( 0 != m_handle )
	{
		assert( m_id != D_OS::GetSelfThreadID() );

		D_THR_FUNC_RETURN stat = 0;

		int iRet = D_OS::JoinThread( m_handle, &stat );

		m_handle = 0;

		m_id = 0;

		assert( 0 == iRet );
	}
}

void CDThread::Terminate()
{
	if ( m_handle == 0 )
	{
		assert( 0 == m_id );
		return;
	}

	int iRet = D_OS::TerminateThread( m_handle, 0 );
	assert( 0 == iRet );

	m_handle = 0;

	m_id = 0;
}

#ifdef D_WIN32
UINT D_STD_CALL CDThread::StartThread( LPVOID pArg )
#elif defined( D_LINUX)		// linux  实现
static void* D_STD_CALL CDThread::StartThread( LPVOID pArg );
#endif
{
	CDThread* pthread = (CDThread*)pArg;

	pthread->Run();

	return 0;
}



CDThreadBase::CDThreadBase( 
	DWORD dwThreadDefineType /*= (DWORD)-1*/,
	IDThreadSink* pThreadSink /*= NULL*/, 
	THREAD_BLOCK_TYPE blockType /*= THREAD_BLOCK */ )
	: m_pSink( pThreadSink )
	, m_dwThreadID( 0 )
	, m_hThread( 0 )
	, m_nThreadDefineType( dwThreadDefineType )
	, m_bDestroyed( FALSE )
	, m_BlockType( blockType )
	, m_CreateType( THREAD_NO_TYPE )
	, m_pTQ( NULL )
	, m_pEQ( NULL )
{
	if ( THREAD_NONBLOCK == blockType )
	{
		m_dwThreadID = D_OS::GetSelfThreadID();
	}
}

CDThreadBase::~CDThreadBase()
{
	m_pSink = NULL;

	m_dwThreadID = 0;

	m_hThread = NULL;
}

DResult CDThreadBase::ScheduleTimer( 
	CDTimer* pTimer,
	IDThreadSink* pSink,
	const CDTimeValue& delay,
	const CDTimeValue& interval,
	int runTimes /*= -1 */ )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

DResult CDThreadBase::CancleTimer( CDTimer* pTimer )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

DResult CDThreadBase::SetTimerQueue( CDTimerQueue* pTimerQueue )
{
	D_CHECK_EX( NULL != pTimerQueue, "pTimerQueue is null", D_ERROR_NULL_POINTER );

	if ( NULL != m_pTQ )
	{
		m_pTQ->Destory();
	}

	m_pTQ = pTimerQueue;

	return D_OK;
}

CDTimerQueue* CDThreadBase::GetTimerQueue()
{
	return m_pTQ;
}

DResult CDThreadBase::PostEvent( IDEvent* pEvent )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

DResult CDThreadBase::SendEvent( IDEvent* pEvent )
{
	return D_ERROR_NOT_IMPLEMENTED;
}

DResult CDThreadBase::SetEventQueue( CDEventQueue* pEventQueue )
{
	D_CHECK_EX( NULL != pEventQueue, "pEventQueue is null", return D_ERROR_NULL_POINTER );
	
	if ( NULL != m_pEQ )
	{
		m_pEQ->Destory();
	}

	m_pEQ = pEventQueue;

	return D_OK;
}

CDEventQueue* CDThreadBase::GetEventQueue()
{
	return m_pEQ;
}

DResult CDThreadBase::HeartBeat()
{
	DResult dRet = D_ERROR_FAILURE;

	if ( m_BlockType & THREAD_BLOCK )
	{
		return dRet;
	}

	if ( NULL != m_pSink )
	{
		m_pSink->OnThreadRun( this );
		m_pSink->OnThreadStop( this );
	}

	return dRet;
}

DResult CDThreadBase::SetThreadSink( IDThreadSink* pSink )
{
	// 可以设置null
	//D_CHECK_EX( NULL != pSink, "pSink is null", return D_ERROR_NULL_POINTER );

	m_pSink = pSink;

	return D_OK;
}

DResult CDThreadBase::Join()
{
	// 当前操作不允许
	DResult dRet = D_ERROR_OPER_NOT_ALLOWED;

	// 如果是被动的，就返回，失败
	if ( m_BlockType & THREAD_NONBLOCK )
	{
		return dRet;
	}

	if ( NULL == m_hThread )
	{
		return dRet;
	}

	if ( D_OS::GetSelfThreadID() == m_dwThreadID )
	{
		return dRet;
	}

	D_THR_FUNC_RETURN stat = 0;

	int iret = D_OS::JoinThread( m_hThread, &stat );

	if ( 0 != iret )
	{
		return D_ERROR_FAILURE;
	}

	dRet = D_OK;

	return dRet;
}

DResult CDThreadBase::Join( const CDTimeValue& timeout )
{
	// 当前操作不允许
	DResult dRet = D_ERROR_OPER_NOT_ALLOWED;

	// 如果是被动的，就返回，失败
	if ( m_BlockType & THREAD_NONBLOCK )
	{
		return dRet;
	}

	if ( NULL == m_hThread )
	{
		return dRet;
	}

	if ( D_OS::GetSelfThreadID() == m_dwThreadID )
	{
		return dRet;
	}

	int iret = D_OS::WaitThread( m_hThread, timeout );

	if ( 0 != iret )
	{
		return D_ERROR_FAILURE;
	}

	dRet = D_OK;

	return dRet;
}

DResult CDThreadBase::Activate()
{
	// 当前操作不允许
	DResult dRet = D_ERROR_OPER_NOT_ALLOWED;

	// 如果是被动的，就返回，失败
	if ( m_BlockType & THREAD_NONBLOCK )
	{
		return dRet;
	}

	if ( NULL == m_hThread )
	{
		return dRet;
	}

	if ( D_OS::GetSelfThreadID() == m_dwThreadID )
	{
		return dRet;
	}

	int iret = D_OS::CreateThread(
		CDThreadBase::ThreadEntry,
		this,
		0,
		&m_dwThreadID,
		&m_hThread );

	if ( 0 == m_hThread )
	{
		return D_ERROR_FAILURE;
	}

	dRet = D_OK;

	return dRet;
}

D_THREAD_ID CDThreadBase::GetThreadID()
{
	return m_dwThreadID;
}

DResult CDThreadBase::TerminateThread()
{
	D_OS::TerminateThread( m_hThread, 0 );

	m_hThread = 0;
	m_dwThreadID = 0;

	return D_OK;
}

INT CDThreadBase::Destroy()
{
	CDMutexGuardT<CDThreadMutex> guard( &m_ThreadMutex );

	if ( m_bDestroyed )
	{
		return -1;
	}

	m_bDestroyed = TRUE;

	return D_OK;
}

VOID CDThreadBase::SetThreadID( DWORD dwThreadID )
{
	m_dwThreadID = dwThreadID;
}

VOID CDThreadBase::SetThreadHandle( D_THREAD_HANDLE threadHandle )
{
	m_hThread = threadHandle;
}

VOID CDThreadBase::OnThreadRun()
{
	D_CHECK_EX( NULL != m_pSink, "m_pSink is null", return );

	m_pSink->OnThreadRun( this );
}

VOID CDThreadBase::OnThreadStop()
{
	D_CHECK_EX( NULL != m_pSink, "m_pSink is null", return );

	m_pSink->OnThreadStop( this );
}

BOOL CDThreadBase::IsDestroyed()
{
	return m_bDestroyed;
}

DWORD CDThreadBase::GetDefineThreadID()
{
	return m_nThreadDefineType;
}

THREAD_BLOCK_TYPE CDThreadBase::GetBlockType()
{
	return m_BlockType;
}

VOID CDThreadBase::SetBlockType( THREAD_BLOCK_TYPE blockType )
{
	m_BlockType = blockType;
}

THREAD_CREATE_TYPE CDThreadBase::GetCreateType()
{
	return m_CreateType;
}

VOID CDThreadBase::SetCreateType( THREAD_CREATE_TYPE createType /*= THREAD_NET_TYPE */ )
{
	m_CreateType = createType;
}

#ifdef D_WIN32
UINT D_STD_CALL CDThreadBase::ThreadEntry( LPVOID pArg )
#elif defined( D_LINUX)		// linux  实现
void* D_STD_CALL CDThreadBase::ThreadEntry( LPVOID pArg );
#endif
{
	CDThreadBase* pthread = (CDThreadBase*) pArg;

	if ( NULL == pthread )
	{
#ifdef D_WIN32
		_endthreadex( 0 );
#elif defined( D_LINUX)		// linux  实现
		::PMINIDUMP_THREAD_EX_LIST( NULL );
#endif

		return 0;
	}

	pthread->OnThreadRun();

	pthread->OnThreadStop();

#ifdef D_WIN32

	_endthreadex( 0 );
	
#endif

	return 0;
}
