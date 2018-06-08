#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include "Thread_Linux.h"
#include "system/Thread.h"

using nb::System::Thread_Linux;
using nb::System::Thread;
void *Thread_Linux::Fun(void *pV)
{
	(static_cast<Thread *>(pV))->Run();
}

Thread_Linux::Thread_Linux(Thread *pV)
: NativeThread(pV)
{

}

Thread_Linux::~Thread_Linux()
{
}

void Thread_Linux::Start()
{
	int ret = pthread_create(&m_ThreadHandle, NULL, &Thread_Linux::Fun, m_pV);
}

void Thread_Linux::Quit()
{
	pthread_exit(0);
}

bool Thread_Linux::IsRunning() const
{
	printf("not realy complete fun [IsRunning] in platform x11 or arm.\r\n");
	return true;
}

bool Thread_Linux::Wait(unsigned long nMs)
{
	printf("not realy complete fun [Wait] in platform x11 or arm.\r\n");
}


#endif
