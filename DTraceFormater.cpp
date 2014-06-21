#include "DTraceFormater.h"

#include "DInetAddress.h"
#include "DOSMemory.h"
#include "DTraceDefine.h"


CDTraceFormator::CDTraceFormator( char* pbuffer, DWORD dwBufSize )
	: m_pBuffer( pbuffer )
	, m_dwBufferSize( dwBufSize )
	, m_dwPos( 0 )
	, m_bHex( false )
{

}

void CDTraceFormator::SetHexFlag( bool bHex )
{
	m_bHex = bHex;
}

bool CDTraceFormator::GetHexFlag() const
{
	return m_bHex;
}

void CDTraceFormator::AdvanceBuffer( const char* pBuffer )
{
	if ( NULL != pBuffer )
	{
		DWORD dwLength = D_OS::Strlen( pBuffer, m_dwBufferSize );

		if ( dwLength > ( m_dwBufferSize - m_dwPos - D_TRACE_RESERVE_DATA_LEN ))
		{
			dwLength = m_dwBufferSize - m_dwPos - D_TRACE_RESERVE_DATA_LEN;
		}

		if ( 0 < dwLength )
		{
			D_OS::Memcpy(
				m_pBuffer + m_dwPos * sizeof(char),
				m_dwBufferSize - m_dwPos * sizeof(char),
				(void*)pBuffer,
				dwLength * sizeof(char) );

			m_dwPos += dwLength;
		}
	}
}

CDTraceFormator::operator char*()
{
	return m_pBuffer;
}

CDTraceFormator& CDTraceFormator::operator<<( char cValue )
{
	return (*this << (int)cValue );
}

CDTraceFormator& CDTraceFormator::operator<<( BYTE cbValue )
{
	return (*this << (int)cbValue );
}

CDTraceFormator& CDTraceFormator::operator<<( short sValue )
{
	return (*this << (int)sValue );
}

CDTraceFormator& CDTraceFormator::operator<<( WORD wValue )
{
	return (*this << (int)wValue );
}

CDTraceFormator& CDTraceFormator::operator<<( int iValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		GetHexFlag() ? "%d" : "%08x",
		iValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( UINT iValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		GetHexFlag() ? "%u" : "%08x",
		iValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( long lValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		GetHexFlag() ? "%ld" : "%08x",
		lValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( LONGLONG llValue )
{
	char szValue[128] = { 0 };
	D_ZERO( szValue, 128 );

	D_OS::Sprintf(szValue,
		128,
		GetHexFlag() ? "%lld" : "%08x",
		llValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( DWORD dwValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		GetHexFlag() ? "%lu" : "%08x",
		dwValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( float fValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		"%f",
		fValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( double dValue )
{
	char szValue[64] = { 0 };
	D_ZERO( szValue, 64 );

	D_OS::Sprintf(szValue,
		64,
		"%f",
		dValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( const char* pszValue )
{
	AdvanceBuffer( pszValue );

	return (*this);
}

CDTraceFormator& CDTraceFormator::operator<<( void* lpValue )
{
	return (*this << "0x" << HEX << reinterpret_cast<DWORD>( lpValue) );
}

CDTraceFormator& CDTraceFormator::operator<<( const CDString& strValue )
{
	return (*this << strValue.c_str() );
}

CDTraceFormator& CDTraceFormator::operator<<( const CDInetAddress& address )
{
	return (*this << const_cast<CDInetAddress&>(address).GetStrIP() << ":" << address.GetPort() );
}

CDTraceFormator& CDTraceFormator::operator<<( Ordix ordixValue )
{
	switch ( ordixValue )
	{
	case HEX:
		SetHexFlag( true );
		break;

	case DECIMAL:
		SetHexFlag( false );
		break;
	default:
		break;
	}

	return (*this);
}
