#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WINCE
#include "Thread_Win32.h"
#include "system/Thread.h"
#include "core/Exception.h"

using nb::System::Thread_Windows;
using nb::System::Thread;
using nb::Core::Exception;
DWORD WINAPI Thread_Windows::Fun(void *pV)
{
	(static_cast<Thread *>(pV))->Run();
	return 0;
}

Thread_Windows::Thread_Windows(Thread *pV)
: NativeThread(pV)
{
	m_ThreadHandle = ::CreateThread(NULL, 0, &Thread_Windows::Fun, m_pV, CREATE_SUSPENDED, NULL);
	if(m_ThreadHandle == 0)
	{
		char info[100] = {0};
		sprintf(info, "create thread fail, error code[%d]", (int)::GetLastError());
		NB_THROW_EXCEPTION(info);
	}
	SetPriority(Thread::Priority_Inherit);
}

Thread_Windows::~Thread_Windows()
{
	//	CloseHandle(m_ThreadHandle);
}

void Thread_Windows::SetPriority(nb::System::Thread::Priority priority)
{
	NativeThread::SetPriority(priority);
	int priority_windows = NORMAL_PRIORITY_CLASS;
	switch(GetPriority())
	{
	case Thread::Priority_Idle:
		priority_windows = IDLE_PRIORITY_CLASS;
		break;
	case Thread::Priority_Lowest:			//在windows下lowest和low一样
	case Thread::Priority_Low:
		priority_windows = BELOW_NORMAL_PRIORITY_CLASS;
		break;
	case Thread::Priority_OperatingSystem_Normal:
		priority_windows = NORMAL_PRIORITY_CLASS;
		break;
	case Thread::Priority_High:
		priority_windows = ABOVE_NORMAL_PRIORITY_CLASS;
		break;
	case Thread::Priority_Highest:
		priority_windows = HIGH_PRIORITY_CLASS;
		break;
	case Thread::Priority_Realtime:
		priority_windows = REALTIME_PRIORITY_CLASS;
		break;
	case Thread::Priority_Inherit:
		break;
	default:
		break;
	}
	::SetThreadPriority(m_ThreadHandle, priority_windows);
}

void Thread_Windows::Start()
{
	::ResumeThread(m_ThreadHandle);
}

void Thread_Windows::Quit()
{
	::TerminateThread(m_ThreadHandle, 0);
}

bool Thread_Windows::IsRunning() const
{
	DWORD state;
	GetExitCodeThread(m_ThreadHandle, &state);
	return state == STILL_ACTIVE;
}

bool Thread_Windows::Wait(unsigned long millisecons)
{
	return ::WaitForSingleObject(m_ThreadHandle, millisecons) == WAIT_OBJECT_0;
}


#endif
