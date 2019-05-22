#include "gui/PropertyAnimation.h"
#include "gui/Storyboard.h"

using namespace nb::core;
using namespace nb::gui;

ColorAnimation::ColorAnimation()
	: Easing(std::make_shared<LinearEase>())
{
}

void ColorAnimation::progressing(double progress)
{
	if (!TargetProperty)	return;

	auto ft = Easing()->easeInCore(progress);
	int r = 0, g = 0, b = 0;
	r = (int)((int)From().red() + ft * ((int)To().red() - (int)From().red()));
	g = (int)((int)From().green() + ft * ((int)To().green() - (int)From().green()));
	b = (int)((int)From().blue() + ft * ((int)To().blue() - (int)From().blue()));
	*TargetProperty = Color(r, g, b);
}
