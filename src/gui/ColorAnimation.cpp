#include "gui/ColorAnimation.h"
#include "gui/Storyboard.h"
#include "gui/UIElement.h"
#include "system/System.h"

using namespace nb::Media;
using namespace nb::System;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(ColorAnimation, AnimationTimeline, NULL, NULL);

NB_OBJECT_PROPERTY_IMPLEMENT_EX(ColorAnimation, From, nb::System::Color, NULL);
NB_OBJECT_PROPERTY_IMPLEMENT_EX(ColorAnimation, To, nb::System::Color, NULL);


ColorAnimation::ColorAnimation(void)
{
	From() = nb::System::Color(0, 0, 0);
	To() = nb::System::Color(0, 0, 0);
}

ColorAnimation::~ColorAnimation(void)
{
}

void ColorAnimation::AnimateTo(int frame)
{
}

void ColorAnimation::OnFrameChanged(const nb::System::TimeSpan &frame)
{
	nb::Gui::UIElement *element = Storyboard::GetTarget(this);
	if(element == NULL) return;

	DependencyProperty *prop = Storyboard::GetTargetProperty(this);
	if(prop == NULL) return;

	float v = GetFrameValue(frame);

	nb::System::Color from = (nb::System::Color)From();
	nb::System::Color to = (nb::System::Color)To();
	nb::System::Color newColor;

	newColor.SetRgb((int)nb::System::Bound(0.0f, 255.0f, from.GetRed()+(to.GetRed()-from.GetRed())*v),
					(int)nb::System::Bound(0.0f, 255.0f, from.GetGreen()+(to.GetGreen()-from.GetGreen())*v),
					(int)nb::System::Bound(0.0f, 255.0f, from.GetBlue()+(to.GetBlue()-from.GetBlue())*v));

	element->SetValueValue(prop, (nb::System::Color)newColor);
}
