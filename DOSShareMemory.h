
#ifndef _D_OS_SHAREMEMORY_H_
#define _D_OS_SHAREMEMORY_H_

#include "DBase.h"

namespace D_OS
{
	extern DUTILITY_API DHANDLE CreateShareMemory(
		DHANDLE hFile,
		DWORD dwSize,
		const char* szName );

	extern DUTILITY_API DHANDLE OpenShareMemory(
		const char* szName,
		const char* szRegularFileName = NULL );

	extern DUTILITY_API void* MapViewShareMemory(
		DHANDLE hShareMemory,
		DWORD dwSize );

	extern DUTILITY_API BOOL FlushShareMemory(
		void* lpDataToFlush,
		DWORD dwLength );

	/*
	* ����˵��:
	*	hShareMemory	: Ҫ�رյľ��������ShareMemoryOpen����ShareMemoryCreate
	*					  ���صģ�����ΪNULL����ʾ�����κι����ڴ���
	*	bMapToFile		: �Ƿ�ӳ�䵽�û�ָ�����ļ�(windows�º���)��hShareMemory��ΪNULL
	*					  ʱ��Ч
	*	pHeader			: Ҫ���ӳ����ڴ�ռ�ͷָ��λ�ã�����ΪNULL����ʾ����������
	*	dwLen			: Ҫ�رյĳ���(windows�º���),pHeader��ΪNULLʱ��Ч
	*/
	extern DUTILITY_API int CloseShareMemory(
		DHANDLE hShareMemory,
		bool bMapToFile,
		void* pHeader,
		DWORD dwLength );

	extern DUTILITY_API void UnLinkShareMemory( const char* szName );
}

#endif // _D_OS_SHAREMEMORY_H_