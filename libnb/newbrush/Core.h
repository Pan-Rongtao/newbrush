#pragma once
#include <stdint.h>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <typeindex>
#include <thread>
#include <sstream>
#include <cmath>

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
#if _MSC_VER < 1900
#error "vs2015 or later version needed."
#endif
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)				//linux
#define NB_OS_FAMILY_UNIX 1
#if defined(__ANDROID__)
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
#error "can't recognize NB_OS, check [Core.h]"
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
#define NB_API __declspec(dllexport)
#else
#define NB_API
#endif

//支持构造函数为单字符串参数的exception类型（宏的方式是最优解，因为要打印__FUNCTION__，做成函数是无法输出正确的__FUNCTION__的）


#define nbThrowExceptionIf(condition, exception, argfmt, ...) \
if(condition)\
{\
do{\
	char buffer[512] = {0}; \
	std::string file = __FILE__;\
	size_t n = std::string::npos;\
	if (((n = file.rfind('/')) != std::string::npos) || ((n = file.rfind('\\')) != std::string::npos))\
		file = file.substr(n + 1);\
	snprintf(buffer, sizeof(buffer), "[%s, line %d, %s] throw an '%s'.\n\twhat: " argfmt "\n", file.data(), __LINE__, __FUNCTION__, typeid(exception).name(), ##__VA_ARGS__); \
	throw exception(buffer);\
}while(0);\
}
#define nbThrowException(exception, argfmt, ...) nbThrowExceptionIf(true, exception, argfmt, ##__VA_ARGS__)
//#define nbBindEventFunction(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } //need c++14 support
#define nbBindEventFunction(fn) std::bind(&fn, this, std::placeholders::_1)

#define nbArraySize(arr) sizeof(arr) / sizeof(arr[0])

#if NB_OS == NB_OS_ANDROID
#define RES_DIR "/storage/emulated/0/resource/"
#else
#define RES_DIR "../resource/"
#endif

namespace nb
{
	//获取距1970.1.1的 纳秒/微秒/毫秒/秒数
	NB_API inline uint64_t getNanoseconds()		{ return std::chrono::steady_clock::now().time_since_epoch().count(); }
	NB_API inline uint64_t getMicroseconds()	{ return getNanoseconds() / 1000; }
	NB_API inline uint64_t getMilliseconds()	{ return getNanoseconds() / 1000000; }
	NB_API inline uint64_t getSeconds()			{ return getNanoseconds() / 1000000000; }

	//获取模块启动时间
	NB_API uint64_t getStarupMilliseconds();

	//获取本进程id
	NB_API uint64_t getPid();

	//获取本线程id
	NB_API uint64_t getTid();

	//约等于
	NB_API inline bool epsilonEqual(float a, float b, float epsilon = 1e-6)		{ return fabs(a - b) <= epsilon; }
	NB_API inline bool epsilonEqual(double a, double b, double epsilon = 1e-6)	{ return fabs(a - b) <= epsilon; }

	NB_API void stringTrim(std::string& token);
	NB_API std::vector<std::string> stringSplit(const std::string & str, const std::string & separators, bool ignoreEmpty, bool doTrim = false);

	//取边界内的合法值clamp(1, 5, 10) = 5; clamp(1, 5, 0) = 1; clamp(1, 5, 3) = 3;
	//此函数与c++17中列入标准
	template<class T>
	constexpr const T &clamp(const T &v, const T &lower, const T &upper)
	{
		return std::min(std::max(v, lower), upper);
	}
	
	template<typename T>
	using scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr scope<T> createScope(Args&& ... args)
	{
	//	return std::make_unique<T>(std::forward<Args>(args)...);	//need c++14 support
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr ref<T> createRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<class T1, class T2>
	ref<T1> as(const ref<T2> &other)
	{
		return std::dynamic_pointer_cast<T1, T2>(other);
	}

	template<class T1, class T2>
	T1* as(T2 other)
	{
		return dynamic_cast<T1 *>(other);
	}

	template<class T1, class T2>
	bool is(const ref<T2> &other)
	{
		return as<T1, T2>(other) != nullptr;
	}

	template<class T1, class T2>
	bool is(T2 other)
	{
		return as<T1, T2>(other) != nullptr;
	}

}
