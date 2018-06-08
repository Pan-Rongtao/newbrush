#include "Sync.h"

using nb::Network::SyncSignal;
using nb::Network::Sync;

SyncSignal::SyncSignal()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	m_pEvent = CreateEvent(NULL, false, false, NULL);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	int nRet = sem_init(&m_Sem, 0, 0);				
	if(nRet == -1)
	{
		printf("[%d]sem_init error\r\n", nb::System::Platform::GetCurrentProcessId());
	}
#endif
}

SyncSignal::~SyncSignal()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	CloseHandle(m_pEvent);
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	sem_destroy(&m_Sem);
#endif
}

bool SyncSignal::Set()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	return SetEvent(m_pEvent) ? true : false;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	return sem_post(&m_Sem) == 0 ? true : false;
#endif
}

bool SyncSignal::Reset()
{
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	return ResetEvent(m_pEvent) ? true : false;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
//	none
#endif
}

//////////////
Sync::Sync()
: m_bIsWaiting(false)
{
}

Sync::~Sync()
{
}

bool Sync::IsWaiting()
{
	m_Lock.Lock();
	bool b = m_bIsWaiting;
	m_Lock.Unlock();
	return b;
}

bool Sync::Wait(unsigned long ms)
{
	bool ret = false;
#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
	m_Lock.Lock();
	HANDLE h = m_Signal.m_pEvent;
	m_bIsWaiting = true;
	m_Lock.Unlock();
	ret = WaitForSingleObject(h, ms) == WAIT_TIMEOUT;
#elif NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_X11 || NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
	if(ms == -1)
	{
		m_bIsWaiting = true;
		ret = sem_wait(&(m_Signal.m_Sem));
	}
	else
	{
		struct timespec ts;
		if(clock_gettime(CLOCK_REALTIME, &ts) < 0)
			return -1;

		ts.tv_sec += ms / 1000;

		m_bIsWaiting = true;
		int beg = nb::System::Platform::GetTickCount();
		ret = sem_timedwait(&(m_Signal.m_Sem), &ts) == -1 && errno == ETIMEDOUT;
		//以下case是由于调整了系统时间引起的，并非真正超时，如果是此情况，重新wait一次
		if(ret && nb::System::Platform::GetTickCount() - beg < ms)
			ret = sem_wait(&(m_Signal.m_Sem));

		//以下使用GetTickCount的方式自己计算超时的，会比阻塞式的超时慢一点
		/*
		m_Lock.Lock();
		int beg = nb::System::Platform::GetTickCount();
		m_bIsWaiting = true;
		m_Lock.Unlock();
		while(sem_trywait(&(m_Signal.m_Sem)) == -1 && errno == EAGAIN)
		{
			if(nb::System::Platform::GetTickCount() - beg >= ms)
			{
				ret = true;
				break;
			}
		}
		*/
	}
#endif
	m_bIsWaiting = false;
	return ret;
}

bool Sync::Release()
{
	m_Lock.Lock();
	bool b = m_Signal.Set();
	m_Lock.Unlock();
	return b;
}
