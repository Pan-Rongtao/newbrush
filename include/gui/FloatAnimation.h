#pragma once
#include "AnimationTimeline.h"

namespace nb { namespace gui {

class NB_API FloatAnimation : public AnimationTimeline
{
public:
	FloatAnimation(void);
	virtual ~FloatAnimation(void);

//		virtual void AnimateTo(int frame);

	nb::core::Property_rw<double>		From;
	nb::core::Property_rw<double>		To;

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame);

};

}}
