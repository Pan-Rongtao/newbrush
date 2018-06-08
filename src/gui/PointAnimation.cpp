#include "gui/PointAnimation.h"
#include "gui/Storyboard.h"
#include "gui/UIElement.h"

using namespace nb::Media;

using namespace nb::Core;
using namespace nb::System;

NB_OBJECT_TYPE_IMPLEMENT(PointAnimation, AnimationTimeline, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(PointAnimation, From, nb::System::Point, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(PointAnimation, To, nb::System::Point, NULL);


PointAnimation::PointAnimation(void)
{
	From() = nb::System::Point(0, 0);
	To() = nb::System::Point(0, 0);
}

PointAnimation::~PointAnimation(void)
{
}

void PointAnimation::AnimateTo(int frame)
{
}

void PointAnimation::OnFrameChanged(const nb::System::TimeSpan &frame)
{
	nb::Gui::UIElement *element = Storyboard::GetTarget(this);
	if(element == NULL) return;

	DependencyProperty *prop = Storyboard::GetTargetProperty(this);
	if(prop == NULL) return;

	float v = GetFrameValue(frame);

	nb::System::Point from = (nb::System::Point)From();
	nb::System::Point to = (nb::System::Point)To();


	nb::System::Point point;
	point.SetXY((from.GetX()+(to.GetX()-from.GetX())*(1-v)), (from.GetY()+(to.GetY()-from.GetY())*(1-v)));

	element->SetValueValue(prop, (nb::System::Point)point);
}
