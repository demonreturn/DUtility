

#ifndef _D_DATA_STRUCTOR_H_
#define _D_DATA_STRUCTOR_H_

#include "DBase.h"

// 按用户类型
// 底层类型从 1 ～ 1000
#define D_FRAMEWORK_THREAD 1
// 上层类型从 1000 以上，用户只能在这之上定义
#define D_USER_THREAD 1000

#define D_NETWORK_THREAD D_FRAMEWORK_THREAD
#define D_NETWORK_THREAD1 (D_FRAMEWORK_THREAD + 1)

// 按类型
enum THREAD_TYPE
{

	/*
		基础类型，保留，上层不能直接使用
	*/
	THREAD_BASE = 1 << 1,
	THREAD_TIMERQUEUE = 1 << 2,
	THREAD_EVENTQUEUE = 1 << 3, // 带事件队列的线程类型
	THREAD_REACTOR = 1 << 5, // 带反应器的线程类型，这个类型只能内部使用

	/*
		组合类型，上层可以直接使用，只有这些类型可以指定用户自定义反应器
	*/
	THREAD_WITH_TIMERQUEUE = THREAD_BASE | THREAD_TIMERQUEUE,// 带时间队列
	THREAD_WITH_EVENTQUEUE = THREAD_BASE | THREAD_EVENTQUEUE,// 带事件队列
	THREAD_WITH_TIMERQUEUE_EVENTQUEUE = THREAD_BASE | THREAD_TIMERQUEUE | THREAD_EVENTQUEUE,// 带时间、事件队列

	/*
		这个类型只能底层使用，保留
	*/
	THREAD_WITH_REACTOR = THREAD_BASE | THREAD_TIMERQUEUE | THREAD_EVENTQUEUE | THREAD_REACTOR// 带时间、事件队列和反应器，

};

// 线程对象类型，阻塞 和 非阻塞
// 阻塞 -- 主动对象， 非阻塞 -- 被动对象
enum THREAD_BLOCK_TYPE
{

	THREAD_BLOCK = 1 << 2,
	THREAD_NONBLOCK = 1 << 3

};

// 队列状态
enum QUEUE_STATUS
{
	QUEUE_START = 1 << 1, // 开始
	QUEUE_STOP = 1 << 2 // 停止
};

// 公开的时间值
typedef struct D_TIMEVALUE
{

	// 秒
	LONG Second;

	// 微秒
	LONG USecond;

} D_TIMEVALUE;


#endif	// _D_DATA_STRUCTOR_H_