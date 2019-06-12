#include "gui/RepeatBehavior.h"

using namespace nb::core;
using namespace nb::gui;

RepeatBehavior::RepeatBehavior()
	: m_count(1)
	, m_duration(TimeSpan())
	, m_hasCount(true)
	, m_hasDuration(false)
{
	Count.getter([&]()->int& { if (!m_hasCount)	nbThrowException(std::logic_error, "not a 'Count assigned' RepeatBehavior");	return m_count; });
	Duration.getter([&]()->TimeSpan& { if (!m_hasDuration)	nbThrowException(std::logic_error, "not a 'Duration assigned' RepeatBehavior");	return m_duration; });
}

RepeatBehavior::RepeatBehavior(int count)
	: m_count(count)
	, m_duration(TimeSpan())
	, m_hasCount(true)
	, m_hasDuration(false)
{
}

RepeatBehavior::RepeatBehavior(const nb::core::TimeSpan & ts)
	: m_count(-1)
	, m_duration(ts)
	, m_hasCount(true)
	, m_hasDuration(false)
{
}

RepeatBehavior RepeatBehavior::forever()
{
	RepeatBehavior rb;
	rb.m_count = -1;
	rb.m_duration = TimeSpan();
	rb.m_hasCount = false;
	rb.m_hasDuration = false;
	return rb;
}

void RepeatBehavior::operator =(const RepeatBehavior &other)
{
	m_count = other.m_count;
	m_duration = other.m_duration;
	m_hasCount = other.m_hasCount;
	m_hasDuration = other.m_hasDuration;
}

bool RepeatBehavior::operator==(const RepeatBehavior & other) const
{
	return !(operator !=(other));
}

bool RepeatBehavior::operator!=(const RepeatBehavior & other) const
{
	return m_count != other.m_count || m_duration != other.m_duration || m_hasCount != other.m_hasCount || m_hasDuration != other.m_hasDuration;
}

	