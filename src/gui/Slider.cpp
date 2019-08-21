#include "gui/Slider.h"

using namespace nb;
using namespace nb::gui;

Slider::Slider()
	: Delay(nullptr, nullptr)
	, Interval(nullptr, nullptr)
	, Orientation(nullptr, nullptr)
	, IsDirectionReversed(nullptr, nullptr)
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
