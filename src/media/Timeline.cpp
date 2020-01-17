#include "media/Timeline.h"

using namespace nb;

Timeline::Timeline()
	: Timeline(TimeSpan(), TimeSpan::fromSeconds(1), RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & _beginTime)
	: Timeline(_beginTime, TimeSpan::fromSeconds(1), RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const TimeSpan & _duration)
	: Timeline(_beginTime, _duration, RepeatBehavior(RepeatBehavior(1)))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const TimeSpan & _duration, const RepeatBehavior & _repeatBehavior)
	: m_state(StateE::Stopped)
	, m_autoReversel(false)
	, m_fillBehavior(FillBehaviorE::HoldEnd)
	, m_repeatBehavior(_repeatBehavior)
	, m_timer(1)
{
	setBeginTime(_beginTime);
	setDuration(_duration);
	m_timer.Tick += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	m_startTick = (uint64_t)(nb::getTickCount() + m_beginTime.totalMilliseconds());
	m_state = StateE::Active;
	StateChanged.invoke({ this });
	m_timer.start();
}

void Timeline::setBeginTime(const TimeSpan & beginTime) &
{
	if (beginTime < TimeSpan::zero())
		nbThrowException(std::invalid_argument, "beginTime is negative[%s]", beginTime.toString().data());
	m_beginTime = beginTime;
}

const TimeSpan & Timeline::beginTime() const
{
	return m_beginTime;
}

void Timeline::setDuration(const TimeSpan & duration) &
{
	if (duration < TimeSpan::zero())
		nbThrowException(std::invalid_argument, "duration is negative[%s]", duration.toString().data());
	m_duration = duration;
}

const TimeSpan & Timeline::duration() const
{
	return m_duration;
}

void Timeline::setAutoReversel(bool autoReversel) &
{
	m_autoReversel = autoReversel;
}

bool Timeline::autoReversel() const
{
	return m_autoReversel;
}

void Timeline::setFillBehavior(FillBehaviorE fillBehavior) &
{
	m_fillBehavior = fillBehavior;
}

Timeline::FillBehaviorE Timeline::fillBehavior() const
{
	return m_fillBehavior;
}

void Timeline::setRepeatBehavior(const RepeatBehavior & repeatBehavior) &
{
	m_repeatBehavior = repeatBehavior;
}

RepeatBehavior Timeline::repeatBehavior() const
{
	return m_repeatBehavior;
}

Timeline::StateE Timeline::currentState() const
{
	return m_state;
}

TimeSpan Timeline::getCurrentTime() const
{
	return TimeSpan::fromMilliseconds((int)(getCurrentProgress() * m_duration.totalMilliseconds()));
}

float Timeline::getCurrentProgress() const
{
	if (m_state == StateE::Stopped)
	{
		return 0.0f;
	}
	else
	{
		auto passingTicks = nb::getTickCount() - m_startTick;
		auto progress = 0.0;
		auto dir = std::lldiv(passingTicks, (uint64_t)m_duration.totalMilliseconds());
		if (!autoReversel())
		{
			progress = dir.rem;
		}
		else
		{
			progress = (dir.quot % 2 == 0) ? dir.rem : 1.0 - dir.rem;
		}
		return (float)progress;
	}
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

uint64_t Timeline::calcFillingTicks()
{
	auto ticks = 0.0;
	if (m_repeatBehavior.hasCount())
	{
		auto oneLoop = duration().totalMilliseconds();
		//如果自动逆动画，则一圈变成两倍长度
		if (autoReversel())
		{
			oneLoop *= 2;
		}
		ticks = oneLoop * m_repeatBehavior.getCount();
	}
	else if (m_repeatBehavior.hasDuration())
	{
		ticks = m_repeatBehavior.getDuration().totalMilliseconds();
	}
	else
	{
		ticks = std::numeric_limits<double>::max();
	}
	return (uint64_t)ticks;
}

void Timeline::onTick(const EventArgs & args)
{
	auto curTicks = nb::getTickCount();
	auto endTicks = m_startTick + calcFillingTicks();
	if (curTicks >= m_startTick)
	{
		Process.invoke({ this });
		onProcessing();
		if (curTicks >= endTicks)
		{
			m_state = StateE::Filling;
			StateChanged.invoke({ this });
			onStateChanged();
			m_timer.stop();
			Completed.invoke({ this });
			onCompleted();
		}
	}
}
