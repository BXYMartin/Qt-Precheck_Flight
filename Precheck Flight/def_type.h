/********************************************************************
	创建日期	:	
	最后修改日期:	
	作者		:	关鹏

	功能		:	基础数据类型定义
*********************************************************************/

#ifdef _WINDOWS
#	pragma once
#endif

#ifndef	_TWS_SYSTEMDEF_H
#define _TWS_SYSTEMDEF_H

#include <string>

#ifdef _WINDOWS
//#include <winsock2.h>
//#include <windows.h>

typedef long                long_t;
typedef unsigned long       ulong_t;
typedef void*				HANDLE;

#else
typedef SOCKET socket_t;

typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef int                 int32_t;
typedef unsigned int        uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
typedef float               float_t;
typedef double              double_t;
typedef long                long_t;
typedef unsigned long       ulong_t;
typedef char                char_t;
typedef unsigned char       uchar_t;
#endif

#if _UNICODE
typedef std::wstring        string_t;
#else
typedef std::string         string_t;
#endif


#define IO_HANDLE			HANDLE

#define TASKMASK_DEFAULT	0xFFFFFFFF

#define TASKLEVEL_DEFAULT	0xFFFFFFFF
#define TASKLEVEL_HIGH		THREAD_PRIORITY_HIGHEST
#define TASKLEVEL_NORM		THREAD_PRIORITY_NORMAL
#define TASKLEVEL_LOW		THREAD_PRIORITY_LOWEST

#define FLOAT_PRECISION		0.000001

#endif	//_TWS_SYSTEMDEF_H
