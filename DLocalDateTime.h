
#ifndef _D_LOCAL_TIME_H_
#define _D_LOCAL_TIME_H_

#include "DBase.h"
#include "DDateTime.h"

class CDLocalDateTime
{
public:
	// ����һ����ǰ��������ʱ��
	CDLocalDateTime();

	/************************************
		����: ����һ��ָ�������ա������ı�������ʱ��
	
		����ֵ:
	
		�����б�:
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
		����: ����UTC ��datetime����һ����������ʱ��
		�ڲ������ʱ������ת��
	
		����ֵ:
	
		�����б�:
		const CVxDateTime & dateTime    UTC����ʱ��
	************************************/
	CDLocalDateTime( const CDDateTime& datetime );

	/************************************
		����: ���ݸ�����������������һ����������ʱ��
	
		����ֵ:
	
		�����б�:
		double julianDay               ����������
	************************************/
	CDLocalDateTime( double julianDay );

	CDLocalDateTime( const CDLocalDateTime& dateTime );

	CDLocalDateTime& operator = ( const CDLocalDateTime& dateTime );

	CDLocalDateTime& operator = ( double julianDay );

	/************************************
		����: ��ֵ����
	
		����ֵ:CVxLocalDateTime&
	
		�����б�:
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

	// ����ʱ�������е����ڣ���2012-7-13 12:00:00:000 ���ص���13��
	int Day() const;

	// ���ص�ǰʱ������һ�����ǵڼ��ܡ� firstDayOfWeekӦ����SUNDAY (0) or MONDAY (1)
	// ����ֵ������0��53.
	int Week( int firstDayOfWeek = CDDateTime::MONDAY ) const;

	// һ���е����ڣ�0��6 0 = Sunday, 1 = Monday, ..., 6 = Saturday
	int DayOfWeek() const;

	// ����һ���е����ڣ���1��1��ʱ����1��2��1��ʱ����32�ȵȡ�
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

