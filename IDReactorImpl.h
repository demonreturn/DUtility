

#ifndef _I_D_REACTORIMPL_H_
#define _I_D_REACTORIMPL_H_

#include "DBase.h"
#include "DThread.h"

class IDHandler;

class IDReacotrImpl
{
public:
	/*
	 * 提供对派生类的销毁
	 */
	virtual ~IDReacotrImpl() {}

	/*
	 * 登记一个Handler及对应的事件，并返回分配到的索引值
	 * 允许对一个Handler分多次登记不同的事件
	 * pHandler[in] : 登记的Handler对象
	 * nEvent[in] : Handler对应的事件
	 * pIndex[in/out] : 传入一个整形对象的指针，并返回分配到的索引值。如果传入NULL则表示不需要获取索引值
	 */
	virtual DResult RegisterHandle( IDHandler* phandler, int iEvent, int* pIndex ) = 0;

	/*
	 * 注销一个Handler及对应的事件
	 * 允许对一个Handler分多次注销不同的事件
	 * pHandler[in] : 登记的Handler对象
	 * nEvent[in] : Handler对应的事件
	 * pIndex[in] : Handler分配到的索引值，传入一个整形对象指针，如果传入NULL则表示外部不能提供索引值
	 */
	virtual DResult UnRegisterHandle( IDHandler* phandler, int iEvent, int* pIndex ) = 0;

	/*
	 * Reactor消息循环，捕获事件
	 * 返回产生事件的句柄数
	 */
    virtual int HandleEvents() = 0;

	/*
	 * Reactor消息循环，分派事件
	 */
	virtual DResult Dispatch() = 0;

	/*
	 * 向Reactor发送通知
	 * nNotifyCmd[in] : 通知命令字
	 */
    virtual DResult Notify(int nNotifyCmd) = 0;

	/*
	 * 附加TimerQueue
	 */
	virtual void AttachTimerQueue( CDTimerQueue* pTQ ) = 0;

	/*
	 * 附加EventQueue
	 */
	virtual void AttachEventQueue( CDEventQueue* pEQ ) = 0;

};

#endif	// _I_D_REACTORIMPL_H_