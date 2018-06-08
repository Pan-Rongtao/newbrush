/*******************************************************
**
**	全局模块
**	
**		提供一些基础类型重定义、全局宏等
**		
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include <typeinfo>
#include "PlatformConfigure.h"

//Boolean
typedef bool				Boolean;

//8bits(-128~127)(0~255)
typedef char				SByte;
typedef unsigned char		Byte;
typedef	char				Int8;
typedef	unsigned char		UInt8;
typedef unsigned char		uchar;

//16bits(-32768~32767)(0~65535)
typedef short				Int16;
typedef unsigned short		UInt16;
typedef unsigned short		ushort;

//32bits(-32768~32767)(0~65535)
typedef int					Int32;
typedef	unsigned int		UInt32;
typedef UInt32				uint;

//64bits(-2147483648~2147483647)(0~4294967295)
typedef long long			Int64;
typedef unsigned long long	UInt64;

//浮点数
//			符号位   指数位		尾数位	
//float		  1		   8		 23			(1.175494351e-38f（正值）~ 3.402823466e+38f)
//double	  1		   11		 52			(2.2250738585072014e-308(正值) ~ 1.7976931348623158e+308)
//long double 在Win32下是64位，在gcc下是128位
typedef float				Single;
typedef float				Real;
typedef double				Doublexx;

#define VAR_TYPE_NAME(var)	typeid(var).name()

//定义类导出符号
#if defined(NB_EXPORT)
#undef NB_EXPORT
#endif

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#define NB_EXPORT	__declspec(dllexport)
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#define NB_EXPORT
#else
	#define NB_EXPORT
#endif
