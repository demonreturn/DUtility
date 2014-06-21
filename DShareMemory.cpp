#include "DShareMemory.h"

#include "DOSMemory.h"
#include "DOSShareMemory.h"


CDShareMemory::CDShareMemory()
	: m_strName( "" )
	, m_dwSize( 0 )
	, m_pHead( NULL )
	, m_pCurrent( NULL )
	, m_hFileMap( D_INVALID_HANDLE )
{

}

CDShareMemory::~CDShareMemory()
{
	if ( D_INVALID_HANDLE != m_hFileMap )
	{
		this->Close();
	}
}

int CDShareMemory::Open(
	const char* pname,
	DWORD dwSize,
	DWORD dwOpenMode,
	const char* pFileDir /*= NULL */ )
{
	if ( NULL == pname
		|| 0 == dwSize )
	{
		return D_ERROR_INVALID_PARAM;
	}

	if ( m_hFileMap != D_INVALID_HANDLE )
	{
		return D_ERROR_ALREADY_INIT;
	}

	// ���ȳ��Դ����еĹ����ڴ����
	if ( D_BIT_DISABLED( dwOpenMode, OM_CREATE)
		&& D_BIT_ENABLED( dwOpenMode, OM_MAP_FILE)
		&& NULL != pFileDir )
	{
		// ���û��ָ��OM_CREATE�����ǳ����ļ����������Ҫ�жϳ����ļ��Ƿ����(���Linux)
		CDString strRegularFile = GenerateFileName( pname, pFileDir );

		m_hFileMap = D_OS::OpenShareMemory(
			pname, strRegularFile.c_str() );
	}
	else
	{
		m_hFileMap = D_OS::OpenShareMemory(
			pname,
			NULL );
	}

	if ( D_INVALID_HANDLE == m_hFileMap )
	{
		// ������й����ڴ���󲻴��ڣ���ô�͸���Ҫ�󴴽�һ�����߷���ʧ��
		if ( D_BIT_DISABLED( dwOpenMode, OM_CREATE))
		{
			// ����Ҫ����
			return D_ERROR_FAILURE;
		}

		HANDLE hFile = D_INVALID_HANDLE;

		if ( D_BIT_ENABLED( dwOpenMode, OM_MAP_FILE ))
		{
			// ���Ҫ��ӳ�䵽�ļ��򴴽��ļ�
			CDString strFileName = GenerateFileName( pname, pFileDir);
			if ( false == CreateMapFile( strFileName.c_str(), dwOpenMode))
			{
				return D_ERROR_FAILURE;
			}

			m_fMapping.SetFileSize( dwSize );
			hFile = m_fMapping.GetFileHANDLE();
		}

		m_hFileMap = D_OS::CreateShareMemory(
			hFile, 
			dwSize,
			pname );

		if ( D_INVALID_HANDLE == m_hFileMap )
		{
			return D_ERROR_FAILURE;
		}
	}

	m_pHead = (char*)D_OS::MapViewShareMemory(
		m_hFileMap,
		dwSize );

	if ( NULL == m_pHead )
	{
		bool bMapToFile = true;

		if ( D_INVALID_HANDLE == m_fMapping.GetFileHANDLE())
		{
			bMapToFile = false;
		}

		D_OS::CloseShareMemory( m_hFileMap, bMapToFile, NULL, 0 );

		m_hFileMap = D_INVALID_HANDLE;

		return D_ERROR_FAILURE;
	}

	m_strName = pname;
	m_dwSize = dwSize;

	m_pCurrent = m_pHead;

	return D_OK;

}

char* CDShareMemory::GetHeadPointer() const
{
	return m_pHead;
}

int CDShareMemory::Close()
{
	int iRet = D_OK;

	m_strName.clear();

	if ( NULL != m_pHead )
	{
		iRet = D_OS::CloseShareMemory(
			D_INVALID_HANDLE,
			FALSE,
			m_pHead,
			m_dwSize );

		if ( D_OK != iRet )
		{
			return D_ERROR_FAILURE;
		}

		m_pHead = NULL;
	}

	m_dwSize = 0;
	m_pCurrent = NULL;

	if ( D_INVALID_HANDLE != m_hFileMap )
	{
		bool bMapToFile = true;

		if ( D_INVALID_HANDLE != m_fMapping.GetFileHANDLE() )
		{
			bMapToFile = false;
		}

		iRet = D_OS::CloseShareMemory(
			m_hFileMap, bMapToFile, NULL, 0 );

		if ( D_OK != iRet )
		{
			return D_ERROR_FAILURE;
		}

		m_hFileMap = INVALID_HANDLE_VALUE;
	}

	if ( D_INVALID_HANDLE != m_fMapping.GetFileHANDLE() )
	{
		iRet = m_fMapping.Close();

		if ( D_OK != iRet )
		{
			return D_ERROR_FAILURE;
		}
	}

	return iRet;
}

