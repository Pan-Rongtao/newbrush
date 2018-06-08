#pragma once

#include "Timeline.h"
#include "EasingFunctionBase.h"

namespace nb { namespace Media {

class NB_EXPORT AnimationTimeline : public Timeline
{
	NB_OBJECT_TYPE_DECLARE();

public:
	AnimationTimeline(void);
	virtual ~AnimationTimeline(void);

	virtual float GetFrameValue(const nb::System::TimeSpan &frame);

	virtual void AnimateTo(int frame){}

	NB_OBJECT_PROPERTY_DECLARE(EasingFun, EasingFunctionBase);
};

}}