
#ifndef _D_REACTOR_H_
#define _D_REACTOR_H_

#include "DBase.h"
#include "DMutex.h"

#include "IDReactorImpl.h"
class IDHandler;

class CDReactor
{
public:
	/*
	* Reactor的运行模式
	* Reacotr初始化时使用
	*/
	enum REACTOR_RUN_TYPE
	{
		REACTOR_IDLE = 0,
		REACTOR_LOOP = 1,
		REACTOR_CALL = (1 << 1)
	};

	/*
	* Reactor的通知类型
	*/
	enum REACTOR_NOTIFY_CMD
	{
		REACTOR_NOTIFY_WAKEUP = 1,
		REACTOR_NOTIFY_EXIT = (1 << 1)
	};

	/*
	* Reactor的运行状态
	*/
	enum REACTOR_RUN_STATE
	{
		REACTOR_RUNNING,
		REACTOR_HALTING
	};

	/*
	* Reactor支持的事件类型，这里类型值同ACE兼容
	*/
	enum REACTOR_EVENT_TYPE
	{
		NULL_MASK		= 0,
		READ_MASK		= (1 << 0),
		WRITE_MASK		= (1 << 1),
		EXCEPT_MASK		= (1 << 2),
		ACCEPT_MASK		= (1 << 3),
		CONNECT_MASK	= (1 << 4),
		CLOSE_MASK		= (1 << 5),
		ABANDONED_MASK	= ( 1 << 6 ),				// WFMO	Reactor 新增
		ACTIVE_MASK		= READ_MASK | 
						  WRITE_MASK,		// WFMO Reactor 新增
		ALL_EVENTS_MASK = READ_MASK |
						  WRITE_MASK |
						  EXCEPT_MASK |
						  ACCEPT_MASK |
						  CONNECT_MASK |
						  CLOSE_MASK | 
						  ABANDONED_MASK,
		RWE_MASK		= READ_MASK |
						  WRITE_MASK |
						  EXCEPT_MASK
	};

	CDReactor( IDReacotrImpl* pReactorImpl );

	virtual ~CDReactor();

	/*
	 * 运行Reactor
	 * 开始启动Reactor的消息循环，使其开始捕获事件，并能进行事件分派
	 * 该函数能被多次调用，但若同时被多个线程调用，只有第一个调用线程会执行成功，其他的都将被阻塞
	 *  nRunType : REACTOR_RUN_TYPE
	 */
	DResult Run( int runType = REACTOR_LOOP );

	/*
	 * 向Reactor发送通知,停止/唤醒
	 */
	DResult Notify( int nNotifyCmd );

	/*
	 * 登记一个Handler
	 * 登记完成后，Reactor会在消息循环中捕获Handler触发的事件，并触发回调
	 * 允许对同一个Handler分多次登记不同的事件
	 * pHandler : Handler对象
	 * nEvent : Reactor消息循环需要捕获的事件
	 * pIndex : 传入int型指针，返回登记完成后返回的索引，如果传入NULL，则表示外部不关心索引
	 */
	DResult RegisterHandler(IDHandler* pHandler,int nEvent,int* pIndex);

	/*
	 * 注销一个Handler
	 * 注销完成后，Reactor不会再捕获到该Handler对应的事件
	 * 允许对同一个Handler分多次注销不同的事件
	 * pHandler : Handler对象
	 * nEvent : Reactor消息循环需要捕获的事件
	 * pIndex : 传入int型指针，表示外部指明了该Handler对应的索引，传入NULL，则表示外部无法指明索引
	 */
	DResult UnRegisterHandler(IDHandler* pHandler,int nEvent,int* pIndex);

	/*
	 * 附加TimerQueue对象
	 */
	DResult AttachTimerQueue(CDTimerQueue* pTQ);

	/*
	 * 附加EventQueue对象
	 */
	DResult AttachEventQueue(CDEventQueue* pEQ);

protected:
	DResult Loop();

	CDMutex						m_hLock;

	IDReacotrImpl*				m_pReactorImpl;

	int							m_reactorRunType;
};

#endif	// _D_REACTOR_H_

