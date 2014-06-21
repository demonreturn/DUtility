
#ifndef _D_REGULAR_FILEIMPL_H_
#define _D_REGULAR_FILEIMPL_H_

#include "DBase.h"
#include "IDFileImpl.h"

class CDRegularFileImpl
	: public IDFileImpl
{
public:
	CDRegularFileImpl();

	CDRegularFileImpl(
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode = D_DEFAULT_FILE_MODE );

	virtual ~CDRegularFileImpl();

	virtual DHANDLE Open();

	virtual DHANDLE Open( 
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode );

	virtual int Close();

	virtual int Read(
		char* pBuffer,
		DWORD dwReadLen,
		DWORD& dwActualRead );

	virtual int Write(
		const char* pBuffer,
		DWORD dwWriteLen,
		DWORD& dwActualWrite );

	virtual int Seek(
		D_OFF_T lDistance,
		DWORD dwMoveMethod );

	virtual int Flush();

	virtual DHANDLE GetFileHANDLE();

	virtual int SetFileSize( LONGLONG llFileSize );

	virtual LONGLONG GetFileSize();

	virtual LONGLONG GetCreateTime();

	virtual LONGLONG GetModifyTime();

	virtual int SetFileName( const char* pFileName );

	virtual void SetFlags( DWORD dwFlags )
	{
		m_dwFlags = dwFlags;
	}

	virtual void SetAccessMode( DWORD dwMode )
	{
		m_dwMode = dwMode;
	}

private:
	CDRegularFileImpl( const CDRegularFileImpl& );

	CDRegularFileImpl& operator = ( const CDRegularFileImpl& );

	char						m_fileName[MAX_FILENAMELEN];	/*ÎÄ¼þÃû*/
	DHANDLE						m_fileHANDLE;
	DWORD						m_dwFlags;
	DWORD						m_dwMode;
	File_Attributes				m_fileAttribute;
};

#endif	// _D_REGULAR_FILEIMPL_H_
