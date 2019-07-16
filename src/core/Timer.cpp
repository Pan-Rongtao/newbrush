#include "core/Timer.h"

using namespace nb::core;

std::multimap<uint64_t, Timer *>	Timer::m_tickSequence;

Timer::Timer()
	: m_interval(1000)
	, m_singleShot(false)
	, m_stopFlag(false)
{
}

Timer::Timer(uint64_t ms, bool singleShot)
	: m_interval(ms)
	, m_singleShot(singleShot)
	, m_stopFlag(false)
{
}

Timer::~Timer()
{
	stop();
}

void Timer::setInterval(uint64_t msec)
{
	m_interval = msec;
}

uint64_t Timer::interval() const
{
	return m_interval;
}

void Timer::setSingleShot(bool singleShot)
{
	m_singleShot = singleShot;
}

bool Timer::isSingleShot() const
{
	return m_singleShot;
}

void Timer::start(int msec)
{
	setInterval(msec);
	start();
}

void Timer::start()
{
	remove(this);
	m_tickSequence.insert(std::make_pair(NB_TICK_COUT + interval(), this));
}

void Timer::stop()
{
	remove(this);
}

bool Timer::isActive() const
{
	return std::find_if(m_tickSequence.begin(), m_tickSequence.end(), [this](const std::pair<uint64_t, Timer *> &p) {
		return (p.second == this && !p.second->m_stopFlag); }) != m_tickSequence.end();
}

void Timer::drive()
{
	uint64_t currentTick = NB_TICK_COUT;
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); )
	{
		//到点的timer发送事件并移除此tick对应的timer序列
		if (currentTick >= iter->first)
		{
			Timer *timer = iter->second;
			if (timer->m_stopFlag)
			{
				iter = m_tickSequence.erase(iter);
			}
			else
			{
				Timer::TickArgs args;
				timer->TickEvent.dispatch(args);
				iter = m_tickSequence.erase(iter);
				// 假如不是单次触发模式，将此timer重新加入到队列中
				if (!timer->isSingleShot())
					m_tickSequence.insert(std::make_pair(NB_TICK_COUT + timer->interval(), timer));
			}
		}
		else
		{
			//大于代表后面的都为到点，全部忽略
			break;
		}
	}
}

void Timer::remove(Timer *timer)
{
	for (auto const &iter : m_tickSequence)
	{
		if (iter.second == timer)
		{
			iter.second->m_stopFlag = true;
			return;
		}
	}
}
