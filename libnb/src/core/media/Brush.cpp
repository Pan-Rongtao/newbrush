#include "newbrush/core/media/Brush.h"

using namespace nb;

Brush::Brush()
{
}

DependencyPropertyPtr Brush::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
	return dp;
}
