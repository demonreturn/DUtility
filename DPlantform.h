

#ifndef _D_PLANT_FORM_H_
#define _D_PLANT_FORM_H_

// operation system check

// windows 
#ifdef WIN32
	#ifndef D_WIN32
		#define D_WIN32
	#endif	
#endif

// linux
#ifdef LINUX
	#ifndef D_LINUX
		#define D_LINUX
	#endif
#endif

#if ( !defined( D_WIN32) && !defined(D_LINUX) )
	#error Only support win32 and linux
#endif

/*
 *	在win32环境下，主要使用winsock2，所以要求必须是win NT 4.0或
 *	以上系统
 */
#ifdef D_WIN32
	#ifndef D_HAS_WINNT_4_0
		#define D_HAS_WINNT_4_0 1	// 默认当前操作系统为win NT 4.0或以上版本
	#endif	// SC_HAS_WINNT_4_0

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0400
	#endif	// _WIN32_WINNT
#endif

/*
 *	win32编译环境强制VC系列，不支持诸如Boland C++等等
 */

#ifdef D_WIN32
	#ifndef _MSC_VER
		#error on Win32 platform, ONLY support VC to compile
	#endif	// _MSC_VER

	/* 要求多线程版本C++运行库 */
	#ifndef _MT
		#error on Win32 platform, C Run-Time Libraries of multiple thread version is needed
	#endif

	#pragma warning( disable: 4786 )	// identifier was truncated to '255' characters in the browser information(mainly brought by stl)
	#pragma warning( disable: 4355 )	// disable 'this' used in base member initializer list
	#pragma warning( disable: 4275 )	// deriving exported class from non-exported
	#pragma warning( disable: 4251 )	// using non-exported as public in exported
	#pragma warning( disable: 4005 )	// 忽略可能存在重定义

	#if ( _MSC_VER > 1200 )
		#pragma warning( disable: 6258 )	// 忽略使用TerminateThread产生的warning
		#pragma warning( disable: 6326 )
	#endif	// ( _MSC_VER > 1200 )

#endif	// D_WIN32

/*
 * 编译器版本的定义
 */
#ifndef D_COMPILER_VERSION
	#ifdef D_WIN32
		#define D_COMPILER_VERSION _MSC_VER
		#if (D_COMPILER_VERSION < 1600)
			#error VC2010 or later version is needed 
		#endif	// (D_COMPILER_VERSION < 1200)
	#else	// !D_WIN32
		#define D_COMPILER_VERSION 1600
	#endif	// D_WIN32
#endif	// D_COMPILER_VERSION

/*
 *	在linux环境下，需要使用epoll，所以要求kernel是2.6.x或以上
 */
#ifdef D_LINUX
	#include <linux/version.h>
	#if ( !defined(LINUX_VERSION_CODE) || !defined(KERNEL_VERSION) )
		#error macro LINUX_VERSION_CODE & KERNEL_VERSION are both missed, please check your <linux/version.h>
	#endif	//  ( !defined(LINUX_VERSION_CODE) || !defined(KERNEL_VERSION) )

	#if ( LINUX_VERSION_CODE < KERNEL_VERSION(2, 4, 20) )
		#error kernel 2.6.9 or later version is needed
	#endif	// ( LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 9) )
#endif	// D_LINUX

/*
 *	linux环境下，强制gcc 3.4或以上版本
 */
#ifdef D_LINUX
	#if ( !defined(__GNUC__) || !defined(__GNUC_MINOR__) )
		#error on Linux platform, ONLY support gcc to compile 
	#endif	//__GNUC__

	#if( (__GNUC__ < 3) || (__GNUC_MINOR__ < 4) )
		#error gcc 3.4 or later version is needed
	#endif	// ( __GNUC__ < 3 ) || ( __GNUC_MINOR__ < 4 )
#endif	// D_LINUX

#ifdef D_WIN32
	#if (_M_IX86 > 400)
		#define D_HAS_PENTIUM
	#endif // _M_IX86
	#elif defined( __GNUC__ )
		#if ( defined (i386) || defined(__i386__) )
	#define D_HAS_PENTIUM
#endif /* i386 */
#endif	// D_WIN32

#ifdef D_WIN32
	#define D_HAS_BUILTIN_ATOMIC_OP
#elif defined( __GNUC__ ) && defined( SC_HAS_PENTIUM )
	#define D_HAS_BUILTIN_ATOMIC_OP
#endif // CM_WIN32

#define D_USE_TICK_WHELL

#define D_HAS_MUTEX_TIMEOUTS

#endif	// _D_PLANT_FORM_H_