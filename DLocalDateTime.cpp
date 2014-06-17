#include "DLocalDateTime.h"
#include "DTimeSpan.h"
#include "DTimeZone.h"


CDLocalDateTime::CDLocalDateTime()
{
	DetermineTzd( true );
}

CDLocalDateTime::CDLocalDateTime( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microsecond /*= 0 */ )
	:m_dateTime(year, month, day, hour, minute, second, millisecond, microsecond)
{
	DetermineTzd();
}

CDLocalDateTime::CDLocalDateTime( const CDTimeStamp& timestamp )
	:m_dateTime(timestamp)
{
	DetermineTzd( true );
}

CDLocalDateTime::CDLocalDateTime( const CDDateTime& datetime )
	: m_dateTime( datetime )
{
	DetermineTzd( true );
}

CDLocalDateTime::CDLocalDateTime( double julianDay )
	: m_dateTime( julianDay )
{
	DetermineTzd( true );
}

CDLocalDateTime::CDLocalDateTime( const CDLocalDateTime& dateTime )
	: m_dateTime( dateTime.m_dateTime )
	, m_tzd( dateTime.m_tzd )
{

}

CDLocalDateTime::CDLocalDateTime( CDTimeStamp::TTimeValue utcTime, CDTimeStamp::TTimeDiff diff, int tzd )
{

}

CDLocalDateTime& CDLocalDateTime::operator=( const CDLocalDateTime& dateTime )
{
	if ( &dateTime != this )
	{
		m_dateTime = dateTime.m_dateTime;
		m_tzd = dateTime.m_tzd;
	}

	return *this;
}

CDLocalDateTime& CDLocalDateTime::operator=( double julianDay )
{
	m_dateTime = julianDay;
	DetermineTzd(true);

	return *this;
}

CDLocalDateTime& CDLocalDateTime::Assign( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microseconds /*= 0*/ )
{
	m_dateTime.Assign(year, month, day, hour, minute, second, millisecond, microseconds);
	DetermineTzd(false);
	return *this;
}

int CDLocalDateTime::Year() const
{
	return m_dateTime.Year();
}

int CDLocalDateTime::Month() const
{
	return m_dateTime.Month();
}

int CDLocalDateTime::Day() const
{
	return m_dateTime.Day();
}

int CDLocalDateTime::Week( int firstDayOfWeek /*= CDDateTime::MONDAY */ ) const
{
	return m_dateTime.Week( firstDayOfWeek );
}

int CDLocalDateTime::DayOfWeek() const
{
	return m_dateTime.DayOfWeek();
}

int CDLocalDateTime::DayOfYear() const
{
	return m_dateTime.DayOfYear();
}

int CDLocalDateTime::Hour() const
{
	return m_dateTime.Hour();
}

int CDLocalDateTime::HourAMPM() const
{
	return m_dateTime.HourAMPM();
}

bool CDLocalDateTime::IsAM() const
{
	return m_dateTime.IsAM();
}

bool CDLocalDateTime::IsPM() const
{
	return m_dateTime.IsPM();
}

int CDLocalDateTime::Minute() const
{
	return m_dateTime.Minute();
}

int CDLocalDateTime::Second() const
{
	return m_dateTime.Second();
}

int CDLocalDateTime::Millisecond() const
{
	return m_dateTime.Millisecond();
}

int CDLocalDateTime::Microsecond() const
{
	return m_dateTime.Microsecond();
}

double CDLocalDateTime::JulianDay() const
{
	return m_dateTime.JulianDay();
}

int CDLocalDateTime::Tzd() const
{
	return m_tzd;
}

CDDateTime CDLocalDateTime::UTC() const
{
	return CDDateTime( m_dateTime.UtcTime(), -((CDTimeStamp::TTimeDiff)m_tzd) * CDTimeSpan::SECONDS );
}

