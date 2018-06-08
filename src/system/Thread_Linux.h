#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include "NativeThread.h"
#include <unistd.h>

namespace nb{ namespace System{

class Thread_Linux : public NativeThread
{
public:
	Thread_Linux(Thread *pV);
	~Thread_Linux();

	virtual void Start();

	virtual void Quit();

	virtual bool IsRunning() const;

	virtual bool Wait(unsigned long millisecons);

private:
	static void *Fun(void *pV);
	pthread_t	m_ThreadHandle;
};

}}

#endif
