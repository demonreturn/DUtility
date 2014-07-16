
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
	* Reactor������ģʽ
	* Reacotr��ʼ��ʱʹ��
	*/
	enum REACTOR_RUN_TYPE
	{
		REACTOR_IDLE = 0,
		REACTOR_LOOP = 1,
		REACTOR_CALL = (1 << 1)
	};

	/*
	* Reactor��֪ͨ����
	*/
	enum REACTOR_NOTIFY_CMD
	{
		REACTOR_NOTIFY_WAKEUP = 1,
		REACTOR_NOTIFY_EXIT = (1 << 1)
	};

	/*
	* Reactor������״̬
	*/
	enum REACTOR_RUN_STATE
	{
		REACTOR_RUNNING,
		REACTOR_HALTING
	};

	/*
	* Reactor֧�ֵ��¼����ͣ���������ֵͬACE����
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
		ABANDONED_MASK	= ( 1 << 6 ),				// WFMO	Reactor ����
		ACTIVE_MASK		= READ_MASK | 
						  WRITE_MASK,		// WFMO Reactor ����
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
	 * ����Reactor
	 * ��ʼ����Reactor����Ϣѭ����ʹ�俪ʼ�����¼������ܽ����¼�����
	 * �ú����ܱ���ε��ã�����ͬʱ������̵߳��ã�ֻ�е�һ�������̻߳�ִ�гɹ��������Ķ���������
	 *  nRunType : REACTOR_RUN_TYPE
	 */
	DResult Run( int runType = REACTOR_LOOP );

	/*
	 * ��Reactor����֪ͨ,ֹͣ/����
	 */
	DResult Notify( int nNotifyCmd );

	/*
	 * �Ǽ�һ��Handler
	 * �Ǽ���ɺ�Reactor������Ϣѭ���в���Handler�������¼����������ص�
	 * �����ͬһ��Handler�ֶ�εǼǲ�ͬ���¼�
	 * pHandler : Handler����
	 * nEvent : Reactor��Ϣѭ����Ҫ������¼�
	 * pIndex : ����int��ָ�룬���صǼ���ɺ󷵻ص��������������NULL�����ʾ�ⲿ����������
	 */
	DResult RegisterHandler(IDHandler* pHandler,int nEvent,int* pIndex);

	/*
	 * ע��һ��Handler
	 * ע����ɺ�Reactor�����ٲ��񵽸�Handler��Ӧ���¼�
	 * �����ͬһ��Handler�ֶ��ע����ͬ���¼�
	 * pHandler : Handler����
	 * nEvent : Reactor��Ϣѭ����Ҫ������¼�
	 * pIndex : ����int��ָ�룬��ʾ�ⲿָ���˸�Handler��Ӧ������������NULL�����ʾ�ⲿ�޷�ָ������
	 */
	DResult UnRegisterHandler(IDHandler* pHandler,int nEvent,int* pIndex);

	/*
	 * ����TimerQueue����
	 */
	DResult AttachTimerQueue(CDTimerQueue* pTQ);

	/*
	 * ����EventQueue����
	 */
	DResult AttachEventQueue(CDEventQueue* pEQ);

protected:
	DResult Loop();

	CDMutex						m_hLock;

	IDReacotrImpl*				m_pReactorImpl;

	int							m_reactorRunType;
};

#endif	// _D_REACTOR_H_

