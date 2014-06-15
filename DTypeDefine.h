

#ifndef _D_TYPE_DEFINE_H_
#define _D_TYPE_DEFINE_H_

#include "DPlantform.h"
#include "DUtility.h"

/*
 * linux下，基本数据类型的定义
 */
#ifdef D_LINUX
	typedef long long				LONGLONG;
	typedef short					SHORT;
	typedef double					DOUBLE;
	typedef unsigned long			DWORD;
	typedef long					LONG;
	typedef int						BOOL;
	typedef unsigned char			BYTE;
	typedef unsigned short			WORD;
	typedef float					FLOAT;
	typedef int						INT;
	typedef unsigned int			UINT;
	typedef FLOAT*					PFLOAT;
	typedef BOOL*					LPBOOL;
	typedef int*					LPINT;
	typedef WORD*					LPWORD;
	typedef long*					LPLONG;
	typedef DWORD*					LPDWORD;
	typedef unsigned int*			LPUINT;
	typedef void					VOID;
	typedef void*					LPVOID;
	typedef const void*				LPCVOID;
	typedef char					CHAR;
	typedef char					TCHAR;
	typedef unsigned short			WCHAR;
	typedef const char*				LPCSTR;
	typedef char*					LPSTR;
	typedef const unsigned short*	LPCWSTR;
	typedef unsigned short*			LPWSTR;
	typedef BYTE*					LPBYTE;
	typedef const BYTE*				LPCBYTE;

	typedef unsigned long long		ULONGLONG;

	#ifndef FALSE
		#define FALSE 0
	#endif

	#ifndef TRUE
		#define TRUE 1
	#endif
#endif

/* DUtility专用返回值类型 */
typedef long DResult;

#ifdef D_WIN32
	struct iovec
	{
		DWORD iov_len;	
		char* iov_base;
	};

	#define D_IOV_MAX 64

#elif defined( D_LINUX )
	#ifndef IOV_MAX
		#define IOV_MAX 16
	#endif	// IOV_MAX

	#define D_IOV_MAX IOV_MAX
#endif	// D_WIN32

#ifdef D_WIN32
	#define EWOULDBLOCK             WSAEWOULDBLOCK
	#define EINPROGRESS             WSAEINPROGRESS
	#define EALREADY                WSAEALREADY
	#define ENOTSOCK                WSAENOTSOCK
	#define EDESTADDRREQ            WSAEDESTADDRREQ
	#define EMSGSIZE                WSAEMSGSIZE
	#define EPROTOTYPE              WSAEPROTOTYPE
	#define ENOPROTOOPT             WSAENOPROTOOPT
	#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
	#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
	#define EOPNOTSUPP              WSAEOPNOTSUPP
	#define EPFNOSUPPORT            WSAEPFNOSUPPORT
	#define EAFNOSUPPORT            WSAEAFNOSUPPORT
	#define EADDRINUSE              WSAEADDRINUSE
	#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
	#define ENETDOWN                WSAENETDOWN
	#define ENETUNREACH             WSAENETUNREACH
	#define ENETRESET               WSAENETRESET
	#define ECONNABORTED            WSAECONNABORTED
	#define ECONNRESET              WSAECONNRESET
	#define ENOBUFS                 WSAENOBUFS
	#define EIDONN                 WSAEIDONN
	#define ENOTCONN                WSAENOTCONN
	#define ESHUTDOWN               WSAESHUTDOWN
	#define ETOOMANYREFS            WSAETOOMANYREFS
	#define ETIMEDOUT               WSAETIMEDOUT
	#define ECONNREFUSED            WSAECONNREFUSED
	#define ELOOP                   WSAELOOP
	#define EHOSTDOWN               WSAEHOSTDOWN
	#define EHOSTUNREACH            WSAEHOSTUNREACH
	#define EPROCLIM                WSAEPROCLIM
	#define EUSERS                  WSAEUSERS
	#define EDQUOT                  WSAEDQUOT
	#define ESTALE                  WSAESTALE
	#define EREMOTE                 WSAEREMOTE
#elif defined( D_LINUX )
	#define EWOULDBLOCK				EAGAIN
	#ifndef SOCKET_ERROR
		#define SOCKET_ERROR		-1
	#endif	// SOCKET_ERROR

#endif	// D_WIN32

/*
 * 句柄相关
 */
#ifdef D_WIN32
	typedef HANDLE DHANDLE;
	typedef SOCKET DSOCKET;

	#define D_INVALID_HANDLE		INVALID_HANDLE_VALUE
	#define D_SD_RECEIVE			SD_RECEIVE
	#define D_SD_SEND				SD_SEND
	#define D_SD_BOTH				SD_BOTH
#elif defined( D_LINUX )
	typedef int DHANDLE;
	typedef int DSOCKET;

	#define D_INVALID_HANDLE		-1
	#define D_SD_RECEIVE			0
	#define D_SD_SEND				1
	#define D_SD_BOTH				2
#endif

