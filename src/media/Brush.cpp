#include "media/Brush.h"

using namespace nb;

Brush::Brush()
	: Opacity([&](float v) { set(OpacityProperty(), v); }, [&]()->float & {return get<float>(OpacityProperty()); })
{
}

DependencyProperty Brush::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
	return dp;
}
