

#ifndef _D_DATA_STRUCTOR_H_
#define _D_DATA_STRUCTOR_H_

#include "DBase.h"

// ���û�����
// �ײ����ʹ� 1 �� 1000
#define D_FRAMEWORK_THREAD 1
// �ϲ����ʹ� 1000 ���ϣ��û�ֻ������֮�϶���
#define D_USER_THREAD 1000

#define D_NETWORK_THREAD D_FRAMEWORK_THREAD
#define D_NETWORK_THREAD1 (D_FRAMEWORK_THREAD + 1)

// ������
enum THREAD_TYPE
{

	/*
		�������ͣ��������ϲ㲻��ֱ��ʹ��
	*/
	THREAD_BASE = 1 << 1,
	THREAD_TIMERQUEUE = 1 << 2,
	THREAD_EVENTQUEUE = 1 << 3, // ���¼����е��߳�����
	THREAD_REACTOR = 1 << 5, // ����Ӧ�����߳����ͣ��������ֻ���ڲ�ʹ��

	/*
		������ͣ��ϲ����ֱ��ʹ�ã�ֻ����Щ���Ϳ���ָ���û��Զ��巴Ӧ��
	*/
	THREAD_WITH_TIMERQUEUE = THREAD_BASE | THREAD_TIMERQUEUE,// ��ʱ�����
	THREAD_WITH_EVENTQUEUE = THREAD_BASE | THREAD_EVENTQUEUE,// ���¼�����
	THREAD_WITH_TIMERQUEUE_EVENTQUEUE = THREAD_BASE | THREAD_TIMERQUEUE | THREAD_EVENTQUEUE,// ��ʱ�䡢�¼�����

	/*
		�������ֻ�ܵײ�ʹ�ã�����
	*/
	THREAD_WITH_REACTOR = THREAD_BASE | THREAD_TIMERQUEUE | THREAD_EVENTQUEUE | THREAD_REACTOR// ��ʱ�䡢�¼����кͷ�Ӧ����

};

// �̶߳������ͣ����� �� ������
// ���� -- �������� ������ -- ��������
enum THREAD_BLOCK_TYPE
{

	THREAD_BLOCK = 1 << 2,
	THREAD_NONBLOCK = 1 << 3

};

// ����״̬
enum QUEUE_STATUS
{
	QUEUE_START = 1 << 1, // ��ʼ
	QUEUE_STOP = 1 << 2 // ֹͣ
};

// ������ʱ��ֵ
typedef struct D_TIMEVALUE
{

	// ��
	LONG Second;

	// ΢��
	LONG USecond;

} D_TIMEVALUE;


#endif	// _D_DATA_STRUCTOR_H_