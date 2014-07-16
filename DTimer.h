
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
	* ������	��ʱ���ã�ֻ�趨һ�Σ�������ִ��
	* ������	pTimerSink [in] ��ʱ���ص��ӿ�
	*			interval [in] ��ʱִ��ʱ��
	*
	* ����ֵ��	D_OK �ɹ������� ʧ��
	*/
	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& interval );

	/*
	* ������	��ʱ����,��ǰ��ʼִ��
	* ������	pTimerSink [in] ��ʱ���ص��ӿ�
	*			interval [in] ִ�еļ��
	*			runTimes [in] ִ�д�����-1��ʾʼ����ѯ
	*
	* ����ֵ��	D_OK �ɹ������� ʧ��
	*/

	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& interval,
		int runTimes );

	/*
	* ������	��ʱ����
	* ������	pTimerSink [in] ��ʱ���ص��ӿ�
	*			delay [in] ����ĳһʱ��ִ��
	*			interval [in] ִ�еļ��
	*			runTimes [in] ִ�д�����-1��ʾʼ����ѯ
	*
	* ����ֵ��	D_OK �ɹ������� ʧ��
	*/
	DResult ScheduleTimer(
		IDTimerSink* pTimerSink,
		const CDTimeValue& delay,
		const CDTimeValue& interval,
		int runTimes = -1 );

	/*
	* ������	ȡ��һ����ʱ��
	* ������	��
	* ����ֵ��	VOID
	*/
	void CancleTimer();
};

#endif	// _D_TIMER_H_

