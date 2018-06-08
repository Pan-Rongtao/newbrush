#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WINCE
#include "NativeThread.h"
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace nb{ namespace System{

class Thread;
class Thread_Windows : public NativeThread
{
public:
	Thread_Windows(Thread *pV);
	~Thread_Windows();

	virtual void SetPriority(nb::System::Thread::Priority priority);

	virtual void Start();

	virtual void Quit();

	virtual bool IsRunning() const;

	virtual bool Wait(unsigned long millisecons);

private:
	static DWORD WINAPI Fun(void *pV);
	HANDLE		m_ThreadHandle;
};

}}



#endif
