
#include "DDateTime.h"


#include "DOSMemory.h"

#include <algorithm>
#include <cmath>
#include <assert.h>

CDDateTime::CDDateTime()
{
	CDTimeStamp now;
	m_ts = now.GetUtcTime();

	ComputeGregorian( JulianDay() );
	ComputeDaytime();
}

CDDateTime::CDDateTime( const CDTimeStamp& timestamp )
	: m_ts( timestamp.GetUtcTime() )
{
	ComputeGregorian( JulianDay() );
	ComputeDaytime();
}

CDDateTime::CDDateTime( int year, int month, int day, int hour /*= 0*/, int minutes /*= 0*/, int seconds /*= 0*/, int milliseconds /*= 0*/, int microseconds /*= 0 */ )
	: m_year( year )
	, m_month( month )
	, m_day( day )
	, m_hour( hour )
	, m_minute( minutes )
	, m_second( seconds )
	, m_millisecond( milliseconds )
	, m_microsecond( microseconds )
{
	assert(year >= 0 && year <= 9999);
	assert (month >= 1 && month <= 12);
	assert (day >= 1 && day <= DaysOfMonth(year, month));
	assert (hour >= 0 && hour <= 23);
	assert (minutes >= 0 && minutes <= 59);
	assert (seconds >= 0 && seconds <= 59);
	assert (milliseconds >= 0 && milliseconds <= 999);
	assert (microseconds >= 0 && microseconds <= 999);

	m_ts = ToUtcTime( ToJulianDay( year, month, day, hour) + 
		10 * ( hour * CDTimeSpan::HOURS + minutes * CDTimeSpan::MINUTES + seconds * CDTimeSpan::SECONDS + milliseconds * CDTimeSpan::MILLISECONDS + microseconds ));
}

CDDateTime::CDDateTime( CDTimeStamp::TTimeValue utctime, CDTimeStamp::TTimeDiff diff )
	: m_ts( utctime + diff * 10 )
{
	ComputeGregorian( JulianDay() );
	ComputeDaytime();
}

CDDateTime::CDDateTime( const CDDateTime& dateTime )
	: m_ts(dateTime.m_ts)
	, m_year(dateTime.m_year)
	, m_month(dateTime.m_month)
	, m_day(dateTime.m_day)
	, m_hour(dateTime.m_hour)
	, m_minute(dateTime.m_minute)
	, m_second(dateTime.m_second)
	, m_millisecond(dateTime.m_millisecond)
	, m_microsecond(dateTime.m_microsecond)
{

}

CDDateTime::CDDateTime( double julianDay )
{
	ComputeGregorian( julianDay );
}

CDDateTime::~CDDateTime()
{
}

CDDateTime& CDDateTime::operator=( const CDDateTime& dateTime )
{
	if ( &dateTime != this )
	{
		m_ts			= dateTime.m_ts;
		m_year			= dateTime.m_year;
		m_month		= dateTime.m_month;
		m_day			= dateTime.m_day;
		m_hour			= dateTime.m_hour;
		m_minute		= dateTime.m_minute;
		m_second		= dateTime.m_second;
		m_millisecond	= dateTime.m_millisecond;
		m_microsecond	= dateTime.m_microsecond;
	}

	return (*this);
}

CDDateTime& CDDateTime::operator=( const CDTimeStamp& timestamp )
{
	m_ts = timestamp.GetUtcTime();

	ComputeGregorian( JulianDay() );
	ComputeDaytime();

	return (*this);
}

CDDateTime& CDDateTime::operator=( double julianDay )
{
	m_ts = ToUtcTime( julianDay );
	ComputeGregorian( julianDay );

	return (*this);
}

CDDateTime& CDDateTime::Assign( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int milliscond /*= 0*/, int microseccond /*= 0 */ )
{
	assert (year >= 0 && year <= 9999);
	assert (month >= 1 && month <= 12);
	assert (day >= 1 && day <= DaysOfMonth(year, month));
	assert (hour >= 0 && hour <= 23);
	assert (minute >= 0 && minute <= 59);
	assert (second >= 0 && second <= 59);
	assert (milliscond >= 0 && milliscond <= 999);
	assert (microseccond >= 0 && microseccond <= 999);

	m_ts = ToUtcTime( ToJulianDay( year, month, day, hour) + 
		10 * ( hour * CDTimeSpan::HOURS + minute * CDTimeSpan::MINUTES + second * CDTimeSpan::SECONDS + milliscond * CDTimeSpan::MILLISECONDS + microseccond ));

	m_year			= year;
	m_month			= month;
	m_day			= day;
	m_hour			= hour;
	m_minute		= minute;
	m_second		= second;
	m_millisecond	= milliscond;
	m_microsecond	= microseccond;

	return (*this);
}

