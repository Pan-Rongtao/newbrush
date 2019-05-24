#include "gui/Timeline.h"

using namespace nb::core;
using namespace nb::gui;

Timeline::Timeline()
	: Timeline(TimeSpan(), TimeSpan(), RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & beginTime)
	: Timeline(beginTime, TimeSpan(), RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & beginTime, const TimeSpan & duration)
	: Timeline(beginTime, duration, RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & beginTime, const TimeSpan & duration, const RepeatBehavior & repeatBehavior)
	: BeginTime(beginTime)
	, Duration(duration)
	, Repeat(repeatBehavior)
	, m_state(StateE::Stopped)
{
	State.getter([&]()->StateE & {return m_state; });
	m_timer.setInterval(1);
	m_timer.TickEvent += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	m_begTick = (uint64_t)(NB_TICK_COUT + BeginTime().totalMilliseconds());
	m_state = StateE::Active;
	StateChangedEvent.dispatch({ m_state });
	m_timer.start();
}

void Timeline::onTick(const Timer::TickArgs & args)
{
	auto endTicks = m_begTick + Duration().totalMilliseconds();
	auto curTicks = NB_TICK_COUT;
	if (curTicks >= m_begTick)
	{
		double progress = std::min(1.0, double(curTicks - m_begTick) / Duration().totalMilliseconds());
		ProgressEvent.dispatch({ progress });
		if (curTicks >= endTicks)
		{
			m_state = StateE::Stopped;
			StateChangedEvent.dispatch({ m_state });
			m_timer.stop();
			CompleteEvent.dispatch({});
		}
	}
}
