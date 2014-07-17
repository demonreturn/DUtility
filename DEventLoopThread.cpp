
#include "DEventLoopThread.h"
#include "DTimeValue.h"

CDEventLoopThread::CDEventLoopThread()
	//: m_runnable( new CDEventLoopRunnable() )
{
}

CDEventLoopThread::~CDEventLoopThread()
{
	//m_runnable = NULL;
}

bool CDEventLoopThread::Start()
{
	if ( CDThread::Start() )
	{
		static const CDTimeValue WAIT_TIME(1, 0);

		m_event.Wait( WAIT_TIME );

		return true;
	}

	return false;
}

void CDEventLoopThread::Stop()
{
	//m_runnable->Stop();

	CDThread::Join();
}

void CDEventLoopThread::Run()
{
	m_event.Signal();

	//m_runnable->Run();
}

DResult CDEventLoopThread::Invoker( const EventCallBack& cb )
{
	//cde

	return D_OK;
}
