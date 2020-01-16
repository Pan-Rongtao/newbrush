#pragma once
#include "Timeline.h"
#include "../core/Easing.h"
#include "../core/DependencyProperty.h"

namespace nb{

class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline();
	virtual ~AnimationTimeline() = default;

	DependencyProperty target;

protected:
	virtual void progressing(float progress) = 0;

};

}