#include "gui/AnimationTimeline.h"
#include "gui/Easing.h"

using namespace nb::core;
using namespace nb::gui;

AnimationTimeline::AnimationTimeline()
{
	ProgressEvent += [&](const Timeline::ProgressArgs &args) {
		progressing(args.progress);
	};
}

AnimationTimeline::~AnimationTimeline()
{
}
