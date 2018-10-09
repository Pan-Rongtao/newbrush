#include "gui/Panel.h"

using namespace nb::core;
using namespace nb::gui;

Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::setZIndex(std::shared_ptr<UIElement> element, int index)
{
}

int Panel::getZIndex(std::shared_ptr<UIElement> element)
{
	return 0;
}

Size Panel::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size Panel::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}
