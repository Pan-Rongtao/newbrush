#include "media/SolidColorBrush.h"

using namespace nb;

SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(nb::Color())
{
}

SolidColorBrush::SolidColorBrush(const nb::Color &color)
	: Color([&](nb::Color v) { set(ColorProperty(), v); }, [&]()->nb::Color {return get<nb::Color>(ColorProperty()); })
{
	Color = color;
}

DependencyProperty SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color", nb::Color());
	return dp;
}
