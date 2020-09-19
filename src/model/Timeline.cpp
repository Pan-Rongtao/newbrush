#include "newbrush/model/Timeline.h"

using namespace nb;

RepeatBehavior::RepeatBehavior(float count)
	: m_type(Type::Counter)
	, m_count(count)
{
}

RepeatBehavior::RepeatBehavior(const TimeSpan & duration)
	: m_type(Type::Duration)
	, m_duration(duration)
{
}

RepeatBehavior RepeatBehavior::fromCount(float count)
{
	return RepeatBehavior(count);
}

RepeatBehavior RepeatBehavior::fromDuration(const TimeSpan & duration)
{
	return RepeatBehavior(duration);
}

RepeatBehavior RepeatBehavior::forever()
{
	RepeatBehavior rb(0.0f);
	rb.m_type = Type::Forever;
	return rb;
}

bool RepeatBehavior::isForever() const
{
	return m_type == Type::Forever;
}

bool RepeatBehavior::hasCount() const
{
	return m_type == Type::Counter;
}

float RepeatBehavior::getCount() const
{
	if (!hasCount())
		nbThrowException(std::logic_error, "not a count RepeatBehavior");
	return m_count;
}

bool RepeatBehavior::hasDuration() const
{
	return m_type == Type::Duration;
}

TimeSpan RepeatBehavior::getDuration() const
{
	if (!hasDuration())
		nbThrowException(std::logic_error, "not a duration RepeatBehavior");
	return m_duration;
}


//////////////////////////////
Timeline::Timeline()
	: Timeline(TimeSpan(), TimeSpan::fromSeconds(1), RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime)
	: Timeline(_beginTime, TimeSpan::fromSeconds(1), RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const TimeSpan & _duration)
	: Timeline(_beginTime, _duration, RepeatBehavior(1))
{
}

Timeline::Timeline(const TimeSpan & _beginTime, const TimeSpan & _duration, const RepeatBehavior & _repeatBehavior)
	: m_state(StateE::Stopped)
	, m_autoReversel(false)
	, m_fillBehavior(FillBehaviorE::HoldEnd)
	, m_repeatBehavior(_repeatBehavior)
	, m_timer(1)
	, m_startTick(0)
	, m_duration(_duration)
{
	setBeginTime(_beginTime);
	m_timer.Tick += std::bind(&Timeline::onTick, this, std::placeholders::_1);
}

void Timeline::begin()
{
	m_startTick = (uint64_t)(getTickCount() + m_beginTime.totalMilliseconds());
	m_state = StateE::Active;
	StateChanged.invoke({ this });
	onStateChanged();
	m_timer.start();
}

void Timeline::setName(const std::string & name)
{
	m_name = name;
}

const std::string & Timeline::name() const
{
	return m_name;
}

void Timeline::stop()
{
	m_timer.stop();
}

void Timeline::setBeginTime(const TimeSpan & beginTime)
{
	if (beginTime < TimeSpan::zero())
		nbThrowException(std::invalid_argument, "beginTime is negative[%s]", beginTime.toString().data());
	m_beginTime = beginTime;
}

const TimeSpan & Timeline::beginTime() const
{
	return m_beginTime;
}

void Timeline::setDuration(const TimeSpan & duration)
{
	m_duration = duration;
}

const TimeSpan & Timeline::duration() const
{
	return m_duration;
}

void Timeline::setAutoReversel(bool autoReversel)
{
	m_autoReversel = autoReversel;
}

bool Timeline::autoReversel() const
{
	return m_autoReversel;
}

void Timeline::setFillBehavior(FillBehaviorE fillBehavior)
{
	m_fillBehavior = fillBehavior;
}

FillBehaviorE Timeline::fillBehavior() const
{
	return m_fillBehavior;
}

void Timeline::setRepeatBehavior(const RepeatBehavior & repeatBehavior)
{
	m_repeatBehavior = repeatBehavior;
}

RepeatBehavior Timeline::repeatBehavior() const
{
	return m_repeatBehavior;
}

StateE Timeline::currentState() const
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
	if (autoReversel() && div.quot % 2 == 1)
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
	return m_duration;
}

uint64_t Timeline::calcFillingTicks()
{
	auto ticks = 0.0;
	if (m_repeatBehavior.hasCount())
	{
		auto oneLoop = getActualDurationTimespan().totalMilliseconds();
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
