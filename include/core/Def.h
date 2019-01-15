#pragma once
#include <typeinfo>
#include <string>
#include <stdint.h>
#include <memory>
#include <algorithm>

//要求c++11
//#if __cplusplus < 201103L
//	#error "c++11 supported requested."
//#endif

//平台识别,如果识别不了平台，编译器则会输出报错，并终止编译
#define PLATFORM_UNKNOWN					0x00000001
#define PLATFORM_WINDOWS					0x00000002
#define PLATFORM_WINCE						0x00000004
#define PLATFORM_LINUX_X11					0x00000008
#define PLATFORM_LINUX_ARM					0x00000010
#define PLATFORM_MAC						0x00000020
#define PLATFORM_IOS						0x00000040
#define PLATFORM_ANDROID					0x00000080
#define NB_SDK_TARGET_PLATFORM				PLATFORM_UNKNOWN

//类UNIX下可使用g++ -dM -E - </dev/null命令查看编译器默认宏
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)	//windows
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_WINDOWS
	#pragma warning(disable: 4251)
#elif defined(WINCE)															//wince
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_WINCE
#elif defined(__ARMEL__) || defined(LINUX_ARM) || defined(__aarch64__)			//linux-arm
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_LINUX_ARM
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)				//linux-x11
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_LINUX_X11
#elif defined(__ANDROID__) || (__Android__)										//android
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_ANDROID
#elif defined(__IOS__) || defined(__Ios__) || defined(ios)						//ios（ios只能主动设置？）
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_IOS
#elif defined(__APPLE__) || defined(Mac) || defined(Apple)						//mac
	#undef	NB_SDK_TARGET_PLATFORM
	#define NB_SDK_TARGET_PLATFORM		PLATFORM_MAC
#else
	#error "!!!!!!!!!!Can not recognize the target platform type: have you configured an sopported platform ? check file 'core/Def.h' to confirm the Macro 'NB_SDK_TARGET_PLATFORM'.!!!!!!!!!!"
#endif

#define NB_NAMESPACE_CORE_BEGIN		namespace nb{ namespace core{
#define NB_NAMESPACE_MEDIA_BEGIN	namespace nb{ namespace media{
#define NB_NAMESPACE_GLES_BEGIN		namespace nb{ namespace gl{
#define NB_NAMESPACE_GUI_BEGIN		namespace nb{ namespace gui{
#define NB_NAMESPACE_END			}}
#define NB_USING_NAMESPACE_CORE		using namespace nb::core;
#define NB_USING_NAMESPACE_MEDIA	using namespace nb::media;
#define NB_USING_NAMESPACE_GLES		using namespace nb::gl;
#define NB_USING_NAMESPACE_GUI		using namespace nb::gui;

//定义API导出宏
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	#define NB_API					__declspec(dllexport)
	#define NB_SPRINTF				_snprintf_s
#else
	#define NB_API
	#define NB_SPRINTF				snprintf
#endif

#define NB_TYPE_NAME(type)			typeid(type).name()
#define NB_THROW_EXCEPTION(content) throw nb::core::Exception(content, __FILE__, __LINE__); 

namespace nb {

	//成员变量在vc中无法导出，Linux下无此问题。目前没有好办法解决，只能做成函数的方式
	//表示PI=3.1415926
	NB_API double pi();

	//表示e=2.7182818
	NB_API double e();

	//角度转弧度
	NB_API double angleToRadian(double angle);

	//弧度转角度
	NB_API double radioToAngle(double radian);

	//约等于，差值在0.00001内表示float相等
	NB_API bool approximatelyEqual(float f1, float f2);

	//约等于，差值在0.000000000001内表示double相等
	NB_API bool approximatelyEqual(double d1, double d2);

	//量级约等于，表示差值在f1和f2所处量级的值几乎可以忽略不计。比如f1和f2都为亿级的数，他们的差值为10，则它们为量级上的约等于
	NB_API bool magnitudeEqual(float f1, float f2);

	//量级约等于
	NB_API bool magnitudeEqual(double d1, double d2);

	//取边界内的合法值（传入的min和max会被修正），返回值可以是min, max，也可以是value本身；Bound(1, 5, 10) = 5; Bound(1, 5, 0) = 1; Bound(1, 5, 3) = 3;
	//min和max被定义为宏，需要加()
	template<class T>
	NB_API const T &bound(const T &lower, const T &upper, const T &value)
	{
		return (std::max)((std::min)(lower, upper), (std::min)((std::max)(lower, upper), value));
	}

	//取近值，表示value与v1，v2最紧挨的值，返回值一定是v1或者v2；
	template<class T>
	NB_API const T &nearBy(const T &v1, const T &v2, const T &value)
	{
		return std::abs(v1 - value) > std::abs(v2 - value) ? v2 : v1;
	}

	//离一个区域的范围，比如 DistanceFromArea(1, 5, -1)返回2；DistanceFromArea(1, 5, 3)返回0；DistanceFromArea(1, 5, 9)返回4
	template<class T>
	NB_API const T distanceFromArea(const T &xBound, const T &yBound, const T &val)
	{
		return (val < xBound) ? xBound - val : (val > yBound ? val - yBound : int(0));
	}

	//获取目标平台类型
	NB_API int getTargetPlatformType();
	NB_API std::string getTargetPlatformName();

	//获取开机以来的时钟滴答数（毫秒数）
	NB_API uint64_t getTickCount();

	//获取当前进程id
	NB_API int getCurrentProcessId();

	//获取当前线程id
	NB_API int getCurrentThreadId();

	//根据pid获取进程名
	NB_API std::string getProcessName(int pid);

	//休眠秒/毫秒/微秒
	NB_API void sleep(int seconds);
	NB_API void msleep(int milliseconds);
	NB_API void usleep(int useconds);
}