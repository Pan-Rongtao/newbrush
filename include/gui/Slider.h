#pragma once
#include "../gui/RangeBase.h"

namespace nb{ namespace gui{

class NB_API Slider : public RangeBase
{
public:
	Slider();
	virtual ~Slider();

public:
	nb::core::Property_rw<int>				Delay;
	nb::core::Property_rw<int>				Interval;
	nb::core::Property_rw<Orientation>		Orientation1;
	nb::core::Property_rw<bool>				IsDirectionReversed;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
