#include "gui/RepeatBehavior.h"

using namespace nb;
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

RepeatBehavior::RepeatBehavior(const TimeSpan & ts)
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

DependencyProperty RepeatBehavior::CountProperty()
{
	static auto dp = DependencyProperty::registerDependency<RepeatBehavior, int>("Count");
	return dp;
}

DependencyProperty RepeatBehavior::DurationProperty()
{
	static auto dp = DependencyProperty::registerDependency<RepeatBehavior, TimeSpan>("Duration");
	return dp;
}

	