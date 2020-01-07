#include "media/SolidColorBrush.h"

using namespace nb;

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(nb::Color())
{
}

SolidColorBrush::SolidColorBrush(const nb::Color &color)
{
	set(ColorProperty(), color);
}

DependencyProperty SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color", nb::Color());
	return dp;
}
