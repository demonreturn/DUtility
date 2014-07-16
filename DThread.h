#ifndef _D_THREAD_H_
#define _D_THREAD_H_

#include "DBase.h"
#include "DDataStructure.h"

#include "DThreadMutex.h"

#include <functional>

class CDThread
{
public:
	virtual ~CDThread();

public:
	CDThread();

	/// �����߳�
	virtual bool Start();

	/// �ȴ�����
	void Join();

	/// ֱ���˳�
	void Terminate();

protected:
	virtual void Run(){}

private:
#ifdef D_WIN32
	static UINT D_STD_CALL			StartThread( LPVOID pArg );
#elif defined( D_LINUX)		// linux  ʵ��
	static void* D_STD_CALL			StartThread( LPVOID pArg );
#endif

protected:
	CDThread( const CDThread& );

	CDThread& operator = ( const CDThread& );

protected:
	D_THREAD_ID					m_id;

	D_THREAD_HANDLE				m_handle;
};

class CDCBThread : public CDThread
{
public:
	typedef std::function<void()> ThreadFunc;

	CDCBThread( const ThreadFunc& func )
		: m_func( func )
	{}

protected:
	virtual void Run()
	{
		m_func();
	}

private:
	ThreadFunc					m_func;
};


class IDEvent;
// �߳�����״̬
enum THRAD_STATUS
{
	THREAD_RUN = 1 << 1, // �߳�����
	THREAD_STOP = 1 << 2 // �߳�ֹͣ
};

// �߳����ͣ��û��̺߳������̣߳��ϲ��û��߳�����
enum THREAD_CREATE_TYPE
{
	THREAD_NO_TYPE = 0,
	THREAD_USER_TYPE,
	THREAD_NET_TYPE
};

// �������
typedef CDTimerQueueT<CDTimer*, IDTimerSink*, CDThreadMutex> CDTimerQueue;
typedef CDEventQueueT<IDEvent*, CDThreadMutex> CDEventQueue;

class CDThreadBase;

class IDThreadSink
{
public:
	virtual VOID OnThreadRun( CDThreadBase* threadID ) = 0;
	virtual VOID OnThreadStop( CDThreadBase* threadID ) = 0;
};

class CDThreadBase
{
public:
	friend class CDThreadManager;

public:
	CDThreadBase(
		DWORD dwThreadDefineType = (DWORD)-1,
		IDThreadSink* pThreadSink = NULL,
		THREAD_BLOCK_TYPE blockType = THREAD_BLOCK );

	virtual DResult ScheduleTimer(
		CDTimer* pTimer,
		IDThreadSink* pSink,
		const CDTimeValue& delay,
		const CDTimeValue& interval,
		int runTimes = -1 );

	virtual DResult CancleTimer( CDTimer* pTimer );

	virtual DResult SetTimerQueue( CDTimerQueue* pTimerQueue );

	virtual CDTimerQueue* GetTimerQueue();

	// �첽
	virtual DResult PostEvent( IDEvent* pEvent );

	// ͬ��
	virtual DResult SendEvent( IDEvent* pEvent );

	virtual DResult SetEventQueue( CDEventQueue* pEventQueue );

	virtual CDEventQueue* GetEventQueue();

	virtual DResult HeartBeat();

	DResult SetThreadSink( IDThreadSink* pSink );

	/*
	* ������	�ȴ��̣߳�����߳�״̬�����Ƿ��ڻ�����ܵȴ��Լ�
	*			�ȴ��ɹ����ر��߳̾��
	* ����ֵ��	D_OK �ɹ��� ���� ʧ��
	*/
	DResult Join();

	DResult Join( const CDTimeValue& timeout );

	/*
	* ������	����������һ���߳�,ֻ�������������
	* ����ֵ��	D_OK �ɹ��� ���� ʧ��
	*/
	virtual DResult Activate();/*long flags = THR_NEW_LWP | THR_JOINABLE |THR_INHERIT_SCHED*/

	D_THREAD_ID GetThreadID();

	/*
	* ������	����û��������ͣ�1 �� 1000Ϊ�ײ㶨�巶Χ��1000����Ϊ�ϲ��û����巶Χ
	* ����ֵ��	�Զ���ID
	*/
	DWORD GetDefineThreadID();

	/*
	* ������	�����������
	* ����ֵ��	��������
	*/
	THREAD_BLOCK_TYPE GetBlockType();

	VOID SetBlockType( THREAD_BLOCK_TYPE blockType );

	THREAD_CREATE_TYPE GetCreateType();

	VOID SetCreateType( THREAD_CREATE_TYPE createType = THREAD_NET_TYPE );

	BOOL IsDestroyed();

	/*
	* �����������߳�ID�����ڵ�ǰ���ǵ��û��߳��ǽ����ϲ�����̣߳�����
	*		������Ҫ��������ģʽ�����ʱ��û���߳�ID����Ҫ���ý���
	*		���Ƕ��ڷ�����ģʽ�ģ����Ի�ã��������ֻ�����̹߳�����
	*		���е��ã�����ֻ���ڽ��õ�����������µ��á���ǰֻ����
	*		CScThreadManager::CreateUserThread��
	*/
	VOID SetThreadID( DWORD dwThreadID );
	VOID SetThreadHandle( D_THREAD_HANDLE threadHandle );

protected:
	virtual VOID OnThreadRun();

	virtual VOID OnThreadStop();

	virtual INT Destroy();

	DResult TerminateThread();

#ifdef D_WIN32
	static UINT D_STD_CALL ThreadEntry( LPVOID pArg );

#elif defined( D_LINUX )
	static void* D_STD_CALL ThreadEntry( LPVOID pArg );

#endif	// D_WIN32

	virtual ~CDThreadBase();

protected:

	IDThreadSink*				m_pSink;

	DWORD						m_dwThreadID;

	D_THREAD_HANDLE				m_hThread;

	// �̶߳��������ͣ���ܲ㶨�壺1 �� 1000�� �ϲ㶨�壺1000����
	// ��ʼ��ΪDWORD(-1)����ʾ��Ч
	DWORD						m_nThreadDefineType;

	// �߳�ɾ����ʶλ�����˱�־λ�����Ժ󣬸��̶߳���ܾ�����TQ��EQ����ڵ�
	// ����ֹͣ��ɾ����Ӧ��
	BOOL						m_bDestroyed;

	// �߳�ɾ����ʶλ������
	CDThreadMutex				m_ThreadMutex;

	// ������־��Ĭ���������ģ�����������
	THREAD_BLOCK_TYPE			m_BlockType;

	THREAD_CREATE_TYPE			m_CreateType;

	// ʱ�����
	CDTimerQueue*				m_pTQ;

	// �¼�����
	CDEventQueue*				m_pEQ;
};
#endif	// _D_THREAD_H_

