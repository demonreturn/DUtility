
#include "DTimeStamp.h"

CDTimeStamp::CDTimeStamp()
{
	Refresh();
}

CDTimeStamp::CDTimeStamp( TTimeValue tv )
	: m_ts( tv )
{

}

CDTimeStamp::CDTimeStamp( const CDTimeStamp& src )
{
	m_ts = src.m_ts;
}

CDTimeStamp::CDTimeStamp( const timeval& tv )
{
	m_ts = tv.tv_sec * 1000 * 1000 + tv.tv_usec * 1000;
}

CDTimeStamp::~CDTimeStamp()
{
}

void CDTimeStamp::Refresh()
{
#ifdef D_WIN32
	FILETIME ft;
	::GetSystemTimeAsFileTime( &ft );

	// (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	ULARGE_INTEGER lg;
	lg.LowPart = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart = ft.dwLowDateTime;
	ts.HighPart = ft.dwHighDateTime;
	ts.QuadPart -= lg.QuadPart;

	m_ts = ts.QuadPart / 10;
#elif defined( D_LINUX)		// linux  实现
	struct timeval tv;
	if ( !gettimeofday( &tv, NULL ))
	{
		m_ts = TTimeValue(tv.tv_sec) * resolution() + tv.tv_usec;
	}
	else
	{
		m_ts = 0;
	}
#endif
}

std::time_t CDTimeStamp::GetTime() const
{
	return std::time_t( m_ts / Resolution() );
}

CDTimeStamp::TTimeValue CDTimeStamp::GetUtcTime() const
{
	return m_ts * 10 + (TTimeDiff(0x01b21dd2) << 32) + 0x13814000;
}

CDTimeStamp::TTimeValue CDTimeStamp::GetMicroseconds() const
{
	return m_ts;
}

CDTimeStamp::TTimeDiff CDTimeStamp::GetElapsed() const
{
	CDTimeStamp now;
	return now - *this;
}

void CDTimeStamp::ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const
{
	// (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	ULARGE_INTEGER lg;
	lg.LowPart  = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.QuadPart = m_ts * 10;
	ts.QuadPart += lg.QuadPart;

	fileTimeLow = ts.LowPart;
	fileTimeHigh = ts.HighPart;
}

bool CDTimeStamp::IsTimeElapsed( TTimeDiff interval ) const
{
	CDTimeStamp now;
	TTimeDiff diff = now - *this;

	return diff >= interval;
}

CDTimeStamp CDTimeStamp::FromEpochTime( std::time_t t )
{
	return CDTimeStamp( TTimeValue(t) * Resolution() );
}

CDTimeStamp CDTimeStamp::FromEpochMillisecond( TTimeValue tv )
{
	return CDTimeStamp( tv * 1000 );
}

CDTimeStamp CDTimeStamp::FromUTCTime( TTimeValue tv )
{
	tv -= (TTimeDiff(0x01b21dd2) << 32) + 0x13814000;
	tv /= 10;

	return CDTimeStamp( tv );
}

CDTimeStamp CDTimeStamp::FromFileTime( UINT32 fileTimeLow, UINT32 fileTimeHigh )
{
	ULARGE_INTEGER lg; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	lg.LowPart  = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = fileTimeLow;
	ts.HighPart = fileTimeHigh;
	ts.QuadPart -= lg.QuadPart;

	return CDTimeStamp(ts.QuadPart/10);
}

CDTimeStamp::TTimeValue CDTimeStamp::Resolution()
{
	return 1000000;
}

bool CDTimeStamp::operator==( const CDTimeStamp& ts ) const
{
	return m_ts == ts.m_ts;
}

bool CDTimeStamp::operator!=( const CDTimeStamp& ts ) const
{
	return m_ts != ts.m_ts;
}

bool CDTimeStamp::operator>( const CDTimeStamp& ts ) const
{
	return m_ts > ts.m_ts;
}

bool CDTimeStamp::operator>=( const CDTimeStamp& ts ) const
{
	return m_ts >= ts.m_ts;
}

bool CDTimeStamp::operator<( const CDTimeStamp& ts ) const
{
	return m_ts < ts.m_ts;
}

bool CDTimeStamp::operator<=( const CDTimeStamp& ts ) const
{
	return m_ts <= ts.m_ts;
}

CDTimeStamp CDTimeStamp::operator+( TTimeDiff d ) const
{
	return CDTimeStamp( m_ts + d );
}

CDTimeStamp CDTimeStamp::operator-( TTimeDiff d ) const
{
	return CDTimeStamp( m_ts - d );
}

CDTimeStamp::TTimeDiff CDTimeStamp::operator-( const CDTimeStamp& ts ) const
{
	return m_ts - ts.m_ts;
}

CDTimeStamp& CDTimeStamp::operator+=( TTimeDiff d )
{
	m_ts += d;

	return *this;
}

CDTimeStamp& CDTimeStamp::operator-=( TTimeDiff d )
{
	m_ts -= d;

	return *this;
}

CDTimeStamp& CDTimeStamp::operator=( const CDTimeStamp& other )
{
	m_ts = other.m_ts;

	return *this;
}

CDTimeStamp& CDTimeStamp::operator=( TTimeValue tv )
{
	m_ts = tv;

	return *this;
}

DWORD CDTimeStamp::GetMSSeconds() const
{
	return m_ts / 1000;
}

CDTimeStamp CDTimeStamp::GetCurTime()
{
#ifdef D_WIN32
	FILETIME ftime;
	::GetSystemTimeAsFileTime( &ftime );

	return CDTimeStamp::FromFileTime( (UINT32)ftime.dwLowDateTime,
		(UINT32)ftime.dwHighDateTime );
#elif defined( D_LINUX)		// linux  实现
	timeval tvCur;
	::gettimeofday( 
		&tvCur, 
		NULL );

	return CDTimeStamp( tvCur );
#endif
}

