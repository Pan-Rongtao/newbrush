#include "gui/AnimationTimeline.h"
#include "gui/EasingFunctionBase.h"
#include "gui/LineEase.h"

using namespace nb::Media;

NB_OBJECT_TYPE_IMPLEMENT(AnimationTimeline, Timeline, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX_1(AnimationTimeline, EasingFun, EasingFunctionBase, NULL);


AnimationTimeline::AnimationTimeline(void)
{
}

AnimationTimeline::~AnimationTimeline(void)
{
}

float AnimationTimeline::GetFrameValue(const nb::System::TimeSpan &frame)
{
	EasingFunctionBase *fun = EasingFun();
	if(fun == NULL)
	{
		static LineEase ease;
		fun = &ease;
	}

	const nb::System::TimeSpan *t = Duration;
	double rate = frame.ToSeconds() / t->ToSeconds();
	return fun->GetEase(rate);
}
