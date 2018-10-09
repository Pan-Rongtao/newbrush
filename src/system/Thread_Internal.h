#pragma once
#include "core/Def.h"
#include "system/Thread.h"

#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	#define  WIN32_LEAN_AND_MEAN
	#include <windows.h>
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <unistd.h>
#endif

namespace nb { namespace System {

class Thread;
class Thread_Internal
{
public:
	Thread_Internal(Thread *pV);
	~Thread_Internal();

	void setPriority(Thread::Priority priority);

	Thread::Priority priority() const;

	void start();

	void quit();

	bool isRunning() const;

	bool wait(unsigned long millisecons);

private:
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	static DWORD WINAPI fun(void *pV);
	HANDLE		m_ThreadHandle;
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	static void *fun(void *pV);
	pthread_t	m_ThreadHandle;
#endif
	nb::System::Thread::Priority	m_Priority;
	Thread							*m_pV;
};

}}
