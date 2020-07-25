#include "newbrush/gui/shapes/Ellipse.h"

using namespace nb;

Ellipse::Ellipse()
{
}

void Ellipse::onRender(DrawingContextPtr dc)
{
	auto offset = worldOffset();
	auto const &actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);

	auto brush = getValue<BrushPtr>(FillProperty());
	dc->drawEllipse(brush, getPen(), rc.center(), rc.width() * 0.5f, rc.height() * 0.5f);
}

Size Ellipse::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Ellipse::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}
