#pragma once
#include "system/PlatformConfigure.h"
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#include <Windows.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <semaphore.h>
	#include <fcntl.h>
#endif

namespace nb{namespace System{

class Mute_Internal
{
public:
	Mute_Internal(const char *name);
	~Mute_Internal();

	//+1锁计数
	void Lock();

	//-1锁计数
	void Unlock();

private:
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	HANDLE	m_handle;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	sem_t	*m_Sem;
#endif
};

}}

