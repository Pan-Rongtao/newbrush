#include "gui/Ellipse.h"

using namespace nb::core;
using namespace nb::gui;
Ellipse::Ellipse()
{
}

Ellipse::~Ellipse()
{
}

Size Ellipse::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Ellipse::arrangeOverride(const Size & finalSize)
{
	return Size();
}
