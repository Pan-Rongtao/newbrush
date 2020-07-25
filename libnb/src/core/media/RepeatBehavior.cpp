#include "newbrush/core/media/RepeatBehavior.h"

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

bool RepeatBehavior::operator==(const RepeatBehavior & other) const
{
	return !(operator !=(other));
}

bool RepeatBehavior::operator!=(const RepeatBehavior & other) const
{
	if (m_type != other.m_type)
	{
		return false;
	}
	else
	{
		return m_type == Type::Forever ? true : (m_type == Type::Counter ? getCount() == other.getCount() : getDuration() == other.getDuration());
	}
}
