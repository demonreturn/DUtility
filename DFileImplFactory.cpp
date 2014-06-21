#include "DFileImplFactory.h"

#include "DFileType.h"
#include "DRegularFileImpl.h"

// 目前此处只实现普通文件
int CDFileImplFactory::CreateFileImpl( DWORD dwType, IDFileImpl*& pFile )
{
	if ( FILE_TYPES_REGULAR_FILE == dwType )
	{
		pFile = new CDRegularFileImpl();

		if ( NULL == pFile )
		{
			return D_ERROR_FAILURE;
		}

		return D_OK;
	}

	return D_ERROR_NOT_FOUND;
}
