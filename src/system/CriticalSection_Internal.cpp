#include "CriticalSection_Internal.h"

using namespace nb::System;

CriticalSection_Internal::CriticalSection_Internal()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	InitializeCriticalSection(&m_Win32CriticalSection);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;//PTHREAD_MUTEX_INITIALIZER;	//Ê¹ÓÃÇ¶Ì×Ëø
#endif
}

CriticalSection_Internal::~CriticalSection_Internal()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	DeleteCriticalSection(&m_Win32CriticalSection);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_destroy(&m_mutex);
#endif
}

void CriticalSection_Internal::Lock()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	EnterCriticalSection(&m_Win32CriticalSection);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_lock(&m_mutex);
#endif
}

void CriticalSection_Internal::Unlock()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	LeaveCriticalSection(&m_Win32CriticalSection);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_mutex_unlock(&m_mutex);
#endif
}