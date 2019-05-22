#pragma once
#include "Timeline.h"

namespace nb { namespace gui {

template<class T>
class NB_API AnimationTimeline : public Timeline
{
public:
	virtual ~AnimationTimeline() = default;

	core::Property_rw<T>	*TargetProperty;

protected:
	virtual void progressing(double progress) = 0;
	AnimationTimeline() : TargetProperty(nullptr)
	{
		ProgressEvent += [&](const Timeline::ProgressArgs &args) {	progressing(args.progress);	};
	}

};

}}