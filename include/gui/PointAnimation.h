#pragma once
#include "AnimationTimeline.h"
#include "../core/Point.h"

namespace nb{ namespace gui {

class NB_API PointAnimation : public AnimationTimeline
{
public:
	PointAnimation();
	virtual ~PointAnimation();

	virtual void AnimateTo(int frame);

	nb::core::Property_rw<nb::core::Point>		From;
	nb::core::Property_rw<nb::core::Point>		To;

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame);
};

}}
