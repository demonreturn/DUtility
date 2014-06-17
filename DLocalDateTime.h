
#ifndef _D_LOCAL_TIME_H_
#define _D_LOCAL_TIME_H_

#include "DBase.h"
#include "DDateTime.h"

class CDLocalDateTime
{
public:
	// 构造一个当前本地日期时间
	CDLocalDateTime();

	/************************************
		描述: 构造一个指定年月日。。。的本地日期时间
	
		返回值:
	
		参数列表:
		int year             0 to 9999.
		int month            1 to 12.
		int day              1 to 31
		int hour             0 to 23.
		int minute           0 to 59.
		int second           0 to 59.
		int millisecond      0 to 999.
		int microsecond      0 to 999.
	************************************/
	CDLocalDateTime( int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0 );

	CDLocalDateTime( const CDTimeStamp& timestamp );

	/************************************
		描述: 根据UTC 的datetime生成一个本地日期时间
		内部会根据时区进行转换
	
		返回值:
	
		参数列表:
		const CVxDateTime & dateTime    UTC日期时间
	************************************/
	CDLocalDateTime( const CDDateTime& datetime );

	/************************************
		描述: 根据给定的朱利安日生成一个本地日期时间
	
		返回值:
	
		参数列表:
		double julianDay               朱利安日期
	************************************/
	CDLocalDateTime( double julianDay );

	CDLocalDateTime( const CDLocalDateTime& dateTime );

	CDLocalDateTime& operator = ( const CDLocalDateTime& dateTime );

	CDLocalDateTime& operator = ( double julianDay );

	/************************************
		描述: 赋值函数
	
		返回值:CVxLocalDateTime&
	
		参数列表:
		int year             0 to 9999.
		int month            1 to 12.
		int day              1 to 31
		int hour             0 to 23.
		int minute           0 to 59.
		int second           0 to 59.
		int millisecond      0 to 999.
		int microsecond      0 to 999.
	************************************/
	CDLocalDateTime& Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);

	int Year() const;

	int Month() const;

	// 返回时间在月中的日期，如2012-7-13 12:00:00:000 返回的是13号
	int Day() const;

	// 返回当前时间在这一年中是第几周。 firstDayOfWeek应该是SUNDAY (0) or MONDAY (1)
	// 返回值将会是0～53.
	int Week( int firstDayOfWeek = CDDateTime::MONDAY ) const;

	// 一周中的日期，0～6 0 = Sunday, 1 = Monday, ..., 6 = Saturday
	int DayOfWeek() const;

	// 返回一年中的日期，如1月1日时返回1，2月1日时返回32等等。
	int DayOfYear() const;

	int Hour() const;

	int HourAMPM() const;

	bool IsAM() const;

	bool IsPM() const;

	int Minute() const;

	int Second() const;

	int Millisecond() const;

	int Microsecond() const;

	double JulianDay() const;

	int Tzd() const;

	CDDateTime UTC() const;

	CDTimeStamp TimeStamp() const;

	CDTimeStamp::TTimeValue UTCTime() const;

	CDString ToString() const;

// operator
	bool operator == ( const CDLocalDateTime& dateTime ) const;
	bool operator != ( const CDLocalDateTime& dateTime ) const;
	bool operator <  ( const CDLocalDateTime& dateTime ) const;
	bool operator <= ( const CDLocalDateTime& dateTime ) const;
	bool operator >  ( const CDLocalDateTime& dateTime ) const;
	bool operator >= ( const CDLocalDateTime& dateTime ) const;

	CDLocalDateTime  operator +  ( const CDTimeSpan& span ) const;
	CDLocalDateTime  operator -  ( const CDTimeSpan& span ) const;
	CDTimeSpan		  operator -  ( const CDLocalDateTime& dateTime ) const;
	CDLocalDateTime& operator += ( const CDTimeSpan& span );
	CDLocalDateTime& operator -= ( const CDTimeSpan& span );

protected:
	CDLocalDateTime( CDTimeStamp::TTimeValue utcTime, CDTimeStamp::TTimeDiff diff, int tzd );

	void DetermineTzd(bool adjust = false);

	void AdjustForTzd();

	std::time_t DstOffset(int& dstOffset) const;

private:
	CDDateTime					m_dateTime;
	int							m_tzd;
};

#endif	// _D_LOCAL_TIME_H_

