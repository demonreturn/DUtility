
#include "DTimeZone.h"

#include <ctime>
#include <time.h>
#ifdef D_WIN32
#include <Windows.h>
#endif

int CDTimeZone::UtcOffset()
{
#ifdef D_WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation( &tzInfo );

	return -tzInfo.Bias * 60;
#elif defined( D_LINUX)		// linux  实现
	return -timezone;
#endif
}

int CDTimeZone::Dst()
{
#ifdef D_WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation( &tzInfo );
	return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias*60 : 0;
#elif defined( D_LINUX)		// linux  实现
	std::time_t now = std::time(NULL);
	struct std::tm t;
	if ( !localtime_r(&now, &t ))
	{
		return 0;
	}

	return t.tm_isdst == 1 ? 3600 : 0;
#endif
}

bool CDTimeZone::IsDst( const CDTimeStamp& timestamp )
{
	std::time_t time = timestamp.GetTime();
	struct std::tm tms;
	errno_t eno = localtime_s( &tms, &time);
	if (0 != eno)
		return false;
	return tms.tm_isdst > 0;
}

int CDTimeZone::Tzd()
{
	return UtcOffset() + Dst();
}
