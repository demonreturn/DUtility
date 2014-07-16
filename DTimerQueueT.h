
#ifndef _D_TIMER_QUEUE_T_
#define _D_TIMER_QUEUE_T_

#include "DBase.h"
#include "DDataStructure.h"
#include "DTimerNodeT.h"
#include "DMutexGuardT.h"

#include "DTrace.h"

const DWORD TIME_TICK_MIN = 50; // 毫秒，最小定时时间
const DWORD TIME_TICK_MAX = 4294967; // 秒，最大定时上线

interface IDTimerSink
{
public:
	virtual ~IDTimerSink() {}

	virtual int OnTimer( CDTimer* pTimer ) = 0;
};

template< class TIMERTYPE, class TYPE, class LOCK>
class CDTimerQueueT
{
protected:
	typedef CDTimeNodeT<TIMERTYPE, TYPE>* TIMERNODE;

public:
	CDTimerQueueT();

	virtual DResult Schedule(
		TIMERTYPE pTimerType, 
		TYPE pType,
		const CDTimeValue& delay,
		const CDTimeValue& interval,
		int runtimes = -1 );

	virtual DResult Cancle( TIMERTYPE pTimerType );

	virtual int Expire();

	virtual DResult Sort();

	DResult GetEarliestInterVal( DWORD& dwTickCount );

	void Destory();

	DResult Stop();

	DResult Start();

	DResult SetOwnerThread( DWORD dwThreadID );

private:
	virtual ~CDTimerQueueT();

	CDTimerQueueT<TIMERTYPE, TYPE> AllocNode();

	DResult SetTimerNode( 
		TIMERNODE pTimerNode,
		TIMERTYPE pTimerType, 
		TYPE pType, 
		const CDTimeValue& delay,
		const CDTimeValue& interval,
		int runtimes );

	DResult Dispatch( CDTimeNodeT<TIMERTYPE, TYPE> * pTimerNode );

	int UpdateTimerNode( TIMERNODE pTimerNode );

	void FreeNode( CDTimeNodeT<TIMERTYPE, TYPE>*& pTimerNode );

/*	void Sort();*/

	DResult Schedule( TIMERNODE pTimerNode );

	DResult ReSchedule( TIMERNODE pTimerNode );

	void UpdateReferenceTimeTick();

private:
	LOCK						m_lock;

	CDNodeListT<TIMERNODE>		m_nodeList;

	INT64						m_timerTick;

	LOCK						m_tLock;

	QUEUE_STATUS				m_queueStatus;

	DWORD						m_threadID;
};

