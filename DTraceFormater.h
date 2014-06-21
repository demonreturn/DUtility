
#ifndef _D_TRACE_FORMATER_H_
#define _D_TRACE_FORMATER_H_

#include "DBase.h"

class CDInetAddress;

class CDTraceFormator
{
public:
	/*
	 * 写入内容的表现形式
	 *
	 * <HEX>, 16进制
	 * <DECIMAL>, 10进制
	*/
	typedef enum tag_Ordix
	{
		HEX     = 0,
		DECIMAL = 1
	} Ordix;

public:
	CDTraceFormator( char* pbuffer, DWORD dwBufSize );

public:
	CDTraceFormator& operator << ( char cValue );

	CDTraceFormator& operator << ( BYTE cbValue );

	CDTraceFormator& operator << ( short sValue );

	CDTraceFormator& operator << ( WORD wValue );

	CDTraceFormator& operator << ( int iValue );

	CDTraceFormator& operator << ( UINT iValue );

	CDTraceFormator& operator << ( long lValue );

	CDTraceFormator& operator << ( LONGLONG llValue );

	CDTraceFormator& operator << ( DWORD dwValue );

	CDTraceFormator& operator << ( float fValue );

	CDTraceFormator& operator << ( double dValue );

	CDTraceFormator& operator << ( const char* pszValue );

	CDTraceFormator& operator << ( void* lpValue );

	CDTraceFormator& operator << ( const CDString& strValue );

	CDTraceFormator& operator << ( const CDInetAddress& address );

	CDTraceFormator& operator << ( Ordix ordixValue );

	operator char* ();

private:
	void SetHexFlag( bool bHex );

	bool GetHexFlag() const;

	void AdvanceBuffer( const char* pBuffer );

private:
	bool						m_bHex;
	char*						m_pBuffer;
	DWORD						m_dwBufferSize;
	DWORD						m_dwPos;
};

#endif	// _D_TRACE_FORMATER_H_

