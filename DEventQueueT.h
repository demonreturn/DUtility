

#ifndef _D_EVENT_QUEUE_T_H_
#define _D_EVENT_QUEUE_T_H_

#include "DBase.h"

#include "DEventNodeT.h"
#include "DNodeList.h"
#include "DEventQueueStrategyT.h"
#include "DMutexGuardT.h"

#include "DTrace.h"

class IDEvent
{
public:
	virtual ~IDEvent()
	{

	}

public:
	virtual int OnEvent() = 0;

	virtual int OnDestory()
	{
		delete this;

		return 0;
	}
};

template < class TYPE, class LOCK>
class CDEventQueueT
{
protected:
	typedef CDEventNodeT<TYPE>*		EVENTNODE;
public:
	CDEventQueueT();

	virtual DResult PostEvent( TYPE pType );

	DResult PostEvent( 
		TYPE pType,
		POSTSEND_TYPE psType,
		CDSyncAutoEvent* pSyncAutoEvent = NULL );

	virtual DResult HandleEvent( BOOL& bQuit );

	virtual DResult Sort();

	BOOL IsEmpty();

	void Destory();

	DResult Stop();

	DResult Start();

	/*
	* ������	���棺��Ͷ�����һ���¼�ʱ���ڲ�������ã��ⲿ��Ҫ�������������
	*			����m_bQuit��־
	*/
	void DestorySelf();

private:
	virtual ~CDEventQueueT();

	virtual DResult Dispatch( CDEventNodeT<TYPE>* pEventNode );

	virtual CDEventNodeT<TYPE>* AllocNode();

	virtual void FreeNode( CDEventNodeT<TYPE>*& pEventNode );

	DResult PostEvent( CDEventNodeT<TYPE>* pEventNode );

private:
	typedef CDNodeListT<EVENTNODE> CDNodeList;

	typedef CDEventQueueStrategyT<CDNodeList> CDEventQueueStrategy;

	LOCK							m_lock; // �����¼�����

	CDNodeListT<EVENTNODE>			m_NodeList;// �¼��ڵ����,����ط���Ҫ�滻ΪIScNodeListT����̬new����������

	// ���п�����;��ֹͣ�¼����գ���QUEUE_START���¼����Խ��ղ�������QUEUE_STOP���¼�������Ҳ������
	UINT							m_QueueStatus;//QUEUE_STATUS

	BOOL							m_bQuit; // �ڴ�������¼�ʱ������

	CDEventQueueStrategy			m_EventQueueStrategy;// �������һ����Ա��ÿ�������Ա����ʱ�ڵ�洢
};

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::PostEvent( CDEventNodeT<TYPE>* pEventNode )
{
	D_CHECK_EX( NULL != pEventNode, "", return D_ERROR_NULL_POINTER);

	m_NodeList.Add( pEventNode );

	return D_OK;
}

template < class TYPE, class LOCK>
void CDEventQueueT<TYPE, LOCK>::FreeNode( CDEventNodeT<TYPE>*& pEventNode )
{
	D_CHECK_EX( NULL != pEventNode, "", return );

	pEventNode->OnDestory();

	pEventNode = NULL;
}

template < class TYPE, class LOCK>
CDEventNodeT<TYPE>* CDEventQueueT<TYPE, LOCK>::AllocNode()
{
	CDEventNodeT<TYPE>* pEventNode = new CDEventNodeT<TYPE>();

	D_CHECK_EX( NULL != pEventNode, "", return NULL );

	return pEventNode;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::Dispatch( CDEventNodeT<TYPE>* pEventNode )
{
	D_CHECK_EX( NULL != pEventNode, "", return D_ERROR_NULL_POINTER );

	pEventNode->OnEvent();

	return D_OK;
}

template < class TYPE, class LOCK>
void CDEventQueueT<TYPE, LOCK>::DestorySelf()
{
	m_bQuit = TRUE;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::Start()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	m_QueueStatus = QUEUE_START;

	return D_OK;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::Stop()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	m_QueueStatus = QUEUE_STOP;

	return D_OK;
}

template < class TYPE, class LOCK>
void CDEventQueueT<TYPE, LOCK>::Destory()
{
	delete this;
}

template < class TYPE, class LOCK>
BOOL CDEventQueueT<TYPE, LOCK>::IsEmpty()
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	if ( 0 == m_NodeList.GetSize() )
	{
		return TRUE;
	}

	return FALSE;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::Sort()
{
	m_NodeList.GetList().sort();

	return D_OK;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::HandleEvent( BOOL& bQuit )
{
	if ( D_BIT_ENABLED( m_QueueStatus, QUEUE_STOP ) )
	{
		return D_ERROR_FAILURE;
	}

	DResult dRet = D_OK;
	bQuit = FALSE;

	if ( m_bQuit )
	{
		bQuit = TRUE;
	}

	int listSize = m_NodeList.GetSize();

	if ( 0 == listSize )
	{
		return dRet;
	}

	CDNodeList* pTempNodeList = NULL;
	{
		CDMutexGuardT<LOCK> guard( &m_lock );
		pTempNodeList = m_EventQueueStrategy.GetEventQueue( m_NodeList );
	}

	int cycleNum = pTempNodeList->GetSize();

	CDEventNodeT<TYPE>* pEventNode = NULL;
	for ( int index = 0; index < cycleNum; ++index )
	{
		pEventNode = pTempNodeList->GetFirst();

		D_CHECK_EX( NULL != pEventNode, "", return D_OK );

		pTempNodeList->RemoveFirst();

		this->Dispatch( pEventNode );

		this->FreeNode( pEventNode );
	}

	pTempNodeList = NULL;

	return dRet;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::PostEvent( 
	TYPE pType,
	POSTSEND_TYPE psType,
	CDSyncAutoEvent* pSyncAutoEvent /*= NULL */ )
{
	CDMutexGuardT<LOCK> guard( &m_lock );

	if ( D_BIT_ENABLED( m_QueueStatus, QUEUE_STOP ) )
	{
		return D_ERROR_FAILURE;
	}

	CDEventNodeT<TYPE>* pEventNode = this->AllocNode();

	if ( NULL == pEventNode )
	{
		return D_ERROR_FAILURE;
	}

	pEventNode->SetEventNode( pType, psType );
	if ( SENDEVENT == psType )
	{
		pEventNode->SetSyncEvent( pSyncAutoEvent );
	}

	DResult dRet = D_OK;

	dRet = this->PostEvent( pEventNode );

	return dRet;
}

template < class TYPE, class LOCK>
DResult CDEventQueueT<TYPE, LOCK>::PostEvent( TYPE pType )
{
	D_ASSERT( NULL != pType );
	DResult dRet = D_OK;

	dRet = this->PostEvent( pType, POSTEVENT );

	return dRet;
}

template < class TYPE, class LOCK>
CDEventQueueT<TYPE, LOCK>::~CDEventQueueT()
{

}

template < class TYPE, class LOCK>
CDEventQueueT<TYPE, LOCK>::CDEventQueueT()
	: m_QueueStatus( QUEUE_START )
	, m_bQuit( FALSE )
{

}


#endif	// _D_EVENT_QUEUE_T_H_

