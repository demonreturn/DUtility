#include "DLogFile.h"

#include "DFile.h"
#include "DMutexGuardT.h"
#include "DThreadMutex.h"

#include <sstream>
#include <assert.h>

const UINT32 CDLogFile::D_LOG_FILE_MAX_SIZE = 10 * 1024 * 1024;
static const CDString D_LOG_PATH = "log";
static const CDString D_LOG_EXT = ".log";
static const UINT32 D_LOG_BEGIN_POS_LENGTH = 16;
static const CDString D_LOG_BEGIN_TAG = "\r\n\r\n************************* Begin trace line ***********************\r\n\r\n";
static const UINT32 D_LOG_BEGIN_TAG_LENGTH = D_LOG_BEGIN_TAG.length();
static const CDString D_LOG_END_TAG = "\r\n\r\n************************* End trace line *************************\r\n\r\n";
static const UINT32 D_LOG_END_TAG_LENGTH = D_LOG_END_TAG.length();

static const UINT32 D_LOG_BLOCK_SIZE = 1024;

inline UINT32 GetInitBeginPos()
{
#ifdef D_LOG_NEED_REPEAT
	return D_LOG_BEGIN_TAG_LENGTH;
#else
	return D_LOG_BEGIN_TAG_LENGTH;
#endif
}

inline bool ReadFile( CDFile* pfile, char* pdata, DWORD length )
{
	DWORD actualRead = 0;
	pfile->Read( pdata, length, actualRead );

	return (actualRead == length) ? true : false;
}

inline bool WriteFile( CDFile* pfile, const char* pdata, DWORD length )
{
	DWORD acutalWrite = 0;
	pfile->Write( pdata, length, acutalWrite );

	return (acutalWrite == length ) ? true : false;
}

CDLogFile::CDLogFile()
	: m_pFile( new CDFile() )
	, m_pThreadMutex( new CDThreadMutex() )
	, m_offset( 0 )
{
	Init();
}

CDLogFile::~CDLogFile()
{
	UnInit();

	D_DELETE( m_pFile );
	D_DELETE( m_pThreadMutex );
}

CDLogFile* CDLogFile::Instance()
{
	static CDLogFile s_instance;

	return &s_instance;
}

void CDLogFile::Init()
{
	CDMutexGuardT<CDThreadMutex> lockguard( m_pThreadMutex );

	//CDString logPath = GetLogFilePath();

	// TODO:: createdir;

	//CDString logFile = 
}

void CDLogFile::UnInit()
{

}
