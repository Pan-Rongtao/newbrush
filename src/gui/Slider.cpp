#include "gui/Slider.h"

using namespace nb;
using namespace nb::gui;

Slider::Slider()
{
}

Size Slider::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Slider::arrangeOverride(const Size & finalSize)
{
	return Size();
}
