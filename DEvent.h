
#ifndef _D_EVENT_H_
#define _D_EVENT_H_

#include "DBase.h"
#include "DOSLock.h"

class CDTimeValue;
class CDEvent
{
public:
	//内核对象类型
	enum MANUAL_STATE
	{
		MANUAL_STATE_AUTOEVENT		= 0,	//自动事件对象
		MANUAL_STATE_MANUALEVENT	= 1,	//手动事件对象
	};

	//内核对象初始状态
	enum INITIIAL_STATE
	{
		INITIIAL_STATE_NOSIGNAL		= 0,	//未通知的状态
		INITIIAL_STATE_SIGNAL		= 1,	//通知的状态
	};

	CDEvent(
		INT nManualReset = MANUAL_STATE_AUTOEVENT,
		INT nInitialState = INITIIAL_STATE_NOSIGNAL,
		LPCSTR pszName = 0,
		LPVOID pArg = 0 );

	virtual ~CDEvent();

	/*
	描述：		获得事件内核对象句柄
	*/
	D_EVENT GetHandle() const;

	/*
	描述：		等待事件内核对象
	*/
	int Wait();

	/*
	描述：		等待事件内核对象一段时间
	*/
	int Wait( const CDTimeValue& timeout );

	/*
	描述：		设置事件内核对象为通知状态
	*/
	int Signal();

	/*
	描述：		暂停
	*/
	int Pulse();

	/*
	描述：		重置，主要用在手动重置中
	*/
	int Reset();

private:
	/*
	描述：		摧毁事件内核对象
	*/
	int Remove();

protected:
	D_EVENT						m_eventHandle;

private:
	CDEvent( const CDEvent& );
	CDEvent& operator = ( const CDEvent& );
};

#endif	// _D_EVENT_H_

