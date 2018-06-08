#pragma once

#include "system/Timer.h"
#include "system/TimeSpan.h"

namespace nb { namespace Media{

class Timeline;
class TimelinePrivate : public nbObject
{
public:
	TimelinePrivate(Timeline *owner);
	virtual ~TimelinePrivate(void);

	void Begin();
	void SetCurrentFrame(const nb::System::TimeSpan &frame);

	nb::System::Timer * GetTimer() const;

	void OnTimerTimeout(nb::System::Timer::TimeoutParam &param);

private:
	nb::System::TimerPtr m_timer;
	Timeline *m_owner;

	long long m_beginClock;
};

}}
