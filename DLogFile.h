
#ifndef _D_LOG_FILE_H_
#define _D_LOG_FILE_H_

#include "DBase.h"

class CDFile;
class CDThreadMutex;

class CDLogFile
{
public:
	~CDLogFile();

	static CDLogFile* Instance();

	static const UINT32 D_LOG_FILE_MAX_SIZE;

public:
	bool Write( const char* pdata, UINT32 length );

private:
	CDLogFile();

	void Init();

	void UnInit();

	void WriteLogBeginPos( UINT32 offset );

	UINT32 ReadLogBeginPos();

	CDString GetLogFilePath();

	CDString GetLogFileName();

private:
	CDFile*						m_pFile;
	CDThreadMutex*				m_pThreadMutex;

	UINT32						m_offset;
};

#endif	// _D_LOG_FILE_H_
