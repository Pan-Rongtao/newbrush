#pragma once
#include "system/Platform.h"
#include "system/CriticalSection.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	#define  WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	#include <semaphore.h>
	#include <time.h>
	#include <errno.h>
#endif


namespace nb{ namespace Network{

class SyncSignal
{
	friend class Sync;
public: 
	SyncSignal();
	~SyncSignal();

	bool Set();
	bool Reset();

private:
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	HANDLE	m_pEvent;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	sem_t	m_Sem;
#endif
};


class Sync
{
public:
	Sync();
	~Sync();

	bool IsWaiting();
	bool Wait(unsigned long ms = -1);
	bool Release();

private:
	bool						m_bIsWaiting;
	SyncSignal					m_Signal;
	nb::System::CriticalSection	m_Lock;
};

}}
