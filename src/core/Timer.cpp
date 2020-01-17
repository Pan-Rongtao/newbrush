#include "core/Timer.h"

using namespace nb;

bool								Timer::m_onDispatching = false;		//标记正在dispatch期间
std::set<Timer *>					Timer::m_timerRemovedOnDispatching;	//记录在dispatch期间调用stop()/remove()的timer
std::multimap<uint64_t, Timer *>	Timer::m_tickSequence;

Timer::Timer()
	: Timer(1000, false)
{
}

Timer::Timer(uint64_t ms, bool singleShot)
	: m_interval(ms)
	, m_singleShot(singleShot)
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
	add(this);
}

void Timer::stop()
{
	remove(this);
}

bool Timer::isActive() const
{
	return std::find_if(m_tickSequence.begin(), m_tickSequence.end(), [this](const std::pair<uint64_t, Timer *> &p) {
		return (p.second == this); }) != m_tickSequence.end();
}

void Timer::driveInLoop()
{
	uint64_t currentTick = nb::getTickCount();
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); )
	{
		//大于等于表示到点的timer，发送事件并移除此timer，
		//小于代表后面的都未到点，全部忽略
		if (currentTick >= iter->first)
		{
			Timer *timer = iter->second;
			m_onDispatching = true;			//标记以使记录在dispatch期间调用stop()/remove()的timer，供是否重新add该timer提供判断依据
			timer->Tick.invoke({ timer });
			m_onDispatching = false;
			iter = remove(timer);
			// 假如timer是单次触发模式，或者在dispatch期间已经被stop，不再将此timer重新加入到队列中
			if (!timer->isSingleShot() && m_timerRemovedOnDispatching.find(timer) == m_timerRemovedOnDispatching.end())
			{
				add(timer);
			}
			m_timerRemovedOnDispatching.clear();
		}
		else
		{
			break;
		}
	}
}

void Timer::add(Timer * timer)
{
	m_tickSequence.insert({ nb::getTickCount() + timer->interval(), timer } );
}

std::multimap<uint64_t, Timer *>::iterator Timer::remove(Timer *timer)
{
	for (auto iter = m_tickSequence.begin(); iter != m_tickSequence.end(); ++iter)
	{
		if (iter->second == timer)
		{
			if (m_onDispatching)
			{
				m_timerRemovedOnDispatching.insert(timer);
			}
			return m_tickSequence.erase(iter);
		}
	}
	return m_tickSequence.end();
}
