

#ifndef _D_TIME_SPAN_H_
#define _D_TIME_SPAN_H_

#include "DBase.h"
#include "DTimeStamp.h"

class CDTimeSpan
{
public:
	typedef CDTimeStamp::TTimeDiff TTimeDiff;

	// ���Ϊ0
	CDTimeSpan();

	// ����ָ��΢���ʱ����
	CDTimeSpan( TTimeDiff microseconds );

	// ����timeval�ṹ��ʱ������Timespan
	CDTimeSpan( long seconds, long microseconds );

	CDTimeSpan( int days, int hours, int minutes,
		int seconds, int microseconds );

	CDTimeSpan( const CDTimeSpan& timespan );

	CDTimeSpan& operator = ( const CDTimeSpan& timespan );

	CDTimeSpan& operator = ( TTimeDiff microseconds );

	CDTimeSpan& Assign( int days, int hours, int minutes, int seconds, int microseconds );

	CDTimeSpan& Assign( long seconds, long microseconds );

	bool operator == ( const CDTimeSpan& ts ) const;
	bool operator != ( const CDTimeSpan& ts ) const;
	bool operator >  ( const CDTimeSpan& ts ) const;
	bool operator >= ( const CDTimeSpan& ts ) const;
	bool operator <  ( const CDTimeSpan& ts ) const;
	bool operator <= ( const CDTimeSpan& ts ) const;

	bool operator == ( TTimeDiff microseconds ) const;
	bool operator != ( TTimeDiff microseconds ) const;
	bool operator >  ( TTimeDiff microseconds ) const;
	bool operator >= ( TTimeDiff microseconds ) const;
	bool operator <  ( TTimeDiff microseconds ) const;
	bool operator <= ( TTimeDiff microseconds ) const;

	CDTimeSpan operator + ( const CDTimeSpan& ts ) const;
	CDTimeSpan operator - ( const CDTimeSpan& ts ) const;

	CDTimeSpan& operator += ( const CDTimeSpan& ts );
	CDTimeSpan& operator -= ( const CDTimeSpan& ts );

	CDTimeSpan operator + ( TTimeDiff microseconds ) const;
	CDTimeSpan operator - ( TTimeDiff microseconds ) const;

	CDTimeSpan& operator += ( TTimeDiff microseconds );
	CDTimeSpan& operator -= ( TTimeDiff microseconds );

	/************************************
		����: ��������
	
		����ֵ:int  ����
	
		�����б�:
	************************************/
	int Days() const;

	/************************************
		����: �������е�Сʱ��
	
		����ֵ:int Сʱ����0��24Сʱ
	
		�����б�:
	************************************/
	int Hours() const;

	/************************************
		����: �����ܵ�Сʱ����������ת��ΪСʱ
	
		����ֵ:int Сʱ��
	
		�����б�:
	************************************/
	int TotalHours() const;

	/************************************
		����: �������еķ�����
	
		����ֵ:int ��������0��59
	
		�����б�:
	************************************/
	int Minutes() const;

	/************************************
		����: ����ʱ��������ʾ���ܷ�����
	
		����ֵ:int �ܷ�����������Сʱ���ᱻת��
	
		�����б�:
	************************************/
	int TotalMinutes() const;

	/************************************
		����: �������е�����
	
		����ֵ:int ������0��59
	
		�����б�:
	************************************/
	int Seconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵ�����
	
		����ֵ:int �ܵ�����
	
		�����б�:
	************************************/
	int TotalSeconds() const;

	/************************************
		����: �������еĺ�����
	
		����ֵ:int ��������0��999
	
		�����б�:
	************************************/
	int MilliSeconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵĺ�����
	
		����ֵ:CVxTimespan::TTimeDiff
	
		�����б�:
	************************************/
	TTimeDiff TotalMilliSeconds() const;

	/************************************
		����: �������е�΢����
	
		����ֵ:int
	
		�����б�:
	************************************/
	int MicroSeconds() const;

	/************************************
		����: ����ʱ��������ʾ���ܵ�΢����
	
		����ֵ:CVxTimespan::TTimeDiff
	
		�����б�:
	************************************/
	TTimeDiff TotalMicroSeconds() const;

	/************************************
		����: ��΢�����ʽ�������С������
	
		����ֵ:int 0��999999
	
		�����б�:
	************************************/
	int Useconds() const;

	// ����ת΢��ı���
	static const TTimeDiff MILLISECONDS									= 1000;

	// ��ת΢��ı���
	static const TTimeDiff SECONDS										= 1000*MILLISECONDS;

	// ��ת΢��ı���
	static const TTimeDiff MINUTES										= 60*SECONDS;

	// Сʱת΢��ı���
	static const TTimeDiff HOURS										= 60*MINUTES;

	// ��ת΢��ı���
	static const TTimeDiff DAYS											= 24*HOURS;

private:
	/**
	 * ʱ���ȱ�ʾ��64λ����
	 */
	TTimeDiff					m_span;
};

#endif	// _D_TIME_SPAN_H_

