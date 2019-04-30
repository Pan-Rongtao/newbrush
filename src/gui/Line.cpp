#include "gui/Line.h"

using namespace nb::core;
using namespace nb::gui;

Line::Line()
{
}

Line::~Line()
{
}

Size Line::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Line::arrangeOverride(const Size & finalSize)
{
	return Size();
}
