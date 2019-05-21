#include "core/Timer.h"
#include "TimersDriver.h"

using namespace nb::core;

Timer::Timer()
	: Timer(1000, false)
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
	TimersDriver::instance()->add(this);
}

void Timer::stop()
{
	TimersDriver::instance()->remove(this);
}

bool Timer::isActive() const
{
	return TimersDriver::instance()->has(const_cast<Timer *>(this));
}

void Timer::drive()
{
	TimersDriver::instance()->drive();
}
