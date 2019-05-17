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
{
}

Timeline::~Timeline(void)
{
}

void Timeline::start()
{
}
