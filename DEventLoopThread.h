
#ifndef _D_EVENT_LOOP_THREAD_H_
#define _D_EVENT_LOOP_THREAD_H_

#include "DBase.h"
#include "DThread.h"
#include "DAutoEvent.h"

class CDEventLoopRunnable;
class CDEventLoopThread : public CDThread
{
public:
	typedef INT64									TimerHandle;
	typedef std::function<void()>					EventCallBack;
	typedef std::function<void (TimerHandle) >		TimerCallBack;

	CDEventLoopThread();
	virtual ~CDEventLoopThread();

	virtual bool Start();

	virtual void Stop();

public:
	// �첽Ͷ��
	DResult Invoker( const EventCallBack& cb );

	// ͬ������
	DResult Call( const EventCallBack& cb );

	// ����ʱ�䣬 ʱ�䵥λ����
	TimerHandle SetTimer(
		const TimerCallBack& cb,
		UINT32 interval,
		UINT32 delay = 0,
		UINT32 runtimes = -1 );

	// �ر�ʱ��
	void KillTimer( TimerHandle timeHandle );

protected:
	virtual void Run();

private:
	CDEventLoopThread( const CDEventLoopThread& );
	void operator = ( const CDEventLoopThread& );

	std::shared_ptr<CDEventLoopRunnable>	m_runnable;
	CDAutoEvent								m_event;
};

#endif	// _D_EVENT_LOOP_THREAD_H_
