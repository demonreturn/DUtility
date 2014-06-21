

#ifndef _D_LOG_MESSAGE_H_
#define _D_LOG_MESSAGE_H_


#include "DBase.h"

#include "DTimeStamp.h"

/**
 * CCDLogMessage，表示一条log信息，
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

class CDLogMessage
{
public:
	enum ELogLevel
	{
		// 最重要信息， 最高优先级日志，进程将很有可能无法继续运行，需要关闭。
		LOG_FATAL = 1,

		// 关键信息，.如果是错误信息，则程序内部已经出现错误
		LOG_CRITICAL,

		// 错误， 操作失败，但最为程序整体性将不会受到影响
		LOG_ERROR,

		// 告警， 操作达不到预期的结果
		LOG_WARNING,

		// 通知， 比info更高优先级的日志
		LOG_NOTICE,

		// 信息
		LOG_INFORMATION,

		// 调试消息.
		LOG_DEBUG,

		// 普通trace
		LOG_TRACE,


		LOG_LEVEL_SIZE
	};

	static const char* LOG_LEVEL_NAME[LOG_LEVEL_SIZE];

	CDLogMessage( 
		const CDString& src,
		const CDString& text,
		ELogLevel level,
		const char* pfile,
		const char* fun,
		int line );

	CDLogMessage( const CDLogMessage& msg );


	~CDLogMessage(){}

	const CDString& GetSource() const
	{
		return m_source;
	}

	const CDString& GetText() const
	{
		return m_text;
	}
	
	int GetLevel() const
	{
		return m_level;
	}

	const char* GetLevelName() const;

	const CDTimeStamp& GetTime() const
	{
		return m_time;
	}

	const char* GetSourceFile() const
	{
		return m_file;
	}

	const char* GetFunction() const
	{
		return m_function;
	}

	int GetSourceLine() const
	{
		return m_line;
	}

	D_THREAD_ID GetThreadID() const
	{
		return m_threadID;
	}

	long GetPID() const
	{
		return m_pid;
	}

	static const char* GetLevelName( int level );

	CDLogMessage& operator = ( const CDLogMessage& msg );

	bool operator == ( const CDLogMessage& msg );

private:
	CDString					m_source;

	CDString					m_text;

	ELogLevel					m_level;

	CDTimeStamp					m_time;

	long						m_pid;

	D_THREAD_ID					m_threadID;

	int							m_line;

	const char*					m_file;

	const char*					m_function;
};

#endif	// _D_LOG_MESSAGE_H_