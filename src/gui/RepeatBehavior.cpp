#include "gui/RepeatBehavior.h"

using namespace nb::core;
using namespace nb::gui;

RepeatBehavior::RepeatBehavior()
	: RepeatBehavior(1)
{
}

RepeatBehavior::RepeatBehavior(int count)
	: Count([&]() {return get<int>(CountProperty()); })
	, Duration([&]() {return get<TimeSpan>(DurationProperty()); })
{
}

RepeatBehavior::RepeatBehavior(const nb::core::TimeSpan & ts)
	: Count([&]() {return get<int>(CountProperty()); })
	, Duration([&]() {return get<TimeSpan>(DurationProperty()); })
{
}

RepeatBehavior RepeatBehavior::forever()
{
	RepeatBehavior rb;
	return rb;
}

void RepeatBehavior::operator =(const RepeatBehavior &other)
{
}

bool RepeatBehavior::operator==(const RepeatBehavior & other) const
{
	return !(operator !=(other));
}

bool RepeatBehavior::operator!=(const RepeatBehavior & other) const
{
	return false;// m_count != other.m_count || m_duration != other.m_duration || m_hasCount != other.m_hasCount || m_hasDuration != other.m_hasDuration;
}

const DependencyProperty RepeatBehavior::CountProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<RepeatBehavior, int>("Count", 0);
	return dp;
}

const DependencyProperty RepeatBehavior::DurationProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<RepeatBehavior, TimeSpan>("Duration", TimeSpan());
	return dp;
}

	