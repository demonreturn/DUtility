
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
	// 更新到当前时间
	void Refresh();

	// 返回时间戳的time_t方式的表示，base time是1970年1月1日0点,精度是S
	std::time_t GetTime() const;

	// 返回时间戳的UTC表示方式，base time是1582年10月15日0点,精度是100ns
	TTimeValue GetUtcTime() const;

	// 返回时间戳的微秒表示，base time是1970年1月1日0时
	TTimeValue GetMicroseconds() const;

	DWORD GetMSSeconds() const;

	// 现在的时间与时间戳所表示的时间的差值
	TTimeDiff GetElapsed() const;

	void ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const;

	// 时间戳所表示的时间与当前时间的差值是否大于interval。
	// 时间戳所表示的时间距离现在是否已经逝去了interval
	bool IsTimeElapsed(TTimeDiff interval) const;

	static CDTimeStamp FromEpochTime( std::time_t t );

	static CDTimeStamp FromEpochMillisecond( TTimeValue tv );

	static CDTimeStamp FromUTCTime( TTimeValue tv );

	static CDTimeStamp FromFileTime( UINT32 fileTimeLow,
		UINT32 fileTimeHigh );

	static TTimeValue Resolution();

	static CDTimeStamp GetCurTime();

	//////////////////////////////////////////////////////////////////////////
	// 运算符重载
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
	// 时间戳的64位UTC时间表示,精度是微秒
	TTimeValue					m_ts;
};

#endif // _D_TIMESTAMP_H_

