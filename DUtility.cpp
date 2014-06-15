// DUtility.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "DUtility.h"


// 这是导出变量的一个示例
DUTILITY_API int nDUtility=0;

// 这是导出函数的一个示例。
DUTILITY_API int fnDUtility(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 DUtility.h
CDUtility::CDUtility()
{
	return;
}
