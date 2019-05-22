#pragma once
#include "Timeline.h"

namespace nb { namespace gui {

class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline();

protected:
	AnimationTimeline();

	virtual void progressing(double progress) = 0;
};

}}