
#ifndef _D_TIME_ZONE_H_
#define _D_TIME_ZONE_H_

#include "DBase.h"
#include "DTimeStamp.h"

class CDTimeZone
{
public:
	/************************************
		描述: 返回本地时间与UTC时间的时差，单位秒。
		本地时间 = UTC时间 + UtcOffset + Dst
	
		返回值:int   时差秒值
	
		参数列表:
	************************************/
	static int UtcOffset();

	/************************************
		描述: 如果系统使用了夏令时，返回夏令时的时差，单位秒
	
		返回值:int
	
		参数列表:
	************************************/
	static int Dst();

	/************************************
		描述: 返回给定时间戳是否是夏令时。使用了C运行时库的localtime
	
		返回值:bool
	
		参数列表:
		const CVxTimeStamp & timestamp
	************************************/
	static bool IsDst(const CDTimeStamp& timestamp);

	/************************************
		描述: 返回当前时区与UTC之间的差值，单位秒。utcOffset + dst
	
		返回值:int
	
		参数列表:
	************************************/
	static int Tzd();
};

#endif	// _D_TIME_ZONE_H_

