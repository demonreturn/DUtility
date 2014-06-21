
#ifndef _D_IOBASE_H_
#define _D_IOBASE_H_

#include "DBase.h"

class IDIOBase
{
public:
	virtual ~IDIOBase(){}

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
};

#endif	// _D_IOBASE_H_

