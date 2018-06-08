#include "system/Thread.h"
#include "system/Platform.h"
#include "Thread_Win32.h"
#include "Thread_Linux.h"

using nb::System::Thread;
Thread::Thread() 
: m_pNative(NULL)
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WINCE
	m_pNative = new Thread_Windows(this);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	m_pNative = new Thread_Linux(this);
#else
	#error "unrealized Thread::Thread on this platform"
#endif
}

Thread::~Thread()
{
}

void Thread::SetPriority(Priority priority)
{
	m_pNative->SetPriority(priority);
}

Thread::Priority Thread::GetPriority() const
{
	return m_pNative->GetPriority();
}

void Thread::Start()
{
	m_pNative->Start();
}

void Thread::Quit()
{
	m_pNative->Quit();
}

bool Thread::IsRunning()
{
	return m_pNative->IsRunning();
}

bool Thread::Wait(unsigned long nMs)
{
	return m_pNative->Wait(nMs);
}

void Thread::Run()
{
}

void Thread::Sleep(unsigned long seconds)
{
	nb::System::Platform::Sleep(seconds);
}

void Thread::MSleep(unsigned long milliSeconds)
{
	nb::System::Platform::MSleep(milliSeconds);
}

void Thread::USleep(unsigned long uSeconds)
{
	nb::System::Platform::USleep(uSeconds);
}
