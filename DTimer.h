
#ifndef _D_TIMER_H_
#define _D_TIMER_H_

#include "DBase.h"

class IDTimerSink;
class CDTimeValue;

class CDTimer
{
public:
	CDTimer();

	~CDTimer();

	/*
	* 描述：	定时设置，只设定一次，即现在执行
	* 参数：	pTimerSink [in] 定时器回调接口
	*			interval [in] 延时执行时间
	*
	* 返回值：	D_OK 成功，其他 失败
	*/
	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& interval );

	/*
	* 描述：	定时设置,当前开始执行
	* 参数：	pTimerSink [in] 定时器回调接口
	*			interval [in] 执行的间隔
	*			runTimes [in] 执行次数，-1表示始终轮询
	*
	* 返回值：	D_OK 成功，其他 失败
	*/

	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& interval,
		int runTimes );

	/*
	* 描述：	定时设置
	* 参数：	pTimerSink [in] 定时器回调接口
	*			delay [in] 将来某一时间执行
	*			interval [in] 执行的间隔
	*			runTimes [in] 执行次数，-1表示始终轮询
	*
	* 返回值：	D_OK 成功，其他 失败
	*/
	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& delay,
		const CDTimeValue& interval,
		int runTimes = -1 );

	/*
	* 描述：	取消一个定时器
	* 参数：	无
	* 返回值：	VOID
	*/
	void CancleTimer();
};

#endif	// _D_TIMER_H_

