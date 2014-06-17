
#include "DTimeWatch.h"

CDTimeWatch::CDTimeWatch()
	: m_bRunning(false)
	, m_start(0)
	, m_elapsed(0)
{
}

CDTimeWatch::CDTimeWatch( const CDTimeWatch& right )
	: m_bRunning(right.m_bRunning)
	, m_start(right.m_start)
	, m_elapsed(right.m_elapsed)
{

}

CDTimeWatch::~CDTimeWatch()
{
}

CDTimeWatch& CDTimeWatch::operator=( const CDTimeWatch& right )
{
	if ( &right != this )
	{
		this->m_bRunning = right.m_bRunning;
		this->m_elapsed = right.m_bRunning;
		this->m_start = right.m_start;
	}

	return *this;
}

void CDTimeWatch::Start()
{
	if ( !m_bRunning )
	{
		m_start = CDTimeWatch::GetTickCount();
		m_bRunning = true;
	}
}

void CDTimeWatch::Stop()
{
	if ( m_bRunning )
	{
		m_elapsed += CDTimeWatch::GetTickCount() - m_start;
		m_bRunning = false;
	}
}

void CDTimeWatch::Reset()
{
	m_elapsed = 0;
	m_start = 0;
	m_bRunning = false;
}

void CDTimeWatch::Restart()
{
	Reset();
	Start();
}

INT64 CDTimeWatch::Elapsed() const
{
	if ( m_bRunning )
	{
		return m_elapsed + ( CDTimeWatch::GetTickCount() - m_start );
	}

	return m_elapsed;
}

TIME32_S CDTimeWatch::ElapsedSeconds() const
{
	return TIME32_S( Elapsed() / (1000 * 1000));
}

TIME64_MS CDTimeWatch::ElapsedMillisconds() const
{
	return TIME32_S( Elapsed() / 1000 );
}

INT64 CDTimeWatch::GetTickCount()
{
#ifdef D_WIN32
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency( &frequency );

	LARGE_INTEGER timeCount;
	QueryPerformanceCounter( &timeCount );

	// 返回微秒精度
	return (INT64)( timeCount.QuadPart * 1000000 / frequency.QuadPart );

#elif defined( D_LINUX)		// linux  实现
#error not supported yet
#endif
}
