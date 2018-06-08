#include "system/Timer.h"
#include "TimersDriver.h"
#include "TimerPrivate.h"

using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(Timer, nbObject, NULL, NULL);

Timer::Timer(void)
	: m_interval(1000)
	, m_isSingleShot(false)
{
	m_private = new TimerPrivate();
}

Timer::~Timer(void)
{
	TimersDriver::GetInstance().Remove(this);
	delete m_private;
}

void Timer::SetInterval(int msec)
{
	m_interval = msec;
}

void Timer::SetSingleShot(bool singleShot)
{
	m_isSingleShot = singleShot;
}

void Timer::Start(int msec)
{
	m_interval = msec;
	Start();
}

void Timer::Start()
{
	TimersDriver::GetInstance().Add(this);
}

void Timer::Stop()
{
	TimersDriver::GetInstance().Remove(this);
}

bool Timer::IsActive() const
{
	return m_private->IsActive();
}

void Timer::DriveRun()
{
	TimersDriver::GetInstance().RunOnce();
}
