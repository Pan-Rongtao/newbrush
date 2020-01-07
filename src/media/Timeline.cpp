#include "media/Timeline.h"

using namespace nb;
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
{
	m_timer.setInterval(1);
	m_timer.TickEvent += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	auto beginTime = get<TimeSpan>(BeginTimeProperty());
	m_begTick = (uint64_t)(nb::getTickCount() + beginTime.totalMilliseconds());
	set(StateProperty(), StateE::Active);
	StateChangedEvent.invoke({ StateE::Active });
	m_timer.start();
}

DependencyProperty Timeline::BeginTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, TimeSpan>("BeginTime", TimeSpan());
	return dp;
}

DependencyProperty Timeline::DurationProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, TimeSpan>("Background", TimeSpan());
	return dp;
}

DependencyProperty Timeline::FillBehaviorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, TimeSpan>("Background", TimeSpan());
	return dp;
}

DependencyProperty Timeline::AutoReverseProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, TimeSpan>("Background", TimeSpan());
	return dp;
}

DependencyProperty Timeline::RepeatProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, RepeatBehavior>("Repeat", RepeatBehavior());
	return dp;
}

DependencyProperty Timeline::StateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, StateE>("State", StateE::Stopped);
	return dp;
}

void Timeline::onTick(const Timer::TickArgs & args)
{
	auto duration = get<TimeSpan>(DurationProperty());
	auto endTicks = m_begTick + duration.totalMilliseconds();
	auto curTicks = nb::getTickCount();
	if (curTicks >= m_begTick)
	{
		auto progress = std::min<float>(1.0f, float((curTicks - m_begTick) / duration.totalMilliseconds()));
		ProgressEvent.invoke({ progress });
		if (curTicks >= endTicks)
		{
			set(StateProperty(), StateE::Stopped);
			StateChangedEvent.invoke({ StateE::Stopped });
			m_timer.stop();
			CompleteEvent.invoke({});
		}
	}
}
