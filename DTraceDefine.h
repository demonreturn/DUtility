#ifndef _D_TRACE_DEFINE_H_
#define _D_TRACE_DEFINE_H_

#include "DBase.h"

/* trace���ݵ���󳤶� */
const DWORD D_TRACE_MAX_TRACE_LEN				= 1024;

/* trace��ʽ�����ֱ������� */
const DWORD D_TRACE_RESERVE_DATA_LEN			= 64;

/* ʵ������trace����󳤶� */
const DWORD D_TRACE_AVAILABLE_DATA_LEN		= D_TRACE_MAX_TRACE_LEN - D_TRACE_RESERVE_DATA_LEN;

#endif	// _D_TRACE_DEFINE_H_