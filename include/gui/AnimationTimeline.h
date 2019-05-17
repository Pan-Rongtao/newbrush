#pragma once
#include "Timeline.h"

namespace nb { namespace gui {

class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline();

	virtual float getCurrentValue(const nb::core::TimeSpan &frame);

	virtual void AnimateTo(int frame){}

protected:
	AnimationTimeline();
};

}}