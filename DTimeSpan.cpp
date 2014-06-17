
#include "DTimeSpan.h"

int CDTimeSpan::Days() const
{
	return int( m_span / DAYS );
}

int CDTimeSpan::Hours() const
{
	return int( (m_span / HOURS) % 24 );
}

int CDTimeSpan::TotalHours() const
{
	return int( m_span / HOURS );
}

int CDTimeSpan::Minutes() const
{
	return int(( m_span / MINUTES ) % 60 );
}

int CDTimeSpan::TotalMinutes() const
{
	return int( m_span / MINUTES );
}

int CDTimeSpan::Seconds() const
{
	return int(( m_span / SECONDS ) % 60 );
}

int CDTimeSpan::TotalSeconds() const
{
	return int( m_span / SECONDS );
}

int CDTimeSpan::MilliSeconds() const
{
	return int(( m_span / MILLISECONDS ) % 1000 );
}

CDTimeSpan::TTimeDiff CDTimeSpan::TotalMilliSeconds() const
{
	return int( m_span / MILLISECONDS );
}

int CDTimeSpan::MicroSeconds() const
{
	return int( m_span % 1000 );
}

CDTimeSpan::TTimeDiff CDTimeSpan::TotalMicroSeconds() const
{
	return m_span;
}

int CDTimeSpan::Useconds() const
{
	return int( m_span % 1000000 );
}

CDTimeSpan::CDTimeSpan()
	: m_span( 0 )
{

}

CDTimeSpan::CDTimeSpan( TTimeDiff microseconds )
	: m_span( microseconds )
{

}

CDTimeSpan::CDTimeSpan( long seconds, long microseconds )
	: m_span( TTimeDiff(seconds) * SECONDS + microseconds)
{

}

CDTimeSpan::CDTimeSpan( int days, int hours, int minutes, int seconds, int microseconds )
	: m_span( TTimeDiff(microseconds) + TTimeDiff(seconds) * SECONDS + TTimeDiff(minutes) * MINUTES + TTimeDiff(hours) * HOURS + TTimeDiff(days) * DAYS )
{

}

CDTimeSpan::CDTimeSpan( const CDTimeSpan& timespan )
	: m_span( timespan.m_span )
{

}

CDTimeSpan& CDTimeSpan::operator=( const CDTimeSpan& timespan )
{
	// no need to judge this == &timespan
	m_span = timespan.m_span;

	return *this;
}

CDTimeSpan& CDTimeSpan::operator=( TTimeDiff microseconds )
{
	m_span = microseconds;

	return *this;
}

CDTimeSpan& CDTimeSpan::Assign( int days, int hours, int minutes, int seconds, int microseconds )
{
	m_span = TTimeDiff(microseconds) + TTimeDiff(seconds) * SECONDS + TTimeDiff(minutes) * MINUTES + TTimeDiff(hours) * HOURS + TTimeDiff(days) * DAYS;

	return *this;
}

CDTimeSpan& CDTimeSpan::Assign( long seconds, long microseconds )
{
	m_span = TTimeDiff(seconds) * SECONDS + microseconds;

	return *this;
}

bool CDTimeSpan::operator==( const CDTimeSpan& ts ) const
{
	return m_span == ts.m_span;
}

bool CDTimeSpan::operator==( TTimeDiff microseconds ) const
{
	return m_span == microseconds;
}

bool CDTimeSpan::operator!=( const CDTimeSpan& ts ) const
{
	return m_span != ts.m_span;
}

bool CDTimeSpan::operator!=( TTimeDiff microseconds ) const
{
	return m_span != microseconds;
}

bool CDTimeSpan::operator>( const CDTimeSpan& ts ) const
{
	return m_span > ts.m_span;
}

bool CDTimeSpan::operator>( TTimeDiff microseconds ) const
{
	return m_span > microseconds;
}

bool CDTimeSpan::operator>=( const CDTimeSpan& ts ) const
{
	return m_span >= ts.m_span;
}

bool CDTimeSpan::operator>=( TTimeDiff microseconds ) const
{
	return m_span >= microseconds;
}

bool CDTimeSpan::operator<( const CDTimeSpan& ts ) const
{
	return m_span < ts.m_span;
}

bool CDTimeSpan::operator<( TTimeDiff microseconds ) const
{
	return m_span < microseconds;
}

bool CDTimeSpan::operator<=( const CDTimeSpan& ts ) const
{
	return m_span <= ts.m_span;
}

bool CDTimeSpan::operator<=( TTimeDiff microseconds ) const
{
	return m_span <= microseconds;
}

CDTimeSpan CDTimeSpan::operator+( const CDTimeSpan& ts ) const
{
	return CDTimeSpan( m_span + ts.m_span );
}

CDTimeSpan CDTimeSpan::operator+( TTimeDiff microseconds ) const
{
	return CDTimeSpan( m_span + microseconds );
}

CDTimeSpan CDTimeSpan::operator-( const CDTimeSpan& ts ) const
{
	return CDTimeSpan( m_span - ts.m_span );
}

CDTimeSpan& CDTimeSpan::operator+=( const CDTimeSpan& ts )
{
	m_span += ts.m_span;

	return *this;
}

CDTimeSpan& CDTimeSpan::operator+=( TTimeDiff microseconds )
{
	m_span += microseconds;

	return *this;
}

CDTimeSpan& CDTimeSpan::operator-=( const CDTimeSpan& ts )
{
	m_span -= ts.m_span;

	return *this;
}

CDTimeSpan CDTimeSpan::operator-( TTimeDiff microseconds ) const
{
	return CDTimeSpan( m_span - microseconds );
}

CDTimeSpan& CDTimeSpan::operator-=( TTimeDiff microseconds )
{
	m_span -= microseconds;

	return *this;
}


