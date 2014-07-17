

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

#define EVENT_QUEUE_SIZE 150 // Ĭ�ϴ�����¼����еĸ���Ϊ150�� 
#define EVENT_QUEUE_STEP 100 // ÿ���¼����д��������Ĳ���

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

	DWORD						m_dwLastHandledNum; // �ϴ��¼����еĳ���
	DWORD						m_dwCurrentHandleNum; // ����Ҫ�����¼����еĳ���

	// ��ʱ�¼����У�����������¼������и��ݲ��Ի�ȡ�����ģ���Ҫ������Ķ���
	QUEUETYPE					m_Queue;
};

template < class QUEUETYPE>
DWORD CDEventQueueStrategyT<QUEUETYPE>::CalculateCurrentHandleNum( QUEUETYPE& scQueue )
{
	// ��ǰ�Ȳ�ȡĬ�ϵģ����ڸ���
	return EVENT_QUEUE_SIZE;

	//// ��õ�ǰ���¼����е��¼�����
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

