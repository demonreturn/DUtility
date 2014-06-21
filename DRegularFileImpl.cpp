#include "DRegularFileImpl.h"
#include "DOSMemory.h"
#include "DOSFile.h"
#include "DFile.h"

CDRegularFileImpl::CDRegularFileImpl()
	: m_dwFlags( 0 )
	, m_dwMode( D_DEFAULT_FILE_MODE )
	, m_fileHANDLE( D_INVALID_HANDLE )
{
	D_OS::Memset( m_fileName, 0, sizeof(m_fileName) );
}

CDRegularFileImpl::CDRegularFileImpl( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode /*= D_DEFAULT_FILE_MODE */ )
	: m_dwFlags( dwFlags )
	, m_dwMode( dwMode )
	, m_fileHANDLE( D_INVALID_HANDLE )
{
	D_OS::Memset( m_fileName, 0, sizeof(m_fileName) );

	D_OS::Memcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		D_OS::Strlen( pFileName, MAX_FILENAMELEN ) );
}

CDRegularFileImpl::~CDRegularFileImpl()
{
	if ( D_INVALID_HANDLE != m_fileHANDLE )
	{
		Close();
	}
}

DHANDLE CDRegularFileImpl::Open()
{
	return this->Open(
		m_fileName,
		m_dwFlags,
		m_dwMode );
}

DHANDLE CDRegularFileImpl::Open( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode )
{
	if ( NULL == pFileName )
	{
		return D_INVALID_HANDLE;
	}

	D_OS::Memcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		D_OS::Strlen( pFileName, MAX_FILENAMELEN ) );

	m_fileHANDLE = D_OS::OpenFile(
		pFileName,
		dwFlags,
		dwMode );

	return m_fileHANDLE;
}

int CDRegularFileImpl::Close()
{
	if ( D_INVALID_HANDLE == m_fileHANDLE)
	{
		return D_ERROR_FAILURE;
	}

	int iRet = D_OS::CloseFile( m_fileHANDLE );

	return iRet;
}

int CDRegularFileImpl::Read( 
	char* pBuffer,
	DWORD dwReadLen,
	DWORD& dwActualRead )
{
	if ( D_INVALID_HANDLE != m_fileHANDLE )
	{
		return D_ERROR_FAILURE;
	}

	int iRet = D_OS::ReadFile(
		m_fileHANDLE,
		pBuffer,
		dwReadLen,
		&dwActualRead );

	return (0 == iRet) ? D_OK : D_ERROR_FAILURE;
}

int CDRegularFileImpl::Write( 
	const char* pBuffer,
	DWORD dwWriteLen,
	DWORD& dwActualWrite )
{
	if ( NULL == pBuffer || D_INVALID_HANDLE == m_fileHANDLE )
	{
		return D_ERROR_FAILURE;
	}

	int iRet = D_OS::WriteFile(
		m_fileHANDLE,
		(const LPVOID)pBuffer,
		dwWriteLen,
		&dwActualWrite );

	return ( 0 == iRet ) ? D_OK : D_ERROR_FAILURE;
}

int CDRegularFileImpl::Seek( 
	D_OFF_T lDistance,
	DWORD dwMoveMethod )
{
	if ( D_INVALID_HANDLE == m_fileHANDLE )
	{
		return D_ERROR_FAILURE;
	}

	int iRet = D_OS::SeekFile(
		m_fileHANDLE,
		lDistance,
		dwMoveMethod );

	return ( 0 == iRet ) ? D_OK : D_ERROR_FAILURE;
}

int CDRegularFileImpl::Flush()
{
	if ( D_INVALID_HANDLE == m_fileHANDLE )
	{
		return D_ERROR_FAILURE;
	}

	int iRet = D_OS::FlushFile( m_fileHANDLE );

	return ( 0 == iRet ) ? D_OK : D_ERROR_FAILURE;
}

DHANDLE CDRegularFileImpl::GetFileHANDLE()
{
	return m_fileHANDLE;
}

int CDRegularFileImpl::SetFileSize( LONGLONG llFileSize )
{
	if ( NULL == m_fileHANDLE ||
		0 >= llFileSize )
	{
		return D_ERROR_FAILURE;
	}

	D_OFF_T curOff = D_OS::GetFilePosition( m_fileHANDLE );
	LONGLONG llCurSize = GetFileSize();

	if ( llCurSize == llFileSize )
	{
		return D_OK;
	}

	int iRet = D_OS::TruncateFile(
		m_fileHANDLE,
		llFileSize );

	if ( 0 != iRet )
	{
		return D_ERROR_FAILURE;
	}

	if ( curOff < llFileSize )
	{
		D_OS::SeekFile( m_fileHANDLE,
			curOff,
			D_SEEK_BEGIN );
	}

	return D_OK;
}

LONGLONG CDRegularFileImpl::GetFileSize()
{
	int iRet = D_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llFileSize : -1;
}

LONGLONG CDRegularFileImpl::GetCreateTime()
{
	int iRet = D_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llCreateTime : -1;
}

LONGLONG CDRegularFileImpl::GetModifyTime()
{
	int iRet = D_OS::GetFileAddribute(
		m_fileName,
		m_fileAttribute );

	return ( 0 == iRet ) ? m_fileAttribute.llModifyTime : -1;
}

int CDRegularFileImpl::SetFileName( const char* pFileName )
{
	D_OS::Memcpy( m_fileName,
		sizeof( m_fileName),
		pFileName,
		D_OS::Strlen( pFileName, MAX_FILENAMELEN ) );

	return D_OK;
}
