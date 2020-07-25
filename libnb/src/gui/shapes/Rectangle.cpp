#include "newbrush/gui/shapes/Rectangle.h"

using namespace nb;

DependencyPropertyPtr Rectangle::RadiusXProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusX", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Rectangle::RadiusYProperty()
{
	static auto dp = DependencyProperty::registerDependency<Rectangle, float>("RadiusY", 0.0, nullptr, nullptr, nullptr);
	return dp;
}

void Rectangle::onRender(DrawingContextPtr dc)
{
	auto offset = worldOffset();
	auto const &actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);

	auto brush = getValue<BrushPtr>(FillProperty());
	auto radiusX = getValue<float>(RadiusXProperty());
	auto radiusY = getValue<float>(RadiusYProperty());
	dc->drawRoundedRectangle(brush, getPen(), rc, radiusX, radiusY);
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

UIElementPtr Rectangle::clone() const
{
	return std::make_shared<Rectangle>(*this);
}
