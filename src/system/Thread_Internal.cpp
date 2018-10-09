#include "Thread_Internal.h"
#include "core/Exception.h"

using namespace nb::System;

Thread_Internal::Thread_Internal(Thread * pV)
	: m_pV(pV)
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	m_ThreadHandle = ::CreateThread(NULL, 0, &Thread_Internal::fun, m_pV, CREATE_SUSPENDED, NULL);
	if (m_ThreadHandle == 0)
		throw nb::core::SystemException(__FILE__, __LINE__);
	setPriority(Thread::Priority_Inherit);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM

#endif
}

Thread_Internal::~Thread_Internal()
{
}

void Thread_Internal::setPriority(Thread::Priority priority)
{
	m_Priority = priority;
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	int priority_windows = NORMAL_PRIORITY_CLASS;
	switch (priority)
	{
	case Thread::Priority_Idle:								priority_windows = IDLE_PRIORITY_CLASS;				break;
	case Thread::Priority_Lowest:							//在windows下lowest和low一样
	case Thread::Priority_Low:								priority_windows = BELOW_NORMAL_PRIORITY_CLASS;		break;
	case Thread::Priority_OperatingSystem_Normal:			priority_windows = NORMAL_PRIORITY_CLASS;			break;
	case Thread::Priority_High:								priority_windows = ABOVE_NORMAL_PRIORITY_CLASS;		break;
	case Thread::Priority_Highest:							priority_windows = HIGH_PRIORITY_CLASS;				break;
	case Thread::Priority_Realtime:							priority_windows = REALTIME_PRIORITY_CLASS;			break;
	case Thread::Priority_Inherit:																				break;
	default:																									break;
	}
	::SetThreadPriority(m_ThreadHandle, priority_windows);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	printf("not realy complete fun [setPriority] on platform x11 or arm.\r\n");
#endif
}

Thread::Priority Thread_Internal::priority() const
{
	return m_Priority;
}

void Thread_Internal::start()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	::ResumeThread(m_ThreadHandle);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	int ret = pthread_create(&m_ThreadHandle, NULL, &Thread_Linux::fun, m_pV);
#endif
}

void Thread_Internal::quit()
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	::TerminateThread(m_ThreadHandle, 0);
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	pthread_exit(0);
#endif
}

bool Thread_Internal::isRunning() const
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	DWORD state;
	GetExitCodeThread(m_ThreadHandle, &state);
	return state == STILL_ACTIVE;
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	printf("not realy complete fun [isRunning] on platform x11 or arm.\r\n");
	return true;
#endif
}

bool Thread_Internal::wait(unsigned long millisecons)
{
#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	return ::WaitForSingleObject(m_ThreadHandle, millisecons) == WAIT_OBJECT_0;
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	printf("not realy complete fun [wait] on platform x11 or arm.\r\n");
	return true;
#endif
}

#if NB_SDK_TARGET_PLATFORM == PLATFORM_WINDOWS || NB_SDK_TARGET_PLATFORM == PLATFORM_WINCE
DWORD WINAPI Thread_Internal::fun(void *pV)
{
	(static_cast<Thread *>(pV))->run();
	return 0;
}
#elif NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NB_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
void *Thread_Internal::fun(void *pV)
{
	(static_cast<Thread *>(pV))->run();
	return nullptr;
}
#endif