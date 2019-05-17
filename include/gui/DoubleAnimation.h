#pragma once
#include "AnimationTimeline.h"

namespace nb { namespace gui {

class NB_API DoubleAnimation : public AnimationTimeline
{
public:
	DoubleAnimation();
	virtual ~DoubleAnimation();

//		virtual void AnimateTo(int frame);

	nb::core::Property_rw<double>		From;
	nb::core::Property_rw<double>		To;
	nb::core::Property_rw<double>		By;
	//nb::core::Property_rw<>			EasingFunction;

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame);

};

}}
