
#ifndef _D_TIMESTAMP_H_
#define _D_TIMESTAMP_H_

#include "DBase.h"

#include <ctime>

class DUTILITY_API CDTimeStamp
{
public:
	typedef long long TTimeValue;
	typedef long long TTimeDiff;

public:
	CDTimeStamp();

	CDTimeStamp( TTimeValue tv );

	CDTimeStamp( const CDTimeStamp& src );

	CDTimeStamp( const timeval& tv );

	~CDTimeStamp();

public:
	// ���µ���ǰʱ��
	void Refresh();

	// ����ʱ�����time_t��ʽ�ı�ʾ��base time��1970��1��1��0��,������S
	std::time_t GetTime() const;

	// ����ʱ�����UTC��ʾ��ʽ��base time��1582��10��15��0��,������100ns
	TTimeValue GetUtcTime() const;

	// ����ʱ�����΢���ʾ��base time��1970��1��1��0ʱ
	TTimeValue GetMicroseconds() const;

	DWORD GetMSSeconds() const;

	// ���ڵ�ʱ����ʱ�������ʾ��ʱ��Ĳ�ֵ
	TTimeDiff GetElapsed() const;

	void ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const;

	// ʱ�������ʾ��ʱ���뵱ǰʱ��Ĳ�ֵ�Ƿ����interval��
	// ʱ�������ʾ��ʱ����������Ƿ��Ѿ���ȥ��interval
	bool IsTimeElapsed(TTimeDiff interval) const;

	static CDTimeStamp FromEpochTime( std::time_t t );

	static CDTimeStamp FromEpochMillisecond( TTimeValue tv );

	static CDTimeStamp FromUTCTime( TTimeValue tv );

	static CDTimeStamp FromFileTime( UINT32 fileTimeLow,
		UINT32 fileTimeHigh );

	static TTimeValue Resolution();

	static CDTimeStamp GetCurTime();

	//////////////////////////////////////////////////////////////////////////
	// ���������
	bool operator == (const CDTimeStamp& ts) const;
	bool operator != (const CDTimeStamp& ts) const;
	bool operator >  (const CDTimeStamp& ts) const;
	bool operator >= (const CDTimeStamp& ts) const;
	bool operator <  (const CDTimeStamp& ts) const;
	bool operator <= (const CDTimeStamp& ts) const;

	CDTimeStamp  operator +  (TTimeDiff d) const;
	CDTimeStamp  operator -  (TTimeDiff d) const;
	TTimeDiff     operator -  (const CDTimeStamp& ts) const;
	CDTimeStamp& operator += (TTimeDiff d);
	CDTimeStamp& operator -= (TTimeDiff d);

	CDTimeStamp& operator = (const CDTimeStamp& other);
	CDTimeStamp& operator = (TTimeValue tv);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

private:
	// ʱ�����64λUTCʱ���ʾ,������΢��
	TTimeValue					m_ts;
};

#endif // _D_TIMESTAMP_H_

