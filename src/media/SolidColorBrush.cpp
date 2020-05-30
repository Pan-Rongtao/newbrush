#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(nb::Color())
{
}

SolidColorBrush::SolidColorBrush(const nb::Color &color)
{
	setValue(ColorProperty(), color);
}

DependencyPropertyPtr SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color", nb::Color());
	return dp;
}
