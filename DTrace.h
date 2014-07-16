

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
// LOG �궨��
//////////////////////////////////////////////////////////////////////////

/*
* ������־����Ŀ��ǣ�
* ��־����Ҫ�ȼ����Ӹߵ��� { FATAL>CRITICAL>ERROR>WARNING>NOTICE>INFORMATION>DEBUG>TRACE }
* ÿ���ȼ�����־�ڳ����ڲ���Ӧ��ʹ��������£�
* LOG_FATAL:
*		������ȼ�����¼����ϵͳ�ڲ�����Ҫ����Ϣ������Ǵ�������������󣬳��򽫲��ܼ������У�
*		��Ҫ�رա�������Ǵ����ǽ��Ǵ��������˳�����Ϣ��ʹ������������־��¼֮��
* LOG_CRITICAL:
*		�ؼ���־����¼�����ڲ���Ϊ�ؼ�����Ϣ����������ϵͳ�����ж���������Ƚϴ��Ӱ�죬������Ϣ
*		�����й�����Ҳ��Ƚ��٣�Ŀǰ���ڵ���Ȩ�����¼ʱ���˳�ʱʹ�á�
* LOG_ERROR:
*		������Ϣ�����й����м�⵽�Ĵ����Լ������ڲ������˴��������ڲ�ʹ�õ�Ҳ��Ƚ��٣�
*		���������ݷ��ֲ�һ��ʱʹ�á��϶���Ƿ�Ӧ�����ڲ��Ĵ���
* LOG_WARNING:
*		�澯��Ϣ����Ӧ�Ų����ϵĴ������ⲿ�������ʧ�ܣ����ڳ����ڲ���˵��������һ��������ڲ�
*		δ��������ʧ�ܵ�ֻ�ǵ�ǰ��ĳ��������������ĳ��λ��ʧ�ܣ��������͵�ֵʱ������̬�����ڵȡ�
* LOG_NOTICE:
*		֪ͨ��Ϣ�������ر���Ҫ��֪ͨ��Ϣ�����������Ϣ�Գ��������ִ�в����ش�Ӱ�죬Ӧ��ʹ��
*		LOG_CRITICAL������ȷʵ�������ͨ��Ϣ��Ϊ��ҪһЩ��������һЩ״�������Ҷ������ģ����˵��
*		һ�ֱ����Ľ��ա���ɨ�赽�µķ���ʵ������ʵ�����ߡ�
* LOG_INFORMATION:
*		��ͨ��ʾ��Ϣ����¼һЩ�ⲿ����Ĳ�����������Щ�����Գ����ڲ�������ĳЩӰ�죬��λ�ŵ����ӣ�
*		ɾ���ȡ�
* LOG_DEBUG:
*		������Ϣ���ڽ��г������ʱʹ�ý϶࣬��ͨ����²���������ء�����������־��Ҫ�ڽ��г���
*		����׷��ʱʹ�ã���¼�������ʱ�Ĳ����Լ����÷���ʱ�ķ���ֵ�����ⷽ�������ԵĽǶȶ����ӵġ�
* LOG_TRACE:
*		׷����Ϣ��ѭ����������������ڵ�����Ϣ������Ҫ����־��Ϣ��Ϊʲô�趨�������
*		����Ŀ�����������������ӡһЩ���磺���� ���͵���ϸ��Ϣ�������Բ�������Ϣ�������������Ϣ
*		�ϲ���Debug�����£��ᷢ����һ���������Ϣ����������ԡ�
*		�ںܶ�ʱ�򣬵����Ѿ���ɣ��ܶ��Debug��־���Ը�ΪTrace�������־��
*/

// ����Ҫ��Ϣ�� ������ȼ���־�����̽����п����޷��������У���Ҫ�رա�
#define D_LOG_FATAL(data)			D_LOG_FATAL_WITH_SOURCE(D_MODULE_NAME,data);

// �ؼ���Ϣ��.����Ǵ�����Ϣ��������ڲ��Ѿ����ִ���
#define D_LOG_CRITICAL(data)		D_LOG_CRITICAL_WITH_SOURCE(D_MODULE_NAME, data)

// ���� ����ʧ�ܣ�����Ϊ���������Խ������ܵ�Ӱ��
#define D_LOG_ERROR(data)			D_LOG_ERROR_WITH_SOURCE(D_MODULE_NAME, data)

// �澯�� �����ﲻ��Ԥ�ڵĽ��
#define D_LOG_WARN(data)			D_LOG_WARNING_WITH_SOURCE(D_MODULE_NAME, data)

// ֪ͨ�� ��info�������ȼ�����־
#define D_LOG_NOTICE(data)			D_LOG_NOTICE_WITH_SOURCE(D_MODULE_NAME, data)

// ��Ϣ
#define D_LOG_INFO(data)			D_LOG_INFO_WITH_SOURCE(D_MODULE_NAME, data)

// ������Ϣ.
#define D_LOG_DEBUG(data)			D_LOG_DEBUG_WITH_SOURCE(D_MODULE_NAME, data)

// ��ͨtrace
#define D_LOG_TRACE(data)			D_LOG_TRACE_WITH_SOURCE(D_MODULE_NAME, data)

//////////////////////////////////////////////////////////////////////////
// assert ��ض���
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define _D_ASSERT_NO_HINT_ assert(false)
#else

// ����ʵ����Ҫ���е��������ڽ������Ϊabort�����ڽ��鶨��Ϊ��
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
// ����ʵ����Ҫ���е��������ڽ������Ϊabort�����ڽ��鶨��Ϊ��
#define _D_ASSERT_(hint)														\
	{																			\
		abort();																\
	}

// #define _D_ASSERT_(hint)
#endif

/*
exp : �б�ʽ
hint: ��ʾ���
*/
#define D_ASSERT_EX(exp,hint)													\
	if ( !(exp) )																\
	{																			\
		D_LOG_FATAL("assert, file["<<__FILE__<<"] line["<<__LINE__<<"], "<<hint);\
		_D_ASSERT_(hint);														\
	}

//////////////////////////////////////////////////////////////////////////
// CHECK�����궨��
//////////////////////////////////////////////////////////////////////////

/*
D_CHECK(exp, hint) ���ڴ���if���
exp  : �ж�ʽ
hint : ��ʾ���
D_CHECK���ڼ��exp����exp������ʱ����hint��¼����־�У���־������WARN��
*/
#define D_CHECK(exp, hint)														\
	if( !(exp) )																\
	{																			\
		D_LOG_WARN(hint);														\
	}

/*
D_CHECK_EX(exp, hint, nextState)
exp       : �ж�ʽ
hint      : ��ʾ���
nextState : �������
D_CHECK_EX���exp�ж�ʽ����exp������ʱ����hint��Ϣ��¼����־�У���־������WARN��ͬD_CHECK����
����ִ��nextState��䡣
*/
#define D_CHECK_EX(exp, hint, nextState)											\
	if ( !(exp) )																	\
	{																				\
		D_LOG_WARN(hint);															\
		nextState;																	\
	}

#endif	// _D_TRACE_H_

