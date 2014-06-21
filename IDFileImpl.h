

#ifndef _D_FILEIMPL_H_
#define _D_FILEIMPL_H_

#include "DBase.h"

class IDFileImpl
{
public: 
	virtual ~IDFileImpl(){}

	virtual DHANDLE Open() = 0;

	virtual DHANDLE Open( 
		const char* pFileName,
		DWORD dwFlags,
		DWORD dwMode ) = 0;

	virtual int Close() = 0;

	virtual int Read(
		char* pBuffer,
		DWORD dwReadLen,
		DWORD& dwActualRead ) = 0;

	virtual int Write(
		const char* pBuffer,
		DWORD dwWriteLen,
		DWORD& dwActualWrite ) = 0;

	virtual int Seek(
		D_OFF_T lDistance,
		DWORD dwMoveMethod ) = 0;

	virtual int Flush() = 0;

	virtual DHANDLE GetFileHANDLE() = 0;

	virtual int SetFileSize( LONGLONG llFileSize ) = 0;

	virtual LONGLONG GetFileSize() = 0;

	virtual LONGLONG GetCreateTime() = 0;

	virtual LONGLONG GetModifyTime() = 0;

	virtual int SetFileName( const char* pFileName )
	{
		return D_OK;
	}

	virtual void SetFlags( DWORD dwFlags ){}

	virtual void SetAccessMode( DWORD dwMode ){}
};

#endif	//_D_FILEIMPL_H_