#include "gui/ImageButton.h"

using namespace nb::core;

nb::gui::ImageButton::ImageButton()
{
}

nb::gui::ImageButton::~ImageButton()
{
}

Size nb::gui::ImageButton::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size nb::gui::ImageButton::arrangeOverride(const Size & finalSize) const
{
	return Size();
}
