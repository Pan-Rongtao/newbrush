#pragma once
#include <string>
#include <stdint.h>
#include <memory>
#include <algorithm>

//要求c++11
//#if __cplusplus < 201103L
//	#error "c++11 supported requested."
//#endif

//平台识别,如果识别不了平台，编译器则会输出报错，并终止编译
//类UNIX下可使用g++ -dM -E - </dev/null命令查看编译器默认宏
#define NB_OS_UNKNOWN		0x00000001
#define NB_OS_WINDOWS_NT	0x00000002
#define NB_OS_WINDOWS_CE	0x00000004
#define NB_OS_LINUX			0x00000008
#define NB_OS_MAC_OS_X		0x00000010
#define NB_OS_IOS			0x00000020
#define NB_OS_ANDROID		0x00000040
#define NB_OS_QNX			0x00000080

#if defined(_WINDOWS) || defined(_WIN32_WCE)									//windows
	#define NB_OS_FAMILY_WINDOWS 1
	#if defined(_WIN32_WCE)
		#define NB_OS NB_OS_WINDOWS_CE
	#else
		#define NB_OS NB_OS_WINDOWS_NT
	#endif
	#pragma warning(disable: 4251)
	#if _MSC_VER < 1900
		#error "vs2015 or later version needed."
	#endif
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)				//linux
	#define NB_OS_FAMILY_UNIX 1
	#ifdef (__ANDROID__)
		#define NB_OS NB_OS_ANDROID
	#else
		#define NB_OS_LINUX_X11
	#endif
#elif defined(__QNX__) || defined(__QNXNTO)										//qnx(gcc 5.4)
	#define NB_OS_FAMILY_UNIX 1
	#define NB_OS NB_OS_QNX
#elif defined(__IOS__) || defined(__Ios__) || defined(ios)						//ios（ios只能主动设置？）
	#define NB_OS_FAMILY_UNIX 1
	#define NB_OS		NB_OS_IOS
#elif defined(__APPLE__) || defined(Mac) || defined(Apple)						//mac
	#define NB_OS_FAMILY_UNIX 1
	#define NB_OS		NB_OS_MAC_OS_X
#endif

#ifndef NB_OS
#error "can't recognize NB_OS, check [core/Def.h]"
#endif

#define NB_ARCH_AMD		0x00000001
#define NB_ARCH_ARM		0x00000002

#if defined(__arm__) || defined(__ARM__)
	#define NB_ARCH NB_ARCH_ARM
#else
	#define NB_ARCH NB_ARCH_AMD
#endif


//定义API导出宏
#if NB_OS_FAMILY_WINDOWS
	#define NB_API					__declspec(dllexport)
#else
	#define NB_API
#endif

#define NB_THROW_EXCEPTION(content) throw nb::core::Exception(content, __FILE__, __LINE__);
#define NB_PI						3.14159265358979323
#define NB_2PI						6.28318530717958647
#define NB_HALF_PI					1.57079632679489661
#define NB_ANG2RAD(angle)			(0.01745329251994329 * angle)
#define NB_RAD2ANG(radian)			(57.2957795130823208 * radian)
#define NB_PID						nb::getPid()
#define NB_GET_TICK_COUT			nb::getTickCount()

namespace nb 
{
	//获取开机以来的时钟滴答数（毫秒数）
	NB_API uint64_t getTickCount();

}