#pragma once
#include "Timeline.h"
#include "EasingFunctionBase.h"

namespace nb { namespace gui {

class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline();
	virtual ~AnimationTimeline();

	virtual float GetFrameValue(const nb::core::TimeSpan &frame);

	virtual void AnimateTo(int frame){}

};

}}