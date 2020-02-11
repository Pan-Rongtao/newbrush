#include "newbrush/media/Brush.h"

using namespace nb;

Brush::Brush()
{
}

DependencyProperty Brush::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
	return dp;
}
