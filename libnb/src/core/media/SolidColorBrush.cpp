#include "newbrush/core/media/SolidColorBrush.h"

using namespace nb;

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(Color())
{
}

SolidColorBrush::SolidColorBrush(const Color &color)
{
	setValue(ColorProperty(), color);
}

DependencyPropertyPtr SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<SolidColorBrush, Color>("Color", Color());
	return dp;
}
