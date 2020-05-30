#pragma once
#include <stdint.h>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeindex>
#include "rttr/registration.h"
#include "rttr/registration_friend.h"

//要求c++11
//#if __cplusplus < 201103L
//	#error "c++11 supported requested."
//#endif

//平台识别,如果识别不了平台，编译器则会输出报错，并终止编译
//类UNIX下可使用g++ -dM -E - </dev/null命令查看编译器默认宏
#define NB_OS_WINDOWS_NT		0x00000001
#define NB_OS_WINDOWS_CE		0x00000002
#define NB_OS_LINUX				0x00000004
#define NB_OS_MAC_OS_X			0x00000008
#define NB_OS_IOS				0x00000010
#define NB_OS_ANDROID			0x00000020
#define NB_OS_QNX				0x00000040

#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS) || defined(_WIN32_WCE)									//windows
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
#define NB_OS NB_OS_LINUX
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
#define NB_API								__declspec(dllexport)
#else
#define NB_API
#endif

//支持构造函数为单字符串参数的exception类型（宏的方式是最优解，因为要打印__FUNCTION__，做成函数是无法输出正确的__FUNCTION__的）
#define nbThrowException(exception, argfmt, ...) \
do{\
	char buffer[512] = {0}; \
	std::string file = __FILE__;\
	size_t n = std::string::npos;\
	if (((n = file.rfind('/')) != std::string::npos) || ((n = file.rfind('\\')) != std::string::npos))\
		file = file.substr(n + 1);\
	snprintf(buffer, sizeof(buffer), "[%s, line %d, %s] throw an '%s'.\r\n\twhat: " argfmt "\r\n", file.data(), __LINE__, __FUNCTION__, typeid(exception).name(), ##__VA_ARGS__); \
	throw exception(buffer);\
}while(0)

#define _USE_MATH_DEFINES

namespace nb
{
	using var = rttr::variant;

	//获取开机以来的时钟滴答数（毫秒数）
	NB_API uint64_t getTickCount();

	//获取本进程id
	NB_API uint32_t getPid();

	//获取本线程id
	NB_API uint32_t getTid();

	//获取命名空间名
	NB_API std::string getFullName(const std::type_index &t);

	//获取命名空间
	NB_API std::string getNamespace(const std::type_index &t);

	//获取类名
	NB_API std::string getClassName(const std::type_index &t);

	//取边界内的合法值（传入的min和max会被修正），返回值可以是min, max，也可以是value本身；Bound(1, 5, 10) = 5; Bound(1, 5, 0) = 1; Bound(1, 5, 3) = 3;
	//min和max被定义为宏，需要加()，次函数与c++17中列入标准
	template<class T>
	constexpr NB_API const T &clamp(const T &lower, const T &upper, const T &value)
	{
		return (std::max)((std::min)(lower, upper), (std::min)((std::max)(lower, upper), value));
	}

	NB_API std::vector<std::string> stringSplit(const std::string &s, const std::string &sSymbol, bool bSkipEmptyString);

	template<class T1, class T2>
	NB_API std::shared_ptr<T1> as(const std::shared_ptr<T2> &other)
	{
		return std::dynamic_pointer_cast<T1, T2>(other);
	}

	template<class T1, class T2>
	NB_API T1* as(T2 other)
	{
		return dynamic_cast<T1 *>(other);
	}

	template<class T1, class T2>
	bool is(const std::shared_ptr<T2> &other)
	{
		return as<T1, T2>() != nullptr;
	}

	template<class T1, class T2>
	bool is(T2 other)
	{
		return as<T1, T2>(other) != nullptr;
	}

}