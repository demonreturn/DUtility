
#ifndef _D_FILE_FACTORY_H_
#define _D_FILE_FACTORY_H_

#include "DBase.h"

class IDFileImpl;

class CDFileImplFactory
{
public:
	int CreateFileImpl(
		DWORD dwType,
		IDFileImpl*& pFile );
};

#endif	// _D_FILE_FACTORY_H_
