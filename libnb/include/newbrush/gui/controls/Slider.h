#pragma once
#include "newbrush/gui/controls/RangeBase.h"

namespace nb{

class NB_API Slider : public RangeBase
{
	RTTR_ENABLE(RangeBase)
public:
	Slider() = default;
	virtual ~Slider() = default;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}