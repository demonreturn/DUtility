

#ifndef _D_EVENT_QUEUE_STRATEGY_H_
#define _D_EVENT_QUEUE_STRATEGY_H_

#include "DBase.h"
#include "DNodeList.h"

template < class QUEUETYPE>
class IDEventQueueStrategyT
{
public:
	virtual ~IDEventQueueStrategyT(){}

	virtual QUEUETYPE* GetEventQueue( QUEUETYPE& dQueue ) = 0;
};

#define EVENT_QUEUE_SIZE 150 // 默认处理的事件队列的个数为150个 
#define EVENT_QUEUE_STEP 100 // 每次事件队列处理增长的步长

template < class QUEUETYPE>
class CDEventQueueStrategyT
	: public IDEventQueueStrategyT<QUEUETYPE>
{
public:
	CDEventQueueStrategyT();

	virtual ~CDEventQueueStrategyT();

// common functions 
public:
	virtual QUEUETYPE* GetEventQueue( QUEUETYPE& dQueue );

protected:
	DWORD CalculateCurrentHandleNum( QUEUETYPE& scQueue );

private:

	DWORD						m_dwLastHandledNum; // 上次事件队列的长度
	DWORD						m_dwCurrentHandleNum; // 本次要处理事件队列的长度

	// 临时事件队列，用来保存从事件队列中根据策略获取出来的，需要被处理的队列
	QUEUETYPE					m_Queue;
};

template < class QUEUETYPE>
DWORD CDEventQueueStrategyT<QUEUETYPE>::CalculateCurrentHandleNum( QUEUETYPE& scQueue )
{
	// 当前先采取默认的，后期更新
	return EVENT_QUEUE_SIZE;

	//// 获得当前的事件队列的事件个数
	//m_dwCurrentHandleNum = queue.Size();

	//if ( m_dwCurrentHandleNum >= m_dwLastHandledNum )
	//{
	//	m_dwLastHandledNum += EVENT_QUEUE_STEP;

	//	m_dwLastHandledNum = ( m_dwLastHandledNum > m_dwCurrentHandleNum ) ? m_dwCurrentHandleNum : m_dwLastHandledNum;
	//}
	//else
	//{
	//	m_dwLastHandledNum = m_dwCurrentHandleNum;
	//}

	//return m_dwLastHandledNum;
}

template < class QUEUETYPE>
QUEUETYPE* CDEventQueueStrategyT<QUEUETYPE>::GetEventQueue( QUEUETYPE& dQueue )
{
	m_Queue.Clear();

	DWORD nCount = this->CalculateCurrentHandleNum( dQueue );

	for (DWORD index = 0; index < nCount; index++)
	{
		if ( NULL == dQueue.GetFirst() )
		{
			break;
		}

		m_Queue.Add( dQueue.GetFirst() );

		dQueue.RemoveFirst();
	}

	return &m_Queue;
}

template < class QUEUETYPE>
CDEventQueueStrategyT<QUEUETYPE>::~CDEventQueueStrategyT()
{

}

template < class QUEUETYPE>
CDEventQueueStrategyT<QUEUETYPE>::CDEventQueueStrategyT()
	: m_dwLastHandledNum( 150 )
	, m_dwCurrentHandleNum( 0 )
{

}

#endif	// _D_EVENT_QUEUE_STRATEGY_H_

