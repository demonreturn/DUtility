#include "DTimeValue.h"


CDTimeValue CDTimeValue::GetTimeOfDay()
{
#if defined ( D_WIN32 )

	FILETIME   tfile;
	::GetSystemTimeAsFileTime( &tfile );

	return CDTimeValue( tfile );

	// 添加linux下的实现
#elif defined ( D_LINUX )
	timeval tvCur;
	::gettimeofday( 
		&tvCur, 
		NULL );

	return CDTimeValue( tvCur );

#endif
}

CDTimeValue::CDTimeValue()
{
	this->Set( 
		0,
		0 );
}

CDTimeValue::CDTimeValue( 
	LONGLONG second, 
	LONG usecond )
{
	this->Set(
		second,
		usecond );
}

// 2010.10.27 added by 韦珂
// 补上遗漏的#ifdef
#ifdef D_WIN32
//  Initializes the CDTimeValue object from a Win32 FILETIME
CDTimeValue::CDTimeValue( const FILETIME &file_time )
{
	this->Set( file_time );
}

#endif	// D_WIN32

// 2010.10.27 added by 韦珂
// 补上遗漏的#ifdef
#ifdef D_WIN32

VOID CDTimeValue::Set( const FILETIME &file_time )
{
	//  Initializes the CDTimeValue object from a Win32 FILETIME
	// Don't use a struct initializer, gcc don't like it.
	ULARGE_INTEGER _100ns;
	_100ns.LowPart = file_time.dwLowDateTime;
	_100ns.HighPart = file_time.dwHighDateTime;

	_100ns.QuadPart -= (DWORDLONG)0x19db1ded53e8000;

	// Convert 100ns units to seconds;
	this->m_tv.Second = (LONG) (_100ns.QuadPart / (10000 * 1000));
	// Convert remainder to microseconds;
	this->m_tv.USecond = (LONG) ((_100ns.QuadPart % (10000 * 1000)) / 10);

	// 2010.11.17 edited by 韦珂
	this->BounderCheck();
}

#endif	// D_WIN32


CDTimeValue::CDTimeValue( const D_TIMEVALUE& tv )
{
	this->Set( tv );
}

CDTimeValue::CDTimeValue( const timeval& tv )
{
	this->Set( tv );
}

DWORD CDTimeValue::GetMSecond() const
{
	return ( this->m_tv.Second * 1000 + this->m_tv.USecond / 1000 );
}

// 秒数
DWORD CDTimeValue::GetSecond() const
{
	return this->m_tv.Second;
}

VOID CDTimeValue::SetSecond( LONGLONG second )
{
	// 2010.11.17 edited by 韦珂
	//this->m_tv.Second = (LONG)second;

	Set( second );
}

LONG CDTimeValue::GetUSecond() const
{
	return this->m_tv.USecond;
}

VOID CDTimeValue::SetUSecond( LONG usecond )
{
	this->m_tv.USecond = usecond;

	this->BounderCheck();
}

VOID CDTimeValue::Set( const D_TIMEVALUE &tv )
{
	this->m_tv.Second = tv.Second;
	this->m_tv.USecond = tv.USecond;

	this->BounderCheck();
}

void CDTimeValue::Set( const timeval& tv )
{
	m_tv.Second = tv.tv_sec;
	m_tv.USecond = tv.tv_usec;

	this->BounderCheck();
}

D_INLINE VOID
	CDTimeValue::Set( 
	LONGLONG second, 
	LONG usecond )
{
	//this->m_tv.Second = (LONG)second;
	//this->m_tv.USecond = usecond;
	long lTmp = (long)second;
	this->m_tv.Second = lTmp;
	this->m_tv.USecond = (long)((second - (LONGLONG)lTmp) * D_ONE_SECOND_IN_USECS);
	this->m_tv.USecond += usecond;

	// 2010.11.17 edited by 韦珂
	this->BounderCheck();
}

D_INLINE void CDTimeValue::Set( LONGLONG llSecond )
{
	long lTmp = (long)llSecond;
	this->m_tv.Second = lTmp;
	this->m_tv.USecond = (long)((llSecond - (LONGLONG)lTmp) * D_ONE_SECOND_IN_USECS);

	this->BounderCheck();
}

// True if tv1 > tv2.

