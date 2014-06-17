

#ifndef _D_PROCESS_H_
#define _D_PROCESS_H_

#include "DBase.h"

namespace D_OS
{
	const unsigned long OS_MAX_PROCESS_CMD_LEN = 1024;

	inline long GetProcessID()
	{
#ifdef D_WIN32
		return ::GetCurrentProcessId();
#elif defined( D_LINUX)		// linux  实现
		return getpid();
#endif
	}

	inline const char* GetExecName()
	{
		static char s_szCmd[ OS_MAX_PROCESS_CMD_LEN ] = { 0 };

		static char* s_pszCmd = NULL;

#ifdef D_WIN32
		if ( NULL == s_pszCmd )
		{
			::GetModuleFileNameA(
				NULL,
				s_szCmd,
				sizeof( s_szCmd ) );

			s_pszCmd = s_szCmd;
		}
#elif defined( D_LINUX)		// linux  实现
		char szPidFile[OS_MAX_PROCESS_CMD_LEN];
		memset( szPidFile, 0, sizeof(szPidFile) );

		if ( NULL == s_pszCmd )
		{
			FILE* pPipe = NULL;

			// 设置进程所在proc路径
			::sprintf(
				szPidFile, 
				"/proc/%d", 
				getpid() );    
			char szCurrentPath[256]={0};
			char* pPath = ::getcwd( szCurrentPath, 256 );
			if( pPath == NULL )
			{
				//error
			}

			// 将当前路径设为进程路径
			if( -1 != ::chdir(szPidFile) ) 
			{
				memset( szPidFile, 0, sizeof(szPidFile) );

				//      域1   域2  域3  域4  域5  域6  域7   域8   域9 域10        域11
				// lrwxrwxrwx  1  root  root  0   10月  26  16:35  exe  ->   /sbin/dhclient

				// 把shell命令执行结果的 "域11" 打印出来, 如上所示, 即命令行"/sbin/dhclient\n"
				::snprintf(
					szPidFile,
					OS_MAX_PROCESS_CMD_LEN, 
					"ls -l | grep exe | awk '{print $11}'" );

				// 打开程序对应的pipe
				pPipe = ::popen(
					szPidFile,
					"r" );

				if( NULL == pPipe ) 
				{
					::chdir(szCurrentPath);
					return NULL; 
				}

				//读取shell命令执行结果到字符串<s_szCmdName>中 
				if( NULL == fgets(s_szCmd, OS_MAX_PROCESS_CMD_LEN, pPipe) ) 
				{ 
					::pclose( pPipe );
					::chdir(szCurrentPath);
					return NULL;
				}

				::pclose( pPipe );     //popen开启的fd必须要pclose关闭 

				// 把'\n'从<s_szCmdName>中去掉
				DWORD dwLen = ::strnlen(s_szCmd, OS_MAX_PROCESS_CMD_LEN);

				if (  dwLen > 0 && s_szCmd[ dwLen - 1 ] == 0x0A )
				{
					s_szCmd[ dwLen - 1 ] = 0x00;
				}					
				//SC_ZERO( 
				//	s_szCmdName + ::strnlen(s_szCmdName, SC_OS_PROCESS_CMD_BUF_LEN), 
				//	SC_OS_PROCESS_CMD_BUF_LEN - ::strnlen(s_szCmdName, SC_OS_PROCESS_CMD_BUF_LEN) );

				s_pszCmd = s_szCmd;
				::chdir(szCurrentPath);
			}
		}
#endif

		return s_pszCmd;
	}

	inline const char* GetProcessName()
	{
		const char* pExeName = GetExecName();
		if ( NULL != pExeName )
		{
			const char* pchFind = pExeName + ::strnlen(pExeName, OS_MAX_PROCESS_CMD_LEN );

			while( (pchFind > pExeName) && 
				('\\' != *pchFind) )
			{
				pchFind--;
			}

			if( '\\' == *pchFind )
			{
				pchFind++;
			}

			return pchFind;
		}
		else
		{
			return "UnknowProcess";
		}
	}

	inline const char* GetExecDir()
	{
		static char s_exExecDir[OS_MAX_PROCESS_CMD_LEN] = { 0 };
		static char* s_pexExecDir = NULL;

		if ( NULL != s_pexExecDir )
		{
			const char* pszExecCmdName = GetExecName();
			const char* pszProcessName = GetProcessName();

			const char* poffset = ::strstr( pszExecCmdName, pszProcessName );

			::strncpy_s( s_exExecDir, pszExecCmdName, poffset - pszExecCmdName );

			s_pexExecDir = s_exExecDir;
		}

		return s_pexExecDir;
	}

	inline int SetProcessPriority( DHANDLE prohandle, DWORD dwPriority )
	{
#ifdef D_WIN32
		BOOL bRet = ::SetPriorityClass( prohandle, dwPriority );

		return bRet ? 0 : -1;

#elif defined( D_LINUX)		// linux  实现
		return -1;
#endif
	}

	inline DWORD GetProcessPriority( DHANDLE prohandle )
	{
#ifdef D_WIN32
		return ::GetPriorityClass( prohandle );
#elif defined( D_LINUX)		// linux  实现
		return 0;
#endif
	}
}

#endif //_D_PROCESS_H_

