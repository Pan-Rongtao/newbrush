#pragma once
#include "AnimationTimeline.h"
#include "../core/Color.h"

namespace nb{ namespace gui {

class NB_API ColorAnimation : public AnimationTimeline
{
public:
	ColorAnimation();
	virtual ~ColorAnimation();

	virtual void AnimateTo(int frame);

	nb::core::Property_rw<nb::core::Color>		From;
	nb::core::Property_rw<nb::core::Color>		To;

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame);
};

}}
