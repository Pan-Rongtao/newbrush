#include "gui/Slider.h"

using namespace nb::core;
using namespace nb::gui;

Slider::Slider()
{
}

Slider::~Slider()
{
}

Size nb::gui::Slider::measureOverride(const Size & availableSize)
{
	return Size();
}

Size nb::gui::Slider::arrangeOverride(const Size & finalSize)
{
	return Size();
}
