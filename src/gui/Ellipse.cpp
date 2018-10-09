#include "gui/Ellipse.h"

using namespace nb::core;
using namespace nb::gui;
Ellipse::Ellipse()
{
}

Ellipse::~Ellipse()
{
}

Size Ellipse::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size Ellipse::arrangeOverride(const Size & finalSize) const
{
	return Size();
}
