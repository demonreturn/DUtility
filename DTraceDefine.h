#ifndef _D_TRACE_DEFINE_H_
#define _D_TRACE_DEFINE_H_

#include "DBase.h"

/* trace内容的最大长度 */
const DWORD D_TRACE_MAX_TRACE_LEN				= 1024;

/* trace格式化部分保留长度 */
const DWORD D_TRACE_RESERVE_DATA_LEN			= 64;

/* 实际允许trace的最大长度 */
const DWORD D_TRACE_AVAILABLE_DATA_LEN		= D_TRACE_MAX_TRACE_LEN - D_TRACE_RESERVE_DATA_LEN;

#endif	// _D_TRACE_DEFINE_H_