/*
* D_INLINE的重定义
* gcc 3.x以及4.2, 4.3系列对于凡是inline的函数,
* 如果声明和实现没有在一同一个文件时, link会出错
* 所以, 在linux下把D_INLINE定义为空, 等gnu fix吧
 */
#ifdef D_WIN32
	#define D_INLINE inline

#else	// !D_WIN32
	#define D_INLINE

#endif	// D_WIN32

/*
 * 线程, 锁相关定义
 */
#ifdef D_WIN32
#define D_STD_CALL __stdcall

#elif defined( D_LINUX )
#define D_STD_CALL

#endif	// D_WIN32

/*
 * 线程, 锁相关定义
 */
#ifdef D_WIN32
	typedef DWORD D_THREAD_ID;
	typedef DHANDLE D_THREAD_HANDLE;
	typedef DHANDLE D_SEMAPHONE;
	typedef CRITICAL_SECTION D_THREAD_MUTEX;
	typedef DHANDLE D_PROCESS_HANDLE;

	typedef DWORD D_THR_FUNC_RETURN;
	typedef UINT D_THREAD_RETURN_TYPE;
	typedef D_THREAD_RETURN_TYPE (D_STD_CALL *D_THREAD_FUNC)(void *);
	typedef DHANDLE D_EVENT;

	typedef struct tagDConditionVariable
	{
		long m_lWaiters;

		/// Serialize access to the waiters count.
		D_THREAD_MUTEX m_MutexWaiters;

		/// Queue up threads waiting for the condition to become signaled.
		D_SEMAPHONE* m_pSemWaiters;

		/**
		* An auto reset event used by the broadcast/signal thread to wait
		* for the waiting thread(s) to wake up and get a chance at the
		* semaphore.
		*/
		DHANDLE m_hWaiterDone;

		DWORD m_dwBroadcast;

	} D_CONDITION_VARIABLE;
#elif defined( D_LINUX )
	typedef pthread_t D_THREAD_ID;
	typedef D_THREAD_ID D_THREAD_HANDLE;
	typedef sem_t D_SEMAPHONE;
	typedef pthread_mutex_t D_THREAD_MUTEX;
	typedef pthread_cond_t D_CONDITION_VARIABLE;
	typedef LONG D_PROCESS_HANDLE;

	typedef void* D_THR_FUNC_RETURN;
	// Add by 朱建恒,增加线程函数返回值类型
	typedef void* D_THREAD_RETURN_TYPE;
	typedef D_THREAD_RETURN_TYPE (D_STD_CALL *D_THREAD_FUNC)(void *);
	typedef DHANDLE D_EVENT;

	// 源自win32, winbase.h
	typedef struct tagSECURITY_ATTRIBUTES 
	{
		DWORD nLength;
		LPVOID lpSecurityDeDriptor;
		BOOL bInheritHandle;
	} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
#endif

/*
 * 是否使用IPv6(默认使用IPv4)
 */
#ifdef D_SUPPORT_IPV6
	typedef sockaddr_in6 D_SOCKADDR;
#else
	typedef	sockaddr_in D_SOCKADDR;
#endif	// D_SUPPORT_IPV6

typedef std::string CDString;


/*
 * 文件相关定义
 */
typedef ULONGLONG D_HRTime_T;
//文件偏移量
typedef LONGLONG D_OFF_T;
#ifdef D_WIN32
	#define D_DEFAULT_FILE_MODE	( FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE)	
	#define D_DEFAULT_DLL_MODE		0
	//文件seek操作定义
	#define D_SEEK_BEGIN			FILE_BEGIN
	#define D_SEEK_CUR				FILE_CURRENT
	#define	D_SEEK_END				FILE_END

	typedef HMODULE					DHMODULE;

#elif defined( D_LINUX )
	#define D_DEFAULT_FILE_MODE		0644
	#define D_DEFAULT_DLL_MODE		RTLD_LAZY
	#define D_SEEK_BEGIN			SEEK_SET
	#define D_SEEK_CUR				SEEK_CUR
	#define	D_SEEK_END				SEEK_END

	#define LOCKFILE_FAIL_IMMEDIATELY   0x00000001
	#define LOCKFILE_EXCLUSIVE_LOCK     0x00000002
	#define FILE_ATTRIBUTE_NORMAL       0x00000080 

	#ifndef _O_TEMPORARY
		#define O_TEMPORARY				0x08
	#endif

	//FILETIME 定义
	typedef struct tagFILETIME 
	{
		DWORD dwLowDateTime;   /* low 32 bits  */
		DWORD dwHighDateTime;  /* high 32 bits */
	} FILETIME, *PFILETIME, *LPFILETIME;

	typedef void*					DHMODULE;
	typedef void*					DHPROC;
#endif	// D_WIN32

typedef struct tagFileAttributes
{	
	LONGLONG						llFileSize;		//文件大小
	LONGLONG						llCreateTime;	//create time
	LONGLONG						llModifyTime;	//modify time
}File_Attributes;

#define  MAX_FILENAMELEN			260

#endif	// _D_TYPE_DEFINE_H_