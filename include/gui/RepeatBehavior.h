#pragma once
#include "../core/Property.h"
#include "../core/TimeSpan.h"
#include "../gui/DependencyProperty.h"
#include "../gui/DependencyObject.h"

namespace nb{namespace gui{

class NB_API RepeatBehavior : public DependencyObject
{
public:
	RepeatBehavior();
	RepeatBehavior(int count);
	RepeatBehavior(const nb::core::TimeSpan &ts);
	static RepeatBehavior forever();

	void operator =(const RepeatBehavior &other);
	bool operator ==(const RepeatBehavior &other) const;
	bool operator !=(const RepeatBehavior &other) const;

	core::Property_r<int>				Count;
	core::Property_r<core::TimeSpan>	Duration;

	static const DependencyProperty CountProperty();
	static const DependencyProperty DurationProperty();

};

}}