#include "newbrush/gui/shapes/Line.h"

using namespace nb;

DependencyPropertyPtr Line::X1Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("X1", 0.0f);
	return dp;
}

DependencyPropertyPtr Line::X2Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("X2", 0.0f);
	return dp;
}

DependencyPropertyPtr Line::Y1Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("Y1", 0.0f);
	return dp;
}

DependencyPropertyPtr Line::Y2Property()
{
	static auto dp = DependencyProperty::registerDependency<Line, float>("Y2", 0.0f);
	return dp;
}

void Line::onRender(DrawingContextPtr dc)
{
	auto x1 = getValue<float>(X1Property());
	auto x2 = getValue<float>(X2Property());
	auto y1 = getValue<float>(Y1Property());
	auto y2 = getValue<float>(Y2Property());

	dc->drawLine(getPen(), Point(x1, y1), Point(x2, y2));
}

Size Line::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Line::arrangeOverride(const Size & finalSize)
{
	auto x1 = getValue<float>(X1Property());
	auto x2 = getValue<float>(X2Property());
	auto y1 = getValue<float>(Y1Property());
	auto y2 = getValue<float>(Y2Property());
	return Size(std::abs(x2 - x1), std::abs(y2 - y1));
}
