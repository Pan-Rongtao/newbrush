#include "newbrush/media/Brush.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Brush::Brush()
{
}

DependencyPropertyPtr Brush::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
	return dp;
}
