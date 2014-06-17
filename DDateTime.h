
#ifndef _D_DATE_TIME_H_
#define _D_DATE_TIME_H_

#include "DBase.h"
#include "DTimeStamp.h"
#include "DTimeSpan.h"

class CDDateTime
{
public:
	// 月份定义
	enum Months
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	// 星期定义
	enum DaysOfWeek
	{
		SUNDAY = 0,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};

	// 创建当前时间
	CDDateTime();

	CDDateTime(const CDTimeStamp& timestamp);

	// 创建指定 时间的 日期时间
	CDDateTime( int year, int month, int day, int hour = 0, int minutes = 0, int seconds = 0, int milliseconds = 0, int microseconds = 0 );

	CDDateTime( CDTimeStamp::TTimeValue utctime, CDTimeStamp::TTimeDiff diff );

	CDDateTime( const CDDateTime& dateTime );

	// 根据朱利安历时间创建日期时间
	CDDateTime( double julianDay );

	~CDDateTime();

	CDDateTime& operator = ( const CDDateTime& dateTime );

	CDDateTime& operator = ( const CDTimeStamp& timestamp );

	CDDateTime& operator = ( double julianDay );

	// 赋值
	CDDateTime& Assign( int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int milliscond = 0, int microseccond = 0 );

	// 年
	int Year() const;

	// 月 1～12
	int Month() const;

	int Week(int firstDayOfWeek = MONDAY) const;

	// 日 1～31
	int Day() const;

	// 返回星期几 (0 to 6, 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
	int DayOfWeek() const;

	// Returns the number of the day in the year.
	// January 1 is 1, February 1 is 32, etc.
	int DayOfYear() const;

	// 返回小时数 (0 to 23).
	int Hour() const;

	// 返回分数 (0 to 59).
	int Minute() const;

	// 返回秒值 (0 to 59).
	int Second() const;

	int Millisecond() const;

	int Microsecond() const;

	int HourAMPM() const;

	bool IsAM() const;

	bool IsPM() const;

	CDTimeStamp TimeStamp() const;

	double JulianDay() const;

	/************************************
		描述: 返回UTC的时间表示值，基于1582年2月15日0时，精度为100纳秒
	
		返回值:CVxTimeStamp::TTimeValue
	
		参数列表:
	************************************/
	CDTimeStamp::TTimeValue UtcTime() const;

	/************************************
		描述: 根据给定时区差，转换本地时间为UTC时间
	
		返回值:void
	
		参数列表:
		int tzd 时区差，可以通过时区类的Tzd方法获得
	************************************/
	void MakeUTC( int tsz );

	void MakeLocal( int tsz );

	CDString ToString() const;

	/************************************
		描述: 是否是闰年
	
		返回值:bool
	
		参数列表:
		int year 年
	************************************/
	static bool IsLeapYear(int year);

	/************************************
		描述: 返回指定年月的天数
	
		返回值:int
	
		参数列表:
		int year   年
		int month  月
	************************************/
	static int DaysOfMonth(int year, int month);

	/************************************
		描述: 指定的时间是否是合法的
	
		返回值:bool
	
		参数列表:
		int year
		int month
		int day
		int hour
		int minute
		int second
		int millisecond
		int microsecond
	************************************/
	static bool IsValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

	bool operator == ( const CDDateTime& dateTime ) const;
	bool operator != ( const CDDateTime& dateTime ) const;
	bool operator >  ( const CDDateTime& dateTime ) const;
	bool operator >= ( const CDDateTime& dateTime ) const;
	bool operator <  ( const CDDateTime& dateTime ) const;
	bool operator <= ( const CDDateTime& dateTime ) const;

	CDDateTime  operator +  ( const CDTimeSpan& span ) const;
	CDDateTime  operator -  ( const CDTimeSpan& span ) const;
	CDTimeSpan  operator -  ( const CDDateTime& datetime ) const;
	CDDateTime& operator += ( const CDTimeSpan& span );
	CDDateTime& operator -= ( const CDTimeSpan& span );

protected:
	/************************************
		描述: 把UTC时间转换为朱利安日
	
		返回值:DOUBLE
	
		参数列表:
		CVxTimeStamp::TTimeValue utcTime
	************************************/
	static double ToJulianDay( CDTimeStamp::TTimeValue utcTime );

	/************************************
		描述: 计算指定时间的朱利安日
	
		返回值:DOUBLE
	
		参数列表:
		int year
		int month
		int day
		int hour
		int minute
		int second
		int millisecond
		int microsecond
	************************************/
	static double ToJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0);

	static CDTimeStamp::TTimeValue ToUtcTime( double julianDay );

	/************************************
		描述: 根据朱利安日计算格里格利日
	
		返回值:void
	
		参数列表:
		DOUBLE julianDay
	************************************/
	void ComputeGregorian( double julianDay );

	/************************************
		描述: 根据UTC时间计算时 分 秒 毫秒 微秒时间
	
		返回值:void
	
		参数列表:
	************************************/
	void ComputeDaytime();

private:
	void CheckLimit( short& lower, short& higher, short limit );
	void Normalize();

	CDTimeStamp::TTimeValue	m_ts;
	short						m_year;
	short						m_month;
	short						m_day;
	short						m_hour;
	short						m_minute;
	short						m_second;
	short						m_millisecond;
	short						m_microsecond;
};

#endif	// _D_DATE_TIME_H_

