

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
	* 描述：	警告：在投递最后一个事件时由内部自身调用，外部不要调用这个函数。
	*			设置m_bQuit标志
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

	LOCK							m_lock; // 保护事件队列

	CDNodeList<EVENTNODE>			m_NodeList;// 事件节点队列,这个地方需要替换为IScNodeListT，动态new出来，问题

	// 队列可能中途会停止事件接收，在QUEUE_START下事件可以接收并处理，在QUEUE_STOP下事件不接收也不处理
	UINT							m_QueueStatus;//QUEUE_STATUS

	BOOL							m_bQuit; // 在处理结束事件时被设置

	CDEventQueueStrategy			m_EventQueueStrategy;// 里面存在一个成员，每次这个成员作临时节点存储
};


#endif	// _D_EVENT_QUEUE_T_H_