template< class TIMERTYPE, class TYPE, class LOCK>
void CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::UpdateReferenceTimeTick()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	m_timerTick = CDTimeWatch::GetTickCount();
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::ReSchedule( TIMERNODE pTimerNode )
{
	D_CHECK_EX( NULL != pTimerNode, "", return D_ERROR_NULL_POINTER );

	this->UpdateTimerNode( pTimerNode );

	DResult dRet = D_OK;

	dRet = this->Schedule( pTimerNode );

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Schedule( TIMERNODE pTimerNode )
{
	D_CHECK_EX( NULL != pTimerNode, "", return D_ERROR_NULL_POINTER );

	DResult dRet = D_OK;

	m_nodeList.Add( pTimerNode );

	this->Sort();

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
void CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::FreeNode( CDTimeNodeT<TIMERTYPE, TYPE>*& pTimerNode )
{
	D_LOG_CRITICAL( NULL != pTimerNode );

	pTimerNode->OnDestory();

	pTimerNode = NULL;
}

template< class TIMERTYPE, class TYPE, class LOCK>
int CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::UpdateTimerNode( 
	TIMERNODE pTimerNode )
{
	D_CHECK_EX( NULL != pTimerNode, "", return -1 );

	pTimerNode->SetTimeTick( m_timerTick );

	return 0;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Dispatch( 
	CDTimeNodeT<TIMERTYPE, TYPE> * pTimerNode )
{
	D_CHECK_EX( NULL != pTimerNode, "", return D_ERROR_NULL_POINTER );

	DResult dRet = D_OK;

	dRet = pTimerNode->OnTimer();

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::SetTimerNode(
	TIMERNODE pTimerNode,
	TIMERTYPE pTimerType,
	TYPE pType,
	const CDTimeValue& delay,
	const CDTimeValue& interval,
	int runtimes )
{
	DResult dRet = D_OK;

	this->UpdateReferenceTimeTick();

	DWORD delaySec = delay.GetSecond();
	DWORD intervalSec = interval.GetSecond();

	// 判断delay和interval不能超过49.7天，也就是4294967295毫秒，超过就返回
	if ( delaySec > TIME_TICK_MAX || intervalSec > TIME_TICK_MAX )
	{
		return D_ERROR_FAILURE;
	}

	DWORD intervalTickCount = interval.GetMSecond();
#if defined( D_FORCE_TIME_MIN_VALUE )
	if ( intervalTickCount < 50 )
	{
		intervalTickCount = TIME_TICK_MIN;
	}
#endif

	dRet = pTimerNode->SetTimerNode(
		pTimerType,
		pTimerType,
		delay.GetMSecond(),
		intervalTickCount,
		runtimes );

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
CDTimerQueueT<TIMERTYPE, TYPE> CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::AllocNode()
{
	CDTimeNodeT<TIMERTYPE, TYPE>* pTimerNode = new CDTimeNodeT<TIMERTYPE, TYPE>();

	D_LOG_CRITICAL( NULL != pTimerNode );

	return pTimerNode;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::SetOwnerThread( DWORD dwThreadID )
{
	m_threadID = dwThreadID;

	return D_OK;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Start()
{
	DResult dRet = D_OK;

	CDMutexGuardT<LOCK> guard( &m_lock );

	m_queueStatus = QUEUE_START;

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Stop()
{
	DResult dRet = D_OK;

	CDMutexGuardT<LOCK> guard( &m_lock );

	m_queueStatus = QUEUE_STOP;

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
void CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Destory()
{
	delete this;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::GetEarliestInterVal( DWORD& dwTickCount )
{
	DResult dRet = D_OK;

	CDMutexGuardT<LOCK> guard( &m_lock );

	if ( 0 == m_nodeList.GetSize() )
	{
		dwTickCount = 0;

		return D_ERROR_NOT_FOUND;
	}

	var pTimerNode = m_nodeList.GetFirst();

	D_CHECK_EX( NULL != pTimerNode, "", return D_ERROR_NULL_POINTER );

	INT64 timeTick = pTimerNode->GetTimeTick();

	this->UpdateReferenceTimeTick();

	INT64 tick = m_timerTick - timeTick;
	dwTickCount = tick >= 0 ? tick : 0;

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Sort()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	std::greater<TIMERNODE> sortFunc;

	m_nodeList.GetList().sort( sortFunc );

	return D_OK;
}

template< class TIMERTYPE, class TYPE, class LOCK>
int CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Expire()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	if ( D_BIT_ENABLED( m_queueStatus, QUEUE_STOP ))
	{
		return D_ERROR_FAILURE;
	}

	if ( 0 == m_nodeList.GetSize() )
	{
		return 0;
	}

	int index = 0;

	CDTimeNodeT<TIMERTYPE, TYPE>* pTimerNode = NULL;

	for ( ; index < m_nodeList.GetSize(); ++index )
	{
		pTimerNode = m_nodeList.GetFirst();

		if ( NULL == pTimerNode )
		{
			return -1;
		}

		this->UpdateReferenceTimeTick();

		INT64 timeTick = pTimerNode->GetTimeTick();

		if ( timeTick > this->m_timerTick )
		{
			break;
		}

		m_nodeList.RemoveFirst();

		BOOL bFreeNode = FALSE;

		if ( 0 == pTimerNode->DecreaseRunTimes() )
		{
			bFreeNode = TRUE;
		}
		else
		{
			this->ReSchedule( pTimerNode );
		}

		this->Dispatch( pTimerNode );

		if ( bFreeNode )
		{
			this->FreeNode( pTimerNode );
		}
	}

	return index;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Cancle( TIMERTYPE pTimerType )
{
	DResult dRet = D_OK;

	CDMutexGuardT<LOCK> guard( &m_lock );

	var nodelist = m_nodeList.GetList();
	CDTimeNodeT<TIMERNODE, TYPE>* pTimerNode = NULL;

	BOOL bFound = FALSE;

	for ( var itorbegin = nodelist.begin(); itorbegin != nodelist.end(); )
	{
		pTimerNode = (*itorbegin);

		if ( pTimerNode == pTimerType->GetTimerType() )
		{
			bFound = TRUE;
			break;
		}

		itorbegin++;
	}

	if ( !bFound )
	{
		return dRet;
	}

	dRet = m_nodeList.Remove( pTimerNode );

	this->FreeNode( pTimerNode );

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
DResult CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::Schedule( TIMERTYPE pTimerType, TYPE pType, const CDTimeValue& delay, const CDTimeValue& interval, int runtimes /*= -1 */ )
{
	DResult dRet = D_OK;

	if ( 0 == runtimes )
	{
		return dRet;
	}

	D_CHECK_EX( NULL != pType && NULL != pTimerType, "", return D_ERROR_NULL_POINTER );

	CDMutexGuardT<LOCK> guard( &m_lock );

	if ( D_BIT_ENABLED( m_queueStatus, QUEUE_STOP ))
	{
		return D_ERROR_FAILURE;
	}

	this->Cancle( pTimerType );

	TIMERNODE pTimerNode = this->AllocNode();

	D_CHECK_EX( NULL != pTimerNode, "", return D_ERROR_NULL_POINTER );

	dRet = this->Schedule(
		pTimerNode,
		pTimerType,
		pType,
		delay,
		interval,
		runtimes );

	D_CHECK_EX( D_SUCCEEDED( dRet), "", return dRet );

	dRet = this->Schedule( pTimerNode );

	return dRet;
}

template< class TIMERTYPE, class TYPE, class LOCK>
CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::~CDTimerQueueT()
{

}

template< class TIMERTYPE, class TYPE, class LOCK>
CDTimerQueueT<TIMERTYPE, TYPE, LOCK>::CDTimerQueueT()
	: m_queueStatus( QUEUE_START )
	, m_threadID( (DWORD)-1 )
{

}

#endif	//_D_TIMER_QUEUE_T_

