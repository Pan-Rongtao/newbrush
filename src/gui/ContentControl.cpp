#include "gui/ContentControl.h"

using namespace nb::gui;
using namespace nb::core;

ContentControl::ContentControl()
{
}

ContentControl::~ContentControl()
{
}

Size nb::gui::ContentControl::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size nb::gui::ContentControl::arrangeOverride(const Size & finalSize) const
{
	return Size();
}
