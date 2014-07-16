

#ifndef _D_TRACE_H_
#define _D_TRACE_H_


#include "DLogger.h"

#include <assert.h>
#include <sstream>

#ifdef _DEBUG
#include <crtdbg.h>
#else
#include <exception>
#endif

#ifndef D_MODULE_NAME
#error  undefine moudle name error!;
#endif

//////////////////////////////////////////////////////////////////////////
// LOG 宏定义
//////////////////////////////////////////////////////////////////////////

/*
* 关于日志级别的考虑：
* 日志的重要等级，从高到低 { FATAL>CRITICAL>ERROR>WARNING>NOTICE>INFORMATION>DEBUG>TRACE }
* 每个等级的日志在程序内部对应的使用情况如下：
* LOG_FATAL:
*		最高优先级，记录的是系统内部最重要的信息，如果是错误就是致命错误，程序将不能继续运行，
*		需要关闭。如果不是错误，那将是触发程序退出的信息，使用这个级别的日志记录之。
* LOG_CRITICAL:
*		关键日志，记录的是内部较为关键的信息，对于整个系统的运行都将会产生比较大的影响，这类信息
*		在运行过程中也会比较少，目前是在点授权变更记录时和退出时使用。
* LOG_ERROR:
*		错误信息，运行过程中检测到的错误，以及程序内部产生了错误，现在内部使用的也会比较少，
*		个人在数据发现不一致时使用。较多的是反应程序内部的错误。
* LOG_WARNING:
*		告警信息，对应着操作上的错误，如外部请求操作失败，对于程序内部来说是正常的一个情况，内部
*		未发生错误，失败的只是当前的某个操作。如增加某个位号失败，或者上送点值时发现组态不存在等。
* LOG_NOTICE:
*		通知信息，不是特别重要的通知信息（如果这类信息对程序的整个执行产生重大影响，应该使用
*		LOG_CRITICAL），但确实相对于普通信息更为重要一些，发生了一些状况，而且对于这个模块来说是
*		一种被动的接收。如扫描到新的服务实例或者实例下线。
* LOG_INFORMATION:
*		普通提示信息，记录一些外部发起的操作，至少这些操作对程序内部产生了某些影响，如位号的增加，
*		删除等。
* LOG_DEBUG:
*		调试信息，在进行程序调试时使用较多，普通情况下不打开这个开关。这个级别的日志主要在进行程序
*		流程追踪时使用，记录发起调用时的参数以及调用返回时的返回值。纯粹方便程序调试的角度而增加的。
* LOG_TRACE:
*		追踪信息，循环操作，或者相对于调试信息更不重要的日志信息。为什么设定这个级别？
*		更多的考虑是想在这个级别打印一些诸如：接收 发送的详细信息，周期性操作的信息。如果把这类信息
*		合并到Debug级别下，会发现有一大堆这类信息，不方便调试。
*		在很多时候，调试已经完成，很多的Debug日志可以改为Trace级别的日志。
*/

// 最重要信息， 最高优先级日志，进程将很有可能无法继续运行，需要关闭。
#define D_LOG_FATAL(data)			D_LOG_FATAL_WITH_SOURCE(D_MODULE_NAME,data);

// 关键信息，.如果是错误信息，则程序内部已经出现错误
#define D_LOG_CRITICAL(data)		D_LOG_CRITICAL_WITH_SOURCE(D_MODULE_NAME, data)

// 错误， 操作失败，但最为程序整体性将不会受到影响
#define D_LOG_ERROR(data)			D_LOG_ERROR_WITH_SOURCE(D_MODULE_NAME, data)

// 告警， 操作达不到预期的结果
#define D_LOG_WARN(data)			D_LOG_WARNING_WITH_SOURCE(D_MODULE_NAME, data)

// 通知， 比info更高优先级的日志
#define D_LOG_NOTICE(data)			D_LOG_NOTICE_WITH_SOURCE(D_MODULE_NAME, data)

// 信息
#define D_LOG_INFO(data)			D_LOG_INFO_WITH_SOURCE(D_MODULE_NAME, data)

// 调试消息.
#define D_LOG_DEBUG(data)			D_LOG_DEBUG_WITH_SOURCE(D_MODULE_NAME, data)

// 普通trace
#define D_LOG_TRACE(data)			D_LOG_TRACE_WITH_SOURCE(D_MODULE_NAME, data)

//////////////////////////////////////////////////////////////////////////
// assert 相关定义
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define _D_ASSERT_NO_HINT_ assert(false)
#else

// 根据实际需要进行调整，初期建议更改为abort，后期建议定义为空
#define _D_ASSERT_NO_HINT_			\
 {									\
	abort();						\
 }

//#define  _D_ASSERT_NO_HINT_

#endif

#define D_ASSERT( exp )															\
	if ( !(exp) )																\
	{																			\
		D_LOG_FATAL( "assert, file["<<__FILE__<<"] line["<<__LINE__<<"]." );	\
		_D_ASSERT_NO_HINT_;														\
	}

#ifdef _DEBUG
#define _D_ASSERT_(hint)														\
	{																			\
		std::stringstream ss;													\
		ss << hint;																\
		_CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, D_MODULE_NAME,			\
			"%s", ss.str().c_str());											\
	}
#else
// 根据实际需要进行调整，初期建议更改为abort，后期建议定义为空
#define _D_ASSERT_(hint)														\
	{																			\
		abort();																\
	}

// #define _D_ASSERT_(hint)
#endif

/*
exp : 判别式
hint: 提示语句
*/
#define D_ASSERT_EX(exp,hint)													\
	if ( !(exp) )																\
	{																			\
		D_LOG_FATAL("assert, file["<<__FILE__<<"] line["<<__LINE__<<"], "<<hint);\
		_D_ASSERT_(hint);														\
	}

//////////////////////////////////////////////////////////////////////////
// CHECK，检测宏定义
//////////////////////////////////////////////////////////////////////////

/*
D_CHECK(exp, hint) 用于代替if语句
exp  : 判定式
hint : 提示语句
D_CHECK用于检测exp，当exp不成立时，把hint记录到日志中，日志级别是WARN。
*/
#define D_CHECK(exp, hint)														\
	if( !(exp) )																\
	{																			\
		D_LOG_WARN(hint);														\
	}

/*
D_CHECK_EX(exp, hint, nextState)
exp       : 判定式
hint      : 提示语句
nextState : 运行语句
D_CHECK_EX检测exp判定式，当exp不成立时，把hint信息记录到日志中，日志级别是WARN（同D_CHECK）。
并且执行nextState语句。
*/
#define D_CHECK_EX(exp, hint, nextState)											\
	if ( !(exp) )																	\
	{																				\
		D_LOG_WARN(hint);															\
		nextState;																	\
	}

#endif	// _D_TRACE_H_

