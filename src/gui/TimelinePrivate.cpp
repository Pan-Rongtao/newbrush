#include "TimelinePrivate.h"
#include "gui/Timeline.h"
#include "system/Platform.h"

using namespace nb::Media;
using namespace nb::System;

TimelinePrivate::TimelinePrivate(Timeline *owner)
	: m_owner(owner)
	, m_beginClock(0)
{
	
}

TimelinePrivate::~TimelinePrivate(void)
{
	
}

nb::System::Timer * TimelinePrivate::GetTimer() const
{
	if(m_timer == NULL) 
	{
		TimelinePrivate *pThis = const_cast<TimelinePrivate *>(this);
		pThis->m_timer = new Timer();
		pThis->m_timer->TimeoutEvent.Add(pThis, &TimelinePrivate::OnTimerTimeout);
	}
	return m_timer;
}

void TimelinePrivate::Begin()
{
	GetTimer()->Start(1);
	m_beginClock = nb::System::Platform::GetTickCount();
}

void TimelinePrivate::OnTimerTimeout(Timer::TimeoutParam &param)
{
	int k = nb::System::Platform::GetTickCount() - m_beginClock;

	nb::System::TimeSpan span = m_owner->m_beginTime + nb::System::TimeSpan(0, 0, 0, k);

	nb::System::TimeSpan *dur = m_owner->Duration;//(0, 0, 3, 0);

	if(span >= *dur)
	{
		span = *dur;
		m_timer->Stop();
	}

	m_owner->OnFrameChanged(span);
}

void TimelinePrivate::SetCurrentFrame(const nb::System::TimeSpan &frame)
{
	m_owner->OnFrameChanged(frame);
}

