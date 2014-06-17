
#ifndef _D_DATE_TIME_H_
#define _D_DATE_TIME_H_

#include "DBase.h"
#include "DTimeStamp.h"
#include "DTimeSpan.h"

class CDDateTime
{
public:
	// �·ݶ���
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

	// ���ڶ���
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

	// ������ǰʱ��
	CDDateTime();

	CDDateTime(const CDTimeStamp& timestamp);

	// ����ָ�� ʱ��� ����ʱ��
	CDDateTime( int year, int month, int day, int hour = 0, int minutes = 0, int seconds = 0, int milliseconds = 0, int microseconds = 0 );

	CDDateTime( CDTimeStamp::TTimeValue utctime, CDTimeStamp::TTimeDiff diff );

	CDDateTime( const CDDateTime& dateTime );

	// ������������ʱ�䴴������ʱ��
	CDDateTime( double julianDay );

	~CDDateTime();

	CDDateTime& operator = ( const CDDateTime& dateTime );

	CDDateTime& operator = ( const CDTimeStamp& timestamp );

	CDDateTime& operator = ( double julianDay );

	// ��ֵ
	CDDateTime& Assign( int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int milliscond = 0, int microseccond = 0 );

	// ��
	int Year() const;

	// �� 1��12
	int Month() const;

	int Week(int firstDayOfWeek = MONDAY) const;

	// �� 1��31
	int Day() const;

	// �������ڼ� (0 to 6, 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
	int DayOfWeek() const;

	// Returns the number of the day in the year.
	// January 1 is 1, February 1 is 32, etc.
	int DayOfYear() const;

	// ����Сʱ�� (0 to 23).
	int Hour() const;

	// ���ط��� (0 to 59).
	int Minute() const;

	// ������ֵ (0 to 59).
	int Second() const;

	int Millisecond() const;

	int Microsecond() const;

	int HourAMPM() const;

	bool IsAM() const;

	bool IsPM() const;

	CDTimeStamp TimeStamp() const;

	double JulianDay() const;

	/************************************
		����: ����UTC��ʱ���ʾֵ������1582��2��15��0ʱ������Ϊ100����
	
		����ֵ:CVxTimeStamp::TTimeValue
	
		�����б�:
	************************************/
	CDTimeStamp::TTimeValue UtcTime() const;

	/************************************
		����: ���ݸ���ʱ���ת������ʱ��ΪUTCʱ��
	
		����ֵ:void
	
		�����б�:
		int tzd ʱ�������ͨ��ʱ�����Tzd�������
	************************************/
	void MakeUTC( int tsz );

	void MakeLocal( int tsz );

	CDString ToString() const;

	/************************************
		����: �Ƿ�������
	
		����ֵ:bool
	
		�����б�:
		int year ��
	************************************/
	static bool IsLeapYear(int year);

	/************************************
		����: ����ָ�����µ�����
	
		����ֵ:int
	
		�����б�:
		int year   ��
		int month  ��
	************************************/
	static int DaysOfMonth(int year, int month);

	/************************************
		����: ָ����ʱ���Ƿ��ǺϷ���
	
		����ֵ:bool
	
		�����б�:
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
		����: ��UTCʱ��ת��Ϊ��������
	
		����ֵ:DOUBLE
	
		�����б�:
		CVxTimeStamp::TTimeValue utcTime
	************************************/
	static double ToJulianDay( CDTimeStamp::TTimeValue utcTime );

	/************************************
		����: ����ָ��ʱ�����������
	
		����ֵ:DOUBLE
	
		�����б�:
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
		����: �����������ռ�����������
	
		����ֵ:void
	
		�����б�:
		DOUBLE julianDay
	************************************/
	void ComputeGregorian( double julianDay );

	/************************************
		����: ����UTCʱ�����ʱ �� �� ���� ΢��ʱ��
	
		����ֵ:void
	
		�����б�:
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

