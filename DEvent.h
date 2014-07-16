
#ifndef _D_EVENT_H_
#define _D_EVENT_H_

#include "DBase.h"
#include "DOSLock.h"

class CDTimeValue;
class CDEvent
{
public:
	//�ں˶�������
	enum MANUAL_STATE
	{
		MANUAL_STATE_AUTOEVENT		= 0,	//�Զ��¼�����
		MANUAL_STATE_MANUALEVENT	= 1,	//�ֶ��¼�����
	};

	//�ں˶����ʼ״̬
	enum INITIIAL_STATE
	{
		INITIIAL_STATE_NOSIGNAL		= 0,	//δ֪ͨ��״̬
		INITIIAL_STATE_SIGNAL		= 1,	//֪ͨ��״̬
	};

	CDEvent(
		INT nManualReset = MANUAL_STATE_AUTOEVENT,
		INT nInitialState = INITIIAL_STATE_NOSIGNAL,
		LPCSTR pszName = 0,
		LPVOID pArg = 0 );

	virtual ~CDEvent();

	/*
	������		����¼��ں˶�����
	*/
	D_EVENT GetHandle() const;

	/*
	������		�ȴ��¼��ں˶���
	*/
	int Wait();

	/*
	������		�ȴ��¼��ں˶���һ��ʱ��
	*/
	int Wait( const CDTimeValue& timeout );

	/*
	������		�����¼��ں˶���Ϊ֪ͨ״̬
	*/
	int Signal();

	/*
	������		��ͣ
	*/
	int Pulse();

	/*
	������		���ã���Ҫ�����ֶ�������
	*/
	int Reset();

private:
	/*
	������		�ݻ��¼��ں˶���
	*/
	int Remove();

protected:
	D_EVENT						m_eventHandle;

private:
	CDEvent( const CDEvent& );
	CDEvent& operator = ( const CDEvent& );
};

#endif	// _D_EVENT_H_

