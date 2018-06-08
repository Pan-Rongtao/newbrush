/*******************************************************
**	PlatformConfigure.h
**
**	平台配置
**	
**	此文件会根据各个不同的平台宏定义来确定
**	NEWBRUSH_SDK_TARGET_PLATFORM，
**		可使用#if NEWBRUSH_SDK_TARGET_PLATFORM == xxx来编译平台依赖性的代码
**
**		比如在win32下会有宏WIN32；linux下有__LINUX__等
**	
**	如果识别不了平台，则会输出报错，并停止编译
**  
**	
**
**		潘荣涛
**	
********************************************************/

#pragma once

#define PLATFORM_UNKNOWN					0x00000001
#define PLATFORM_WIN32						0x00000002
#define PLATFORM_WINCE						0x00000004
#define PLATFORM_LINUX_X11					0x00000008
#define PLATFORM_LINUX_ARM					0x00000010
#define PLATFORM_MAC						0x00000020
#define PLATFORM_IOS						0x00000040
#define PLATFORM_ANDROID					0x00000080

//////目标平台类型
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_UNKNOWN


//Win32
#if defined(WIN32) || defined(_WINDOWS)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_WIN32
#endif

//WinCE
#if defined(WINCE)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_WINCE
#endif


//Linux_Arm（大多数arm编译器有__ARMEL__，如无，需自行定义LINUX_ARM宏）
#if defined(__ARMEL__) || defined(LINUX_ARM) || defined(__aarch64__)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_LINUX_ARM

//Linux_X11
#elif defined(linux) || defined(__linux__) || defined(__LINUX__)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_LINUX_X11

//Android（Android平台未调查有哪些宏）
#elif defined(__ANDROID__) || (__Android__)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_ANDROID

//Ios（ios只能主动设置）
#elif defined(__IOS__) || defined(__Ios__) || defined(ios)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_IOS

//Mac
#elif defined(__APPLE__) || defined(Mac) || defined(Apple)
#undef	NEWBRUSH_SDK_TARGET_PLATFORM
#define NEWBRUSH_SDK_TARGET_PLATFORM		PLATFORM_MAC


#endif

//无法识别目标平台类型将终止编译
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_UNKNOWN
#error "!!!!!!!!!!!!!!!!!!!!!!!!!!!!Can not recognize the target platform type: have you configured an sopported platform ? check file 'System/PlatformConfigure.h' . to confirm the Macro 'NEWBRUSH_SDK_TARGET_PLATFORM'.!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
#else

#endif
