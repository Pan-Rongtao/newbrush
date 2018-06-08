#include "TimersDriver.h"
#include "system/Timer.h"
#include "system/Platform.h"
#include "TimerPrivate.h"

using namespace nb::System;

TimersDriver TimersDriver::s_instance;

TimersDriver::TimersDriver(void)
	: m_bUseNextTimerItor(false)
{
}

TimersDriver::~TimersDriver(void)
{
}

void TimersDriver::Add(Timer *timer)
{
	Remove(timer);

	UInt64 k = Platform::GetTickCount() + timer->GetInterval();

	TimerPrivate *timerPrivate = timer->GetPrivate();

	std::multimap<unsigned long long, Timer *>::iterator itor = m_activeTimers.insert(std::pair<unsigned long long, Timer *>(k, timer));
	timerPrivate->SetDriverItor(&itor);
	timerPrivate->SetActive(true);
}

void TimersDriver::Remove(Timer *timer)
{
	TimerPrivate *timerPrivate = timer->GetPrivate();

	if(timerPrivate->IsUseDriverItor())
	{
		if(!m_itorNextTimer.IsNull() && m_itorNextTimer.GetIterator() == timerPrivate->GetDriverItor())
		{
			m_itorNextTimer++;
		}

		m_activeTimers.erase(timerPrivate->GetDriverItor());
		timerPrivate->SetDriverItor(NULL);
		timerPrivate->SetActive(false);
	}
}

void TimersDriver::RunOnce()
{
	UInt64 k = Platform::GetTickCount();

	TimersMap::iterator itor = m_activeTimers.begin();

	while(itor != m_activeTimers.end())
	{
		if(itor->first > k) break;

		Timer *timer = itor->second;

		m_itorNextTimer = itor;
		m_itorNextTimer++;
		m_activeTimers.erase(itor);
		//m_itorNextTimer = m_activeTimers.erase(itor);
		timer->GetPrivate()->SetDriverItor(NULL);
		m_bUseNextTimerItor = true;

		// 假如不是单次触发模式，将新的结束时间点加入到队列中
		if(!timer->IsSingleShot())
		{
			Add(timer);
		}

		Timer::TimeoutParam pa;
		pa.m_sender = timer;
		timer->TimeoutEvent.Dispatch(pa);


		itor = m_itorNextTimer.GetIterator();
		m_bUseNextTimerItor = false;
	}
}
