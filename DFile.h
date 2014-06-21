
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
	* pFileName	:[IN] 需要打开或创建的文件全路径名称
	* nFlags	:[IN] 三个读写标志 O_RDONLY, O_WRONLY or O_RDWR | 打开标志 O_CREAT O_TRUNC   O_APPEND
	* nMode		:[IN] 文件操作权限, 默认SC_DEFAULT_FILE_MODE
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
