#include "system/CriticalSection.h"

using namespace nb::System;

CriticalSection::CriticalSection()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	InitializeCriticalSection(&m_Win32CriticalSection);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;//PTHREAD_MUTEX_INITIALIZER;	//Ê¹ÓÃÇ¶Ì×Ëø
#endif
}

CriticalSection::~CriticalSection()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	DeleteCriticalSection(&m_Win32CriticalSection);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_destroy(&m_mutex);
#endif
}

void CriticalSection::Lock()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	EnterCriticalSection(&m_Win32CriticalSection);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_lock(&m_mutex);
#endif
}

void CriticalSection::Unlock()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS
	LeaveCriticalSection(&m_Win32CriticalSection);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_unlock(&m_mutex);
#endif
}
