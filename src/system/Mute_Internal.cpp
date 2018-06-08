#include "Mute_Internal.h"
#include <assert.h>
#include <stdio.h>
using nb::System::Mute_Internal;

Mute_Internal::Mute_Internal(const char *name)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	m_handle = CreateMutexA(NULL, false, name);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_Sem = sem_open(name, O_RDONLY);
	if(m_Sem == SEM_FAILED)
		m_Sem = sem_open(name, O_CREAT, 0666, 1);
	assert(m_Sem != SEM_FAILED);
#endif
}

Mute_Internal::~Mute_Internal()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	CloseHandle(m_handle);	//只是关闭handle的副本，相当于引用计数-1,
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	sem_close(m_Sem);
#endif
}

void Mute_Internal::Lock()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	::WaitForSingleObject(m_handle, INFINITE);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	int x;
	sem_getvalue(m_Sem, &x);
	printf("wait before[%d]\r\n", x);
	sem_wait(m_Sem);
	sem_getvalue(m_Sem, &x);
	printf("wait after[%d]\r\n", x);
#endif
}

void Mute_Internal::Unlock()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	::ReleaseMutex(m_handle);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	int x;
	sem_getvalue(m_Sem, &x);
	printf("post before[%d]\r\n", x);
	sem_post(m_Sem);
	sem_getvalue(m_Sem, &x);
	printf("post after[%d]\r\n", x);
#endif
}
