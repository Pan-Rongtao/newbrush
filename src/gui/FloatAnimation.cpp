#include "gui/FloatAnimation.h"
#include "gui/Storyboard.h"
#include "gui/UIElement.h"

using namespace nb::Media;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(FloatAnimation, AnimationTimeline, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(FloatAnimation, From, Float, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(FloatAnimation, To, Float, NULL);

FloatAnimation::FloatAnimation(void)
{
	From() = 0;
	To() = 0;
}

FloatAnimation::~FloatAnimation(void)
{
}

//void FloatAnimation::AnimateTo(int frame)
//{
//}

void FloatAnimation::OnFrameChanged(const nb::System::TimeSpan &frame)
{
	nb::Gui::UIElement *element = Storyboard::GetTarget(this);
	if(element == NULL) return;

	DependencyProperty *prop = Storyboard::GetTargetProperty(this);
	if(prop == NULL) return;

	float v = GetFrameValue(frame);
	//v = 1-v;
	float from = (Float)From();
	float to = (Float)To();

	v = from + (to - from) * v;

	element->SetValueValue(prop, (Float)v);
}