int CDDateTime::Year() const
{
	return m_year;
}

int CDDateTime::Month() const
{
	return m_month;
}

int CDDateTime::Day() const
{
	return m_day;
}

int CDDateTime::Week( int firstDayOfWeek /*= MONDAY*/ ) const
{
	assert( firstDayOfWeek >= 0 && firstDayOfWeek <= 6 );

	/// find the first firstDayOfWeek.
	int baseDay = 1;
	while ( CDDateTime( m_year, 1, baseDay ).DayOfWeek() != firstDayOfWeek)
	{
		++baseDay;
	}

	int doy = DayOfYear();
	int offs = baseDay <= 4 ? 0 : 1;
	if ( doy < baseDay )
	{
		return offs;
	}
	else
	{
		return (doy - baseDay)/7 + 1 + offs;
	}
}

int CDDateTime::DayOfYear() const
{
	int doy = 0;
	for ( int month = 1; month < m_month; ++month )
	{
		doy += DaysOfMonth( m_year, month );
	}

	doy += m_day;

	return doy;
}

int CDDateTime::Hour() const
{
	return m_hour;
}

int CDDateTime::Minute() const
{
	return m_minute;
}

int CDDateTime::Second() const
{
	return m_second;
}

int CDDateTime::Millisecond() const
{
	return m_millisecond;
}

int CDDateTime::Microsecond() const
{
	return m_microsecond;
}

int CDDateTime::HourAMPM() const
{
	if ( m_hour < 1 )
	{
		return 12;
	}
	else if( m_hour > 12 )
	{
		return m_hour - 12;
	}
	else
	{
		return m_hour;
	}
}

bool CDDateTime::IsAM() const
{
	return m_hour < 12;
}

bool CDDateTime::IsPM() const
{
	return m_hour >= 12;
}

CDTimeStamp CDDateTime::TimeStamp() const
{
	return m_ts;
}

double CDDateTime::JulianDay() const
{
	return ToJulianDay( m_ts );
}

CDTimeStamp::TTimeValue CDDateTime::UtcTime() const
{
	return m_ts;
}

void CDDateTime::MakeUTC( int tsz )
{
	operator -= ( CDTimeSpan(((CDTimeStamp::TTimeDiff) tsz) * CDTimeSpan::SECONDS));
}

void CDDateTime::MakeLocal( int tsz )
{
	operator += ( CDTimeSpan(((CDTimeStamp::TTimeDiff) tsz) * CDTimeSpan::SECONDS));
}

CDString CDDateTime::ToString() const
{
	static const char* szFormat = "%02d/%02d/%04d %02d:%02d:%02d.%03ld";
	char szBuffer[512]={0};

	D_OS::Snprintf(
		szBuffer,
		sizeof( szBuffer - 1),
		sizeof( szBuffer),
		szFormat,
		m_month,
		m_day,
		m_year,
		m_hour,
		m_minute,
		m_second,
		m_millisecond );

	return CDString( szBuffer );
}

bool CDDateTime::IsLeapYear( int year )
{
	return ( year % 4) == 0 
		&& (( year % 100) != 0 ||
		( year % 400) == 0 );
}

