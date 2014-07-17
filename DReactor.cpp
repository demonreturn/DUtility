
#include "DReactor.h"

#include "DMutexGuardT.h"
#include "DTrace.h"

const int nLoopCount = 2;

CDReactor::CDReactor( IDReacotrImpl* pReactorImpl )
	: m_pReactorImpl( pReactorImpl )
	, m_reactorRunType( REACTOR_IDLE )
{

}

CDReactor::~CDReactor()
{
	D_DELETE( m_pReactorImpl );
}

DResult CDReactor::Run( int runType /*= REACTOR_LOOP */ )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	if ( D_BIT_ENABLED( runType, REACTOR_CALL) )
	{
		m_reactorRunType = REACTOR_CALL;
	}
	else if( D_BIT_ENABLED( runType, REACTOR_LOOP) )
	{
		m_reactorRunType = REACTOR_LOOP;
	}
	else
	{
		D_LOG_ERROR( "reactor run type invalid,runtype:" << runType );
		return D_ERROR_FAILURE;
	}

	return Loop();
}

DResult CDReactor::Notify( int nNotifyCmd )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	if ( nNotifyCmd & REACTOR_NOTIFY_EXIT )
	{
		m_reactorRunType = REACTOR_IDLE;
	}

	return m_pReactorImpl->Notify( nNotifyCmd );
}

DResult CDReactor::RegisterHandler( 
	IDHandler* pHandler,
	int nEvent,
	int* pIndex )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	return m_pReactorImpl->RegisterHandle( pHandler, nEvent, pIndex );
}

DResult CDReactor::UnRegisterHandler( IDHandler* pHandler,int nEvent,int* pIndex )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	return m_pReactorImpl->UnRegisterHandle( pHandler, nEvent, pIndex );
}

DResult CDReactor::AttachTimerQueue( CDTimerQueue* pTQ )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	m_pReactorImpl->AttachTimerQueue( pTQ );

	return D_OK;
}

DResult CDReactor::AttachEventQueue( CDEventQueue* pEQ )
{
	D_CHECK_EX( NULL != m_pReactorImpl, "m_pReactorImpl is null", return D_ERROR_FAILURE );

	m_pReactorImpl->AttachEventQueue( pEQ );

	return D_OK;
}

DResult CDReactor::Loop()
{
	DResult dRet = D_OK;

	CDMutexGuardT<CDMutex> guard( &m_hLock );

	int nFlag = 0;

	do 
	{
		// 如果没有捕获到任何事件就不需要分派
		int nRet = m_pReactorImpl->HandleEvents();

		// 只有在捕获到有事件才需要进行分派，返回-1（出错的情况，不进行分派）
		if ( 0 < nRet)
		{
			dRet = m_pReactorImpl->Dispatch();
		}

		if ( REACTOR_CALL == m_reactorRunType ) 
		{
			break;
		}

		// 如果外部要求终止Reactor消息循环，则这里多做一次循环，以便EQ中所有的事件都处理完了
		if ( REACTOR_IDLE == m_reactorRunType )
		{
			nFlag++;
		}

	} while ( nFlag < nLoopCount );

	return dRet;
}
