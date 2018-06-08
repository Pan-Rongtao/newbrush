#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <Windows.h>
	#define  WIN32_LEAN_AND_MEAN
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <pthread.h>
#endif

namespace nb{ namespace System{

class CriticalSection_Internal
{
public:
	CriticalSection_Internal();
	~CriticalSection_Internal();

	void Lock();
	void Unlock();

private:
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	CRITICAL_SECTION	m_Win32CriticalSection;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_t		m_mutex;
#endif
};

}}
