
#include "DFile.h"


#include "DFileImplFactory.h"
#include "DRegularFileImpl.h"
#include <assert.h>

CDFile::CDFile( DWORD dwType /*= FILE_TYPES_REGULAR_FILE */ )
	: m_fileType( dwType )
	, m_pFileImpl( NULL )
{
	CDFileImplFactory fileFactory;

	int iRet = fileFactory.CreateFileImpl( m_fileType, m_pFileImpl );

	assert( iRet == D_OK );
}

CDFile::CDFile( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode /*= D_DEFAULT_FILE_MODE*/,
	DWORD dwType /*= FILE_TYPES_REGULAR_FILE */ )
	: m_fileType( dwType )
	, m_pFileImpl( NULL )
{
	CDFileImplFactory fileFactory;

	int iRet = fileFactory.CreateFileImpl( m_fileType, m_pFileImpl );
	assert( iRet == D_OK );

	if ( D_OK == iRet )
	{
		iRet = m_pFileImpl->SetFileName( pFileName );
		assert( iRet == D_OK );

		m_pFileImpl->SetFlags( dwFlags );
		m_pFileImpl->SetAccessMode( dwMode );
	}
}

CDFile::~CDFile()
{
	D_DELETE( m_pFileImpl );
}

DHANDLE CDFile::Open()
{
	if ( NULL == m_pFileImpl )
	{
		return D_INVALID_HANDLE;
	}

	return m_pFileImpl->Open();
}

DHANDLE CDFile::Open( 
	const char* pFileName,
	DWORD dwFlags,
	DWORD dwMode )
{
	if ( NULL == m_pFileImpl ||
		NULL == pFileName )
	{
		return D_INVALID_HANDLE;
	}

	return m_pFileImpl->Open(pFileName,
		dwFlags,
		dwMode );
}

int CDFile::Close()
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->Close();
}

int CDFile::Read( 
	char* pBuffer,
	DWORD dwReadLen,
	DWORD& dwActualRead )
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->Read( pBuffer, dwReadLen, dwActualRead );
}

int CDFile::Write( 
	const char* pBuffer,
	DWORD dwWriteLen,
	DWORD& dwActualWrite )
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->Write(pBuffer, dwWriteLen, dwActualWrite );
}

int CDFile::Seek( D_OFF_T lDistance, DWORD dwMoveMethod )
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->Seek( lDistance, dwMoveMethod );
}

int CDFile::Flush()
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->Flush();
}

DHANDLE CDFile::GetFileHANDLE()
{
	if ( NULL == m_pFileImpl )
	{
		return D_INVALID_HANDLE;
	}

	return m_pFileImpl->GetFileHANDLE();
}

int CDFile::SetFileSize( LONGLONG llFileSize )
{
	if ( NULL == m_pFileImpl )
	{
		return D_ERROR_FAILURE;
	}

	return m_pFileImpl->SetFileSize( llFileSize );
}

LONGLONG CDFile::GetFileSize()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetFileSize();
}

LONGLONG CDFile::GetCreateTime()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetCreateTime();
}

LONGLONG CDFile::GetModifyTime()
{
	if ( NULL == m_pFileImpl )
	{
		return -1;
	}

	return m_pFileImpl->GetModifyTime();
}
