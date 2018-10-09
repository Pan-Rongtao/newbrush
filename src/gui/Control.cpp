#include "gui/Control.h"

using namespace nb::core;
using namespace nb::gui;

Control::Control()
{
}

Control::~Control()
{
}

Size nb::gui::Control::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size nb::gui::Control::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}