int CDShareMemory::Read( 
	char* pBuffer,
	DWORD dwLength,
	DWORD& dwAcutualRead )
{
	if ( NULL == pBuffer )
	{
		return D_ERROR_FAILURE;
	}

	// ���㵱ǰָ����ܹ��ĳ��ȿռ�
	dwAcutualRead = m_pHead + m_dwSize - m_pCurrent;

	// ʹ��ʣ�೤�Ⱥ�ϣ����ȡ�ĳ���֮����С��
	dwAcutualRead = ( dwAcutualRead > dwLength ) ? dwLength : dwAcutualRead;

	D_OS::Memcpy( pBuffer, dwAcutualRead, m_pCurrent, dwAcutualRead );

	m_pCurrent += dwAcutualRead;

	return D_OK;
}

int CDShareMemory::Write(
	const char* pBuffer,
	DWORD dwLength )
{
	if ( NULL == pBuffer )
	{
		return D_ERROR_FAILURE;
	}

	DWORD dwRemain = m_pHead + m_dwSize - m_pCurrent;

	if ( dwRemain < dwLength )
	{
		return D_ERROR_FAILURE;
	}

	D_OS::Memcpy( m_pCurrent, dwLength, pBuffer, dwLength );

	return D_OK;
}

int CDShareMemory::Seek( long lOffset, DWORD nMoveMethod )
{
	if ( NULL == m_pHead )
	{
		return D_ERROR_FAILURE;
	}

	LONGLONG llBase = 0;

	switch ( nMoveMethod )
	{
	case D_SEEK_BEGIN:
		llBase = 0;
		break;

	case D_SEEK_CUR:
		llBase = m_pCurrent - m_pHead;
		break;

	case D_SEEK_END:
		llBase = m_dwSize;
		break;
	default:
		return D_ERROR_FAILURE;
		break;
	}

	m_pCurrent = m_pHead + llBase;

	return D_OK;
}

char* CDShareMemory::GetCurrentPointer() const
{
	return m_pCurrent;
}

void CDShareMemory::UnLink()
{
	if ( !m_strName.empty() )
	{
		D_OS::UnLinkShareMemory( m_strName.c_str() );
	}
}

bool CDShareMemory::Flush()
{
	if ( NULL == m_pHead )
	{
		return false;
	}

	return D_OS::FlushShareMemory( m_pHead, m_dwSize ) ? true : false;
}

CDString CDShareMemory::GenerateFileName(
	const char* pname,
	const char* pdirtory )
{
	CDString strFileName;

	if ( NULL != pdirtory )
	{
		strFileName = pdirtory;
	}

	DWORD dwLen = strFileName.length();

	// �Ƴ��ұߵĿո��Ŀ¼�ָ��
	while ( dwLen > 0 )
	{
		char cValue = strFileName[dwLen-1];
		if ( cValue == ' '
			|| cValue == '\\'
			|| cValue == '/' )
		{
			--dwLen;
			continue;
		}
		else
		{
			break;
		}
	}

	strFileName = strFileName.substr( 0, dwLen );

	// ����Ŀ¼�ָ�����ļ������һ��������·����
	strFileName.push_back( D_OS_SEPARATE );
	strFileName.append( pname );

	return strFileName;
}

bool CDShareMemory::CreateMapFile( 
	const char* pname,
	DWORD nMode )
{
	DWORD nFlag = O_RDWR | O_CREAT;

	if ( D_BIT_ENABLED( nMode, OM_TRUNCATE ))
	{
		nFlag |= O_TRUNC;
	}

	if ( D_INVALID_HANDLE != m_fMapping.GetFileHANDLE())
	{
		// ����Ѿ������ļ����ȹرյ�
		m_fMapping.Close();
	}

	return ( D_INVALID_HANDLE != m_fMapping.Open( pname, nFlag ) ) ? true : false;
}




