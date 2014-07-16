
#include "DTimer.h"
#include "DTimeValue.h"
#include "DTrace.h"

CDTimer::CDTimer()
{
}

CDTimer::~CDTimer()
{
}

DResult CDTimer::ScheduleTimer( 
	IDTimerSink* pTimerSink,
	const CDTimeValue& interval )
{
	DResult dRet = D_OK;

	dRet = this->ScheduleTimer(
		pTimerSink, 
		interval,
		CDTimeValue(),
		1 );

	return dRet;
}

DResult CDTimer::ScheduleTimer(
	IDTimerSink* pTimerSink,
	const CDTimeValue& interval,
	int runTimes )
{
	DResult dRet = D_OK;

	if ( 1 == runTimes )
	{
		dRet = this->ScheduleTimer(
			pTimerSink,
			interval );
	}
	else
	{
		dRet = this->ScheduleTimer(
			pTimerSink,
			CDTimeValue(),
			interval,
			runTimes );
	}

	return dRet;
}

DResult CDTimer::ScheduleTimer( 
	IDTimerSink* pTimerSink,
	const CDTimeValue& delay,
	const CDTimeValue& interval,
	int runTimes /*= -1 */ )
{
	DResult dRet = D_OK;

	D_CHECK_EX( NULL != pTimerSink, "pTimerSink is null", return D_ERROR_NULL_POINTER );

	return dRet;
}
