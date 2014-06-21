
#ifndef _D_FILE_H_
#define _D_FILE_H_

#include "DBase.h"
#include "IDIOBase.h"
#include "IDFileImpl.h"
#include "DFileType.h"

class CDFile 
	: public IDIOBase
{
public:
	CDFile( DWORD dwType = FILE_TYPES_REGULAR_FILE );

	/*
	* pFileName	:[IN] ��Ҫ�򿪻򴴽����ļ�ȫ·������
	* nFlags	:[IN] ������д��־ O_RDONLY, O_WRONLY or O_RDWR | �򿪱�־ O_CREAT O_TRUNC   O_APPEND
	* nMode		:[IN] �ļ�����Ȩ��, Ĭ��SC_DEFAULT_FILE_MODE
	*/
	CDFile( const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode = D_DEFAULT_FILE_MODE,
		DWORD dwType = FILE_TYPES_REGULAR_FILE );

	virtual ~CDFile();

	virtual DHANDLE Open();

	virtual DHANDLE Open( 
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode = D_DEFAULT_FILE_MODE );

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

private:
	CDFile( const CDFile&);
	CDFile& operator=( const CDFile& );

	DWORD						m_fileType;
	IDFileImpl*					m_pFileImpl;
};

#endif	// _D_FILE_H_
