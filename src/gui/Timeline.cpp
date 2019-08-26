#include "gui/Timeline.h"

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
	: BeginTime([&](TimeSpan v) { set(BeginTimeProperty(), v); }, [&]()->TimeSpan& {return get<TimeSpan>(BeginTimeProperty()); })
	, Duration([&](TimeSpan v) { set(DurationProperty(), v); }, [&]()->TimeSpan& {return get<TimeSpan>(DurationProperty()); })
	, FillBehavior([&](FillBehaviorE v) { set(FillBehaviorProperty(), v); }, [&]()->FillBehaviorE& {return get<FillBehaviorE>(FillBehaviorProperty()); })
	, AutoReverse([&](bool v) { set(AutoReverseProperty(), v); }, [&]()->bool& {return get<bool>(AutoReverseProperty()); })
	, Repeat([&](RepeatBehavior v) { set(RepeatProperty(), v); }, [&]()->RepeatBehavior& {return get<RepeatBehavior>(RepeatProperty()); })
	, State([&]()->StateE& {return get<StateE>(StateProperty()); })
{
	m_timer.setInterval(1);
	m_timer.TickEvent += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	m_begTick = (uint64_t)(NB_TICK_COUT + BeginTime().totalMilliseconds());
	set(StateProperty(), StateE::Active);
	StateChangedEvent.dispatch({ State() });
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
	auto endTicks = m_begTick + Duration().totalMilliseconds();
	auto curTicks = NB_TICK_COUT;
	if (curTicks >= m_begTick)
	{
		auto progress = std::min<float>(1.0f, float((curTicks - m_begTick) / Duration().totalMilliseconds()));
		ProgressEvent.dispatch({ progress });
		if (curTicks >= endTicks)
		{
			set(StateProperty(), StateE::Stopped);
			StateChangedEvent.dispatch({ State() });
			m_timer.stop();
			CompleteEvent.dispatch({});
		}
	}
}
