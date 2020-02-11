#pragma once
#include "newbrush/gui/RangeBase.h"

namespace nb{ namespace gui{

class NB_API Slider : public RangeBase
{
public:
	Slider();
	virtual ~Slider() = default;

public:
	/*Property_rw<int>				Delay;
	Property_rw<int>				Interval;
	Property_rw<OrientationE>		Orientation;
	Property_rw<bool>				IsDirectionReversed;*/

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
