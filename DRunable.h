
#ifndef _D_RUN_ABLE_H_
#define _D_RUN_ABLE_H_

#include "DBase.h"

#include <memory>
#include <functional>



class CDEventLoop
{
public:
	typedef INT64						TimerHandle;
	typedef std::function<void()>		EventCallBack;
	typedef std::function<void(INT64)>	TimerCallBack;

	typedef std::shared_ptr<CDEventLoop>	EventLoopSharedPtr;

	static const TimerHandle INVALID_TIME_HANDLE;
public:
	CDEventLoop();
	~CDEventLoop();

	DResult Loop();

	void Quit();

	// “Ï≤Ω
	DResult Invoker( const EventCallBack& cb );

	// Õ¨≤Ω
	DResult Call( const EventCallBack& cb );

	TimerHandle SetTimer(
		const TimerCallBack& cb,
		UINT32 interval,
		UINT32 delay = 0,
		UINT32 runtimes = -1 );

	void CloseTimerHandle( TimerHandle timeHandle );

	D_THREAD_ID GetEventLoopThread();

private:
	void SetTimerImpl( const TimerHandle& timeHandle );

	void CancleTimerImpl( const TimerHandle& timeHandle );

	CDEventLoop( const CDEventLoop& );
	CDEventLoop& operator = ( const CDEventLoop& );

	class CDEvemtLoopImpl;

	CDEvemtLoopImpl*				m_impl;

	std::set<TimerHandle>			m_timers;

};

class CDRunable
{
public:
	CDRunable(){}
	 virtual ~CDRunable(){}

	 virtual void Run() {}

	 virtual void Stop() {}

private:
	CDRunable( const CDRunable& );
	CDRunable& operator = ( const CDRunable& );
};

class CDEventLoopRunable
	: public CDRunable
{
public:
	CDEventLoopRunable();
	virtual ~CDEventLoopRunable();

	virtual void Run();

	virtual void Stop();

	CDEventLoop::EventLoopSharedPtr GetEventLoop() const
	{
		return m_eventloop;
	}

private:
	CDEventLoop::EventLoopSharedPtr		m_eventloop;
};

class CDCBRunable
	: public CDRunable
{
public:
	typedef std::function<void()>	ThreadFunc;
	CDCBRunable( const ThreadFunc& func )
	{

	}

	virtual void Run()
	{
		if ( !m_fun._Empty() )
		{
			m_fun();
		}
	}

	virtual void Stop()
	{
	}

private:
	CDCBRunable();

	ThreadFunc					m_fun;
};

#endif	// _D_RUN_ABLE_H_

