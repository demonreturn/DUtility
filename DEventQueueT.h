

#ifndef _D_EVENT_QUEUE_T_H_
#define _D_EVENT_QUEUE_T_H_

#include "DBase.h"

#include "DEventNodeT.h"
#include "DNodeList.h"
#include "DEventQueueStrategyT.h"
#include "DMutexGuardT.h"

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

	void PostEvent( CDEventNodeT<TYPE>* pEventNode );

private:
	typedef CDEventNodeT<EVENTNODE> CDNodeList;
	typedef CDEventQueueStrategyT<CDNodeList> CDEventQueueStrategy;

	LOCK							m_lock; // �����¼�����

	CDNodeList<EVENTNODE>			m_NodeList;// �¼��ڵ����,����ط���Ҫ�滻ΪIScNodeListT����̬new����������

	// ���п�����;��ֹͣ�¼����գ���QUEUE_START���¼����Խ��ղ�������QUEUE_STOP���¼�������Ҳ������
	UINT							m_QueueStatus;//QUEUE_STATUS

	BOOL							m_bQuit; // �ڴ�������¼�ʱ������

	CDEventQueueStrategy			m_EventQueueStrategy;// �������һ����Ա��ÿ�������Ա����ʱ�ڵ�洢
};


#endif	// _D_EVENT_QUEUE_T_H_