CDTimeStamp CDLocalDateTime::TimeStamp() const
{
	return CDTimeStamp::FromUTCTime( m_dateTime.UtcTime() );
}

CDTimeStamp::TTimeValue CDLocalDateTime::UTCTime() const
{
	return m_dateTime.UtcTime() - ((CDTimeStamp::TTimeDiff)m_tzd) * CDTimeSpan::SECONDS;
}

CDString CDLocalDateTime::ToString() const
{
	return m_dateTime.ToString();
}

bool CDLocalDateTime::operator==( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() == dateTime.UTCTime();
}

bool CDLocalDateTime::operator!=( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() != dateTime.UTCTime();
}

bool CDLocalDateTime::operator<( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() < dateTime.UTCTime();
}

bool CDLocalDateTime::operator<=( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() <= dateTime.UTCTime();
}

bool CDLocalDateTime::operator>( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() > dateTime.UTCTime();
}

bool CDLocalDateTime::operator>=( const CDLocalDateTime& dateTime ) const
{
	return UTCTime() >= dateTime.UTCTime();
}

CDLocalDateTime CDLocalDateTime::operator+( const CDTimeSpan& span ) const
{
	CDDateTime tmp( UTCTime(), span.TotalMicroSeconds() );

	return CDLocalDateTime(tmp);
}

CDLocalDateTime CDLocalDateTime::operator-( const CDTimeSpan& span ) const
{
	CDDateTime tmp( UTCTime(), -span.TotalMicroSeconds() );

	return CDLocalDateTime(tmp);
}

CDTimeSpan CDLocalDateTime::operator-( const CDLocalDateTime& dateTime ) const
{
	return CDTimeSpan( (UTCTime() - dateTime.UTCTime()) /10 );
}

CDLocalDateTime& CDLocalDateTime::operator+=( const CDTimeSpan& span )
{
	*this = CDDateTime( UTCTime(), span.TotalMicroSeconds() );

	return *this;
}

CDLocalDateTime& CDLocalDateTime::operator-=( const CDTimeSpan& span )
{
	*this = CDDateTime( UTCTime(), -span.TotalMicroSeconds() );

	return *this;
}

void CDLocalDateTime::DetermineTzd( bool adjust /*= false*/ )
{
	if ( adjust )
	{
		std::time_t epochTime = m_dateTime.TimeStamp().GetTime();
#ifdef D_WIN32
		std::tm broken;
		errno_t eno = localtime_s( &broken, &epochTime );
		if ( 0 != eno )
		{
			return;
		}

		m_tzd = (CDTimeZone::UtcOffset() + ((broken.tm_isdst == 1) ? 3600 : 0));
#elif defined( D_LINUX)		// linux  й╣ож
		std::tm broken;

		if ( localtime_r(&epochTime, &broken))
		{
			m_tzd = (Timezone::UtcOffset() + ((broken.tm_isdst == 1) ? 3600 : 0));
		}
#endif

		AdjustForTzd();
	}
	else
	{
		int dst;
		DstOffset(dst);
		m_tzd = (CDTimeZone::UtcOffset() + dst);
	}
}

void CDLocalDateTime::AdjustForTzd()
{
	m_dateTime += CDTimeSpan(((CDTimeStamp::TTimeDiff) m_tzd)*CDTimeSpan::SECONDS);
}

std::time_t CDLocalDateTime::DstOffset( int& dstOffset ) const
{
	std::time_t local;
	std::tm     broken;

	broken.tm_year  = (m_dateTime.Year() - 1900);
	broken.tm_mon   = (m_dateTime.Month() - 1);
	broken.tm_mday  = m_dateTime.Day();
	broken.tm_hour  = m_dateTime.Hour();
	broken.tm_min   = m_dateTime.Minute();
	broken.tm_sec   = m_dateTime.Second();
	broken.tm_isdst = -1;

	local = std::mktime(&broken);

	dstOffset = (broken.tm_isdst == 1) ? 3600 : 0;
	return local;
}


