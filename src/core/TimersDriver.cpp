#include "TimersDriver.h"
#include "core/Timer.h"

using namespace nb::core;

TimersDriver *TimersDriver::instance()
{
	static TimersDriver *p = nullptr;
	if (!p)
		p = new TimersDriver();
	return p;
}

void TimersDriver::add(Timer *timer)
{
	remove(timer);
	m_tickSequence.insert(std::make_pair(nb::getTickCount() + timer->interval(), timer));
}

void TimersDriver::remove(Timer *timer)
{
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); ++iter)
	{
		if (iter->second == timer)
		{
			m_tickSequence.erase(iter);
			return;
		}
	}
}

bool TimersDriver::has(Timer * timer) const
{
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); ++iter)
		if (iter->second == timer)
			return true;

	return false;
}

void TimersDriver::drive()
{
	uint64_t currentTick = nb::getTickCount();
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); )
	{
		//到点的timer发送事件并移除此tick对应的timer序列
		if (iter->first <= currentTick)
		{
			Timer *timer = iter->second;
			Timer::TickArgs args;
			timer->TickEvent.dispatch(args);
			iter = m_tickSequence.erase(iter);
			// 假如不是单次触发模式，将此timer重新加入到队列中
			if (!timer->isSingleShot())
				m_tickSequence.insert(std::make_pair(nb::getTickCount() + timer->interval(), timer));
		}
		else
		{
			//大于代表后面的都为到点，全部忽略
			break;
		}
	}
}
