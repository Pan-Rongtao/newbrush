#include "gui/Shape.h"

using namespace nb::core;
using namespace nb::gui;

Shape::Shape()
{
}

Shape::~Shape()
{
}

Size Shape::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Shape::arrangeOverride(const Size & finalSize)
{
	return Size();
}
