#pragma once
#include "Timeline.h"
#include "core/Easing.h"

namespace nb { namespace gui {

template<class T>
class NB_API AnimationTimeline : public Timeline
{
public:
	AnimationTimeline() : TargetProperty(nullptr), Easing(std::make_shared<LinearEase>())
	{
		ProgressEvent += [&](const Timeline::ProgressArgs &args) {	progressing(args.progress);	};
	}
	virtual ~AnimationTimeline() = default;

	core::Property_rw<T>									*TargetProperty;
	core::Property_rw<std::shared_ptr<core::EasingBase>>	Easing;

protected:
	virtual void progressing(float progress) = 0;

};

}}