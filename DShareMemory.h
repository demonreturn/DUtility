
#ifndef _D_SHARE_MEMORY_H_
#define _D_SHARE_MEMORY_H_

#include "DBase.h"
#include "DFile.h"

class CDShareMemory
{
public:
	enum D_SHARE_MEMORY_OPEN_MODE
	{
		OM_TRUNCATE				= 1,		// 打开文件映射的共享内存时阶段已存在的文件
		OM_MAP_FILE				= 1 << 1,	// 将共享内存映射到文件
		OM_CREATE				= 1 << 2,	// 如果不存在则自动创建共享内存
	};

	CDShareMemory();

	~CDShareMemory();

	int Open(
		const char* pname,
		DWORD dwSize,
		DWORD dwOpenMode = 0,
		const char* pFileDir = NULL );

	char* GetHeadPointer() const;

	int Close();

	int Read(
		char* pBuffer,
		DWORD dwLength,
		DWORD& dwAcutualRead );

	int Write(
		const char* pBuffer,
		DWORD dwLength );

	int Seek(
		long lOffset,
		DWORD nMoveMethod );

	char* GetCurrentPointer() const;

	/*
	* 函数说明: 
	*	主要用于清理Linux中产生在系统目录/dev/shm/下的共享内存文件。
	* Windows平台下不执行任何操作。
	*
	*/
	void UnLink();

	bool Flush();

protected:
	CDString GenerateFileName(
		const char* pname,
		const char* pdirtory );

	bool CreateMapFile(
		const char* pname,
		DWORD nMode );

private:
	CDString					m_strName;
	DWORD						m_dwSize;
	char*						m_pHead;
	char*						m_pCurrent;
	HANDLE						m_hFileMap;
	CDFile						m_fMapping;
};

#endif // _D_SHARE_MEMORY_H_