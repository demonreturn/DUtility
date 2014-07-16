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

	/// 启动线程
	virtual bool Start();

	/// 等待结束
	void Join();

	/// 直接退出
	void Terminate();

protected:
	virtual void Run(){}

private:
#ifdef D_WIN32
	static UINT D_STD_CALL			StartThread( LPVOID pArg );
#elif defined( D_LINUX)		// linux  实现
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
// 线程运行状态
enum THRAD_STATUS
{
	THREAD_RUN = 1 << 1, // 线程运行
	THREAD_STOP = 1 << 2 // 线程停止
};

// 线程类型，用户线程和网络线程，上层用户线程类型
enum THREAD_CREATE_TYPE
{
	THREAD_NO_TYPE = 0,
	THREAD_USER_TYPE,
	THREAD_NET_TYPE
};

// 定义队列
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

	// 异步
	virtual DResult PostEvent( IDEvent* pEvent );

	// 同步
	virtual DResult SendEvent( IDEvent* pEvent );

	virtual DResult SetEventQueue( CDEventQueue* pEventQueue );

	virtual CDEventQueue* GetEventQueue();

	virtual DResult HeartBeat();

	DResult SetThreadSink( IDThreadSink* pSink );

	/*
	* 描述：	等待线程，检查线程状态，看是否还在活动，不能等待自己
	*			等待成功，关闭线程句柄
	* 返回值：	D_OK 成功， 其他 失败
	*/
	DResult Join();

	DResult Join( const CDTimeValue& timeout );

	/*
	* 描述：	创建并激活一条线程,只能主动对象调用
	* 返回值：	D_OK 成功， 其他 失败
	*/
	virtual DResult Activate();/*long flags = THR_NEW_LWP | THR_JOINABLE |THR_INHERIT_SCHED*/

	D_THREAD_ID GetThreadID();

	/*
	* 描述：	获得用户定义类型，1 ～ 1000为底层定义范围，1000以上为上层用户定义范围
	* 返回值：	自定义ID
	*/
	DWORD GetDefineThreadID();

	/*
	* 描述：	获得阻塞类型
	* 返回值：	阻塞类型
	*/
	THREAD_BLOCK_TYPE GetBlockType();

	VOID SetBlockType( THREAD_BLOCK_TYPE blockType );

	THREAD_CREATE_TYPE GetCreateType();

	VOID SetCreateType( THREAD_CREATE_TYPE createType = THREAD_NET_TYPE );

	BOOL IsDestroyed();

	/*
	* 描述：设置线程ID，由于当前我们的用户线程是借用上层的主线程，对于
	*		我们需要创建阻塞模式的这个时候没有线程ID，需要设置进来
	*		但是对于非阻塞模式的，可以获得，这个设置只能在线程管理中
	*		进行调用，并且只能在借用的阻塞的情况下调用。当前只限于
	*		CScThreadManager::CreateUserThread中
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

	// 线程对象定义类型，框架层定义：1 ～ 1000， 上层定义：1000以上
	// 初始化为DWORD(-1)，表示无效
	DWORD						m_nThreadDefineType;

	// 线程删除标识位，当此标志位设置以后，该线程对象拒绝在向TQ或EQ插入节点
	// 并且停止和删除反应器
	BOOL						m_bDestroyed;

	// 线程删除标识位保护段
	CDThreadMutex				m_ThreadMutex;

	// 阻塞标志，默认是阻塞的，即主动对象
	THREAD_BLOCK_TYPE			m_BlockType;

	THREAD_CREATE_TYPE			m_CreateType;

	// 时间队列
	CDTimerQueue*				m_pTQ;

	// 事件队列
	CDEventQueue*				m_pEQ;
};
#endif	// _D_THREAD_H_

