#include "newbrush/core/media/animation/Timeline.h"

using namespace nb;

Duration::Duration(const TimeSpan & ts)
	: m_ts(new TimeSpan(ts))
{
	if (ts < TimeSpan::zero())
		nbThrowException(std::invalid_argument, "duration is negative[%s]", ts.toString().data());
}

Duration::Duration(const Duration & other)
{
	m_ts = other.m_ts ? new TimeSpan(*other.m_ts) : nullptr;
}

void Duration::operator=(const Duration & other)
{
	delete m_ts;
	m_ts = other.m_ts ? new TimeSpan(*other.m_ts) : nullptr;
}

Duration Duration::automatic()
{
	return Duration();
}

bool Duration::hasTimeSpan() const
{
	return m_ts != nullptr;
}

TimeSpan Duration::timeSpan() const
{
	if (!hasTimeSpan())	nbThrowException(std::logic_error, "doesn't has TimeSpan.");
	return *m_ts;
}

Duration::Duration()
	: m_ts(nullptr)
{
}

Timeline::Timeline()
	: Timeline(TimeSpan(), Duration::automatic(), RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime)
	: Timeline(_beginTime, Duration::automatic(), RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const Duration & _duration)
	: Timeline(_beginTime, _duration, RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const Duration & _duration, const RepeatBehavior & _repeatBehavior)
	: m_state(StateE::Stopped)
	, m_timer(1)
	, m_startTick(0)
{
	setValue(BeginTimeProperty(), _beginTime);
	setValue(DurationProperty(), _duration);
	setValue(RepeatBehaviorProperty(), _repeatBehavior);
	m_timer.Tick += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	m_startTick = (uint64_t)(getTickCount() + getValue<TimeSpan>(BeginTimeProperty()).totalMilliseconds());
	m_state = StateE::Active;
	StateChanged.invoke({ this });
	onStateChanged();
	m_timer.start();
}

void Timeline::stop()
{
	m_timer.stop();
}

DependencyPropertyPtr Timeline::BeginTimeProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, TimeSpan>("BeginTime", TimeSpan());
	return dp;
}

DependencyPropertyPtr Timeline::DurationProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, Duration>("Duration", Duration::automatic());
	return dp;
}

DependencyPropertyPtr Timeline::AutoReverseProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, bool>("AutoReverse", false);
	return dp;
}

DependencyPropertyPtr Timeline::FillBehaviorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, FillBehaviorE>("FillBehavior", FillBehaviorE::HoldEnd);
	return dp;
}

DependencyPropertyPtr Timeline::RepeatBehaviorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Timeline, RepeatBehavior>("RepeatBehavior", RepeatBehavior(1));
	return dp;
}

Timeline::StateE Timeline::currentState() const
{
	return m_state;
}

TimeSpan Timeline::getCurrentTime() const
{
	return TimeSpan::fromMilliseconds((int)(getCurrentProgress() * getActualDurationTimespan().totalMilliseconds()));
}

float Timeline::getCurrentProgress() const
{
	if (m_startTick == 0)
	{
		return 0.0f;
	}

	auto durationTicks = (uint64_t)getActualDurationTimespan().totalMilliseconds();
	auto passingTicks = getTickCount() - m_startTick;
	if (durationTicks == 0)
	{
		return 0.0f;
	}
	else if (passingTicks == durationTicks)
	{
		return 1.0f;
	}

	auto div = std::lldiv(passingTicks, durationTicks);
	auto progress = (double)div.rem / (double)durationTicks;
	auto autoReverse = getValue<bool>(AutoReverseProperty());
	if (autoReverse && div.quot % 2 == 1)
	{
		progress = 1.0 - progress;
	}
	return (float)progress;
}

void Timeline::onStateChanged()
{
}

void Timeline::onProcessing()
{
}

void Timeline::onCompleted()
{
}

TimeSpan Timeline::getActualDurationTimespan() const
{
	auto const &duration = getValue<Duration>(DurationProperty());
	return duration.hasTimeSpan() ? duration.timeSpan() : TimeSpan(0, 0, 1);
}

uint64_t Timeline::calcFillingTicks()
{
	auto ticks = 0.0;
	auto const & repeatBehavior = getValue<RepeatBehavior>(RepeatBehaviorProperty());
	if (repeatBehavior.hasCount())
	{
		auto oneLoop = getActualDurationTimespan().totalMilliseconds();
		//如果自动逆动画，则一圈变成两倍长度
		auto autoReverse = getValue<bool>(AutoReverseProperty());
		if (autoReverse)
		{
			oneLoop *= 2;
		}
		ticks = oneLoop * repeatBehavior.getCount();
	}
	else if (repeatBehavior.hasDuration())
	{
		ticks = repeatBehavior.getDuration().totalMilliseconds();
	}
	else
	{
		ticks = std::numeric_limits<double>::max();
	}
	return (uint64_t)ticks;
}

void Timeline::onTick(const EventArgs & args)
{
	auto curTicks = getTickCount();
	auto fillingTicks = calcFillingTicks();
	auto endTicks = m_startTick + fillingTicks;
	if (curTicks >= m_startTick)
	{
		if (fillingTicks != 0)
		{
			//不要换顺序
			onProcessing();
			Process.invoke({ this });
		}
		if (curTicks >= endTicks)
		{
			m_timer.stop();
			m_state = StateE::Filling;
			StateChanged.invoke({ this });
			onStateChanged();
			Completed.invoke({ this });
			onCompleted();
		}
	}
}