int CDDateTime::DaysOfMonth( int year, int month )
{
	assert( 1 <= month && 12 >= month );

	static int daysOfMonthTable[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( 2 == month && IsLeapYear( year ))
	{
		return 29;
	}
	else
	{
		return daysOfMonthTable[ month ];
	}
}

bool CDDateTime::IsValid( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microsecond /*= 0*/ )
{
	return
		(year >= 0 && year <= 9999) &&
		(month >= 1 && month <= 12) &&
		(day >= 1 && day <= DaysOfMonth(year, month)) &&
		(hour >= 0 && hour <= 23) &&
		(minute >= 0 && minute <= 59) &&
		(second >= 0 && second <= 59) &&
		(millisecond >= 0 && millisecond <= 999) &&
		(microsecond >= 0 && microsecond <= 999);
}

bool CDDateTime::operator==( const CDDateTime& dateTime ) const
{
	return m_ts == dateTime.m_ts;
}

bool CDDateTime::operator!=( const CDDateTime& dateTime ) const
{
	return m_ts != dateTime.m_ts;
}

bool CDDateTime::operator>( const CDDateTime& dateTime ) const
{
	return m_ts > dateTime.m_ts;
}

bool CDDateTime::operator>=( const CDDateTime& dateTime ) const
{
	return m_ts >= dateTime.m_ts;
}

bool CDDateTime::operator<( const CDDateTime& dateTime ) const
{
	return m_ts < dateTime.m_ts;
}

bool CDDateTime::operator<=( const CDDateTime& dateTime ) const
{
	return m_ts <= dateTime.m_ts;
}

CDDateTime CDDateTime::operator+( const CDTimeSpan& span ) const
{
	return CDDateTime( m_ts, span.TotalMicroSeconds() );
}

CDDateTime CDDateTime::operator-( const CDTimeSpan& span ) const
{
	return CDDateTime( m_ts, span.TotalMicroSeconds() * (-1) );
}

CDTimeSpan CDDateTime::operator-( const CDDateTime& datetime ) const
{
	return CDTimeSpan(( m_ts - datetime.m_ts) / 10 );
}

CDDateTime& CDDateTime::operator+=( const CDTimeSpan& span )
{
	m_ts += span.TotalMicroSeconds() * 10;

	ComputeGregorian(JulianDay());
	ComputeDaytime();

	return (*this);
}

CDDateTime& CDDateTime::operator-=( const CDTimeSpan& span )
{
	m_ts -= span.TotalMicroSeconds() * 10;

	ComputeGregorian(JulianDay());
	ComputeDaytime();

	return (*this);
}

double CDDateTime::ToJulianDay( CDTimeStamp::TTimeValue utcTime )
{
	double utcDays = double( utcTime ) / 864000000000.0;

	return utcDays + 2299160.5; // first day of Gregorian reform (Oct 15 1582)
}

double CDDateTime::ToJulianDay( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microsecond /*= 0*/ )
{
	// lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
	static int lookup[] = {-91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337};

	// day to double
	double dday = double(day) + ((double((hour*60 + minute)*60 + second)*1000 + millisecond)*1000 + microsecond)/86400000000.0;
	if (month < 3)
	{
		month += 12;
		--year;
	}
	double dyear = double(year);
	return dday + lookup[month] + 365*year + std::floor(dyear/4) - std::floor(dyear/100) + std::floor(dyear/400) + 1721118.5;
}

CDTimeStamp::TTimeValue CDDateTime::ToUtcTime( double julianDay )
{
	return CDTimeStamp::TTimeValue((julianDay - 2299160.5)*864000000000.0);
}

void CDDateTime::ComputeGregorian( double julianDay )
{
	double z = std::floor( julianDay - 1721118.5);
	double r = julianDay - 1721118.5 - z;
	double g = z - 0.25;
	double a = std::floor( g / 36524.25 );
	double b = a - std::floor(a/4);

	m_year = short( std::floor(( b + a ) / 365.25));
	double c = b + z - std::floor(365.25*m_year);
	m_month = short( std::floor((5*c + 456)/153) );
	double dday = c - std::floor((153.0*m_month - 457)/5) + r;
	m_day = short( dday );

	if (m_month > 12)
	{
		++m_year;
		m_month -= 12;
	}
	r      *= 24;
	m_hour   = short(std::floor(r));
	r      -= std::floor(r);
	r      *= 60;
	m_minute = short(std::floor(r));
	r      -= std::floor(r);
	r      *= 60;
	m_second = short(std::floor(r));
	r      -= std::floor(r);
	r      *= 1000;
	m_millisecond = short(std::floor(r));
	r      -= std::floor(r);
	r      *= 1000;
	m_microsecond = short(r + 0.5);

	Normalize();

	assert (m_month >= 1 && m_month <= 12);
	assert (m_day >= 1 && m_day <= DaysOfMonth(m_year, m_month));
	assert (m_hour >= 0 && m_hour <= 23);
	assert (m_minute >= 0 && m_minute <= 59);
	assert (m_second >= 0 && m_second <= 59);
	assert (m_millisecond >= 0 && m_millisecond <= 999);
	assert (m_microsecond >= 0 && m_microsecond <= 999);
}

void CDDateTime::ComputeDaytime()
{
	CDTimeSpan span(m_ts/10);
	m_hour        = span.Hours();
	m_minute      = span.Minutes();
	m_second      = span.Seconds();
	m_millisecond = span.MilliSeconds();
	m_microsecond = span.MicroSeconds();
}

void CDDateTime::CheckLimit( short& lower, short& higher, short limit )
{
	if ( lower >= limit )
	{
		higher += short( lower / limit );
		lower += short( lower % limit );
	}
}

void CDDateTime::Normalize()
{
	CheckLimit(m_microsecond, m_millisecond, 1000);
	CheckLimit(m_millisecond, m_second, 1000);
	CheckLimit(m_second, m_minute, 60);
	CheckLimit(m_minute, m_hour, 60);
	CheckLimit(m_hour, m_day, 24);

	if (m_day > DaysOfMonth(m_year, m_month))
	{
		m_day -= DaysOfMonth(m_year, m_month);
		if (++m_month > 12)
		{
			++m_year;
			m_month -= 12;
		}
	}
}

int CDDateTime::DayOfWeek() const
{
	return int((std::floor(JulianDay() + 1.5))) % 7;
}


