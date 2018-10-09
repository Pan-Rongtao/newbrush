#include "gui/Rectangle.h"

using namespace nb::core;
using namespace nb::gui;

Rectangle::Rectangle()
{

}

Rectangle::~Rectangle()
{
}

Size nb::gui::Rectangle::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size nb::gui::Rectangle::arrangeOverride(const Size & finalSize) const
{
	return Size();
}
