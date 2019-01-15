#pragma once
#include "AnimationTimeline.h"

namespace nb { namespace gui {

class NB_API ObjectAnimation : public AnimationTimeline
{
public:
	ObjectAnimation();
	virtual ~ObjectAnimation();

protected:
	virtual void OnFrameChanged(const nb::core::TimeSpan &frame) {}
};

}}
