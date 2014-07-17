

#ifndef _I_D_REACTORIMPL_H_
#define _I_D_REACTORIMPL_H_

#include "DBase.h"
#include "DThread.h"

class IDHandler;

class IDReacotrImpl
{
public:
	/*
	 * �ṩ�������������
	 */
	virtual ~IDReacotrImpl() {}

	/*
	 * �Ǽ�һ��Handler����Ӧ���¼��������ط��䵽������ֵ
	 * �����һ��Handler�ֶ�εǼǲ�ͬ���¼�
	 * pHandler[in] : �Ǽǵ�Handler����
	 * nEvent[in] : Handler��Ӧ���¼�
	 * pIndex[in/out] : ����һ�����ζ����ָ�룬�����ط��䵽������ֵ���������NULL���ʾ����Ҫ��ȡ����ֵ
	 */
	virtual DResult RegisterHandle( IDHandler* phandler, int iEvent, int* pIndex ) = 0;

	/*
	 * ע��һ��Handler����Ӧ���¼�
	 * �����һ��Handler�ֶ��ע����ͬ���¼�
	 * pHandler[in] : �Ǽǵ�Handler����
	 * nEvent[in] : Handler��Ӧ���¼�
	 * pIndex[in] : Handler���䵽������ֵ������һ�����ζ���ָ�룬�������NULL���ʾ�ⲿ�����ṩ����ֵ
	 */
	virtual DResult UnRegisterHandle( IDHandler* phandler, int iEvent, int* pIndex ) = 0;

	/*
	 * Reactor��Ϣѭ���������¼�
	 * ���ز����¼��ľ����
	 */
    virtual int HandleEvents() = 0;

	/*
	 * Reactor��Ϣѭ���������¼�
	 */
	virtual DResult Dispatch() = 0;

	/*
	 * ��Reactor����֪ͨ
	 * nNotifyCmd[in] : ֪ͨ������
	 */
    virtual DResult Notify(int nNotifyCmd) = 0;

	/*
	 * ����TimerQueue
	 */
	virtual void AttachTimerQueue( CDTimerQueue* pTQ ) = 0;

	/*
	 * ����EventQueue
	 */
	virtual void AttachEventQueue( CDEventQueue* pEQ ) = 0;

};

#endif	// _I_D_REACTORIMPL_H_