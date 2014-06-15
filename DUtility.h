
/************************************************************************/
/*                          DUtility                                    */
/************************************************************************/

#ifndef _D_UTILITY_DEFINE_H_
#define _D_UTILITY_DEFINE_H_

/* �趨select�Ⱥ������������Ϊ2048 - ԭ64 */
#ifdef D_WIN32

#ifdef FD_SETSIZE
	#define FD_SETSIZE
#endif // FD_SETSIZE

#define FD_SETSIZE 2048
#include <WinSock2.h>

#endif // D_WIN32


// ͷ�ļ����ö���
#ifdef D_WIN32
	#include <string.h>
	#include <direct.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <limits.h>
	#include <stddef.h>
	#include <stdarg.h>
	#include <signal.h>
	#include <errno.h>
	#include <wchar.h>

	#include <crtdbg.h>
	#include <process.h>
#elif defined( D_LINUX )
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <limits.h>
	#include <stdarg.h>
	#include <time.h>
	#include <signal.h>
	#include <sys/stat.h>
	#include <sys/fcntl.h>
	#include <pthread.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <ctype.h>
	#include <assert.h>
	#include <netinet/tcp.h>
	#include <semaphore.h>
	#include <dlfcn.h>
#endif

// ����ͷ�ļ�����
#include <fcntl.h>
#include <memory>
#include <utility>
#include <algorithm>
#include <utility>
#include <set> 
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stack>

#ifdef DUTILITY_EXPORTS
#define DUTILITY_API __declspec(dllexport)
#else
#define DUTILITY_API __declspec(dllimport)
#endif

// export import defines
#ifdef D_WIN32
	#if( defined( _USERDLL) || defined(DUTILITY_EXPORTS) )
		#define DUTILITY_API __declspec( dllexport )
	#else
		#define DUTILITY_API __declspec( dllimport )
	#endif
#else
	#define DUTILITY_EXPORT
#endif // D_WIN32

/*
 * �ָ�������
 */
#ifdef D_WIN32
#define D_OS_SEPARATE	'\\'
#elif defined( D_LINUX)		// linux  ʵ��
#define D_OS_SEPARATE	'/'	
#endif

// ���ü��궨��
/* ���ĳbit��û�б����� */
#ifndef D_BIT_ENABLED
#define D_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif	// D_BIT_ENABLED

/* ���ĳbit��û�б����� */
#ifndef D_BIT_DISABLED
#define D_BIT_DISABLED( dword, bit ) ( ((dword) & (bit)) == 0 )
#endif	// D_BIT_DISABLED

/* ���ĳbit��ֵ�Ƿ���<mask>��� */
#ifndef D_BIT_CMP_MASK
#define D_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// D_BIT_CMP_MASK

/* ����ĳbit */
#ifndef D_SET_BITS
#define D_SET_BITS( dword, bits ) ( dword |= (bits) )
#endif	// D_SET_BITS

/* ����ĳbit */
#ifndef D_CLR_BITS
#define D_CLR_BITS( dword, bits ) ( dword &= ~(bits) )
#endif	// D_CLR_BITS

/* ɾ��һ��ָ�벢��ΪNULL */
#ifndef D_DELETE
#define D_DELETE( p )			\
	do								\
	{								\
	if ( NULL != p )			\
		{							\
		delete p;				\
		p = NULL;				\
		}							\
	} while ( 0 )
#endif	// D_DELETE

/* ɾ��һ��ָ�����鲢��ΪNULL */
#ifndef D_ARRAY_DELETE
#define D_ARRAY_DELETE( pArray )	\
	do									\
	{									\
	if ( NULL != pArray )			\
		{								\
		delete []pArray;			\
		pArray = NULL;				\
		}								\
	} while( 0 )
#endif	// D_ARRAY_DELETE

/* �жϵ�ǰֵ�Ƿ�Ϊ��ʧ�ܡ� */
#define D_FAILED( rResult ) ( rResult != D_OK )

/* �жϵ�ǰֵ�Ƿ�Ϊ���ɹ��� */
#define D_SUCCEEDED( rResult ) ( rResult == D_OK )

/* ���<length>��'0' */
#define D_ZERO( psz, length ) memset( psz, 0, length )

#endif	// _D_UTILITY_DEFINE_H_


