#include "media/AnimationTimeline.h"

using namespace nb;

AnimationTimeline::AnimationTimeline()
	: target(DependencyProperty::invalidProperty())
{
	ProgressEvent += [&](const EventArgs &args) {
//		progressing(args.progress);	
	};
}