D_INLINE BOOL
	operator > (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	if (tv1.GetSecond () > tv2.GetSecond ())
	{
		return 1;
	}
	else if (tv1.GetSecond () == tv2.GetSecond ()
		&& tv1.GetUSecond () > tv2.GetUSecond ())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// True if tv1 >= tv2.

D_INLINE BOOL
	operator >= (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	if (tv1.GetSecond () > tv2.GetSecond ())
	{
		return 1;
	}
	else if (tv1.GetSecond () == tv2.GetSecond ()
		&& tv1.GetUSecond () >= tv2.GetUSecond ())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// True if tv1 < tv2.
D_INLINE BOOL
	operator < (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	return tv2 > tv1;
}

// True if tv1 >= tv2.
D_INLINE BOOL
	operator <= (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	return tv2 >= tv1;
}

// True if tv1 == tv2.
D_INLINE BOOL
	operator == (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	return tv1.GetSecond () == tv2.GetSecond ()
		&& tv1.GetUSecond () == tv2.GetUSecond ();
}

// True if tv1 != tv2.
D_INLINE BOOL
	operator != (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	return !(tv1 == tv2);
}

// Add TV to this.
D_INLINE CDTimeValue &
	CDTimeValue::operator+= ( const CDTimeValue &tv )
{
	this->SetSecond( this->GetSecond() + tv.GetSecond() );
	this->SetUSecond( this->GetUSecond() + tv.GetUSecond() );

	// 2010.11.17 edited by 韦珂
	this->BounderCheck();

	return *this;
}

D_INLINE CDTimeValue &
	CDTimeValue::operator+= ( LONGLONG tv )
{
	this->SetSecond( this->GetSecond () + tv );
	return *this;
}

D_INLINE CDTimeValue &
	CDTimeValue::operator= ( const CDTimeValue &tv )
{
	this->SetSecond( tv.GetSecond() );
	this->SetUSecond( tv.GetUSecond() );
	return *this;
}

D_INLINE CDTimeValue &
	CDTimeValue::operator= ( LONGLONG tv )
{
	this->SetSecond( tv );
	this->SetUSecond( 0 );
	return *this;
}

// Subtract TV to this.

D_INLINE CDTimeValue &
	CDTimeValue::operator-= ( const CDTimeValue &tv )
{
	this->SetSecond( this->GetSecond() - tv.GetSecond() );
	this->SetUSecond( this->GetUSecond() - tv.GetUSecond() );

	// 2010.11.17 edited by 韦珂
	this->BounderCheck();

	return *this;
}

D_INLINE CDTimeValue &
	CDTimeValue::operator-= ( LONGLONG tv )
{
	this->SetSecond( this->GetSecond () - tv );
	return *this;
}

// Adds two CDTimeValue objects together, returns the sum.

D_INLINE CDTimeValue
	operator + (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	CDTimeValue sum( tv1 );
	sum += tv2;

	return sum;
}

// Subtracts two CTimeValue objects, returns the difference.

D_INLINE CDTimeValue
	operator - (
	const CDTimeValue &tv1,
	const CDTimeValue &tv2 )
{
	CDTimeValue delta( tv1 );
	delta -= tv2;

	return delta;
}

void CDTimeValue::BounderCheck()
{
	// 如果<m_tv.USecond>大于边界值, 即超过1秒
	if ( D_ONE_SECOND_IN_USECS <= m_tv.USecond ) 
	{
		do 
		{
			// 加1秒
			m_tv.Second++;

			// 减1000000微秒
			m_tv.USecond -= D_ONE_SECOND_IN_USECS;
		}
		while( D_ONE_SECOND_IN_USECS <= m_tv.USecond );
	}
	// 如果<m_tv.USecond>小于负的边界值, 即小于1微秒
	else if ( -D_ONE_SECOND_IN_USECS >= m_tv.USecond ) 
	{
		do 
		{
			// 减1秒
			m_tv.Second--;

			// 加1000000微秒
			m_tv.USecond += D_ONE_SECOND_IN_USECS;
		}
		while( -D_ONE_SECOND_IN_USECS >= m_tv.USecond );
	}

	if ( 1 <= m_tv.Second && 0 > m_tv.USecond ) 
	{
		m_tv.Second--;
		m_tv.USecond += D_ONE_SECOND_IN_USECS;
	}
	else if ( 0 > m_tv.Second && 0 < m_tv.USecond ) 
	{
		m_tv.Second++;
		m_tv.USecond -= D_ONE_SECOND_IN_USECS;
	}
}

