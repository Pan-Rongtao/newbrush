#include "gui/Page.h"

using namespace nb::core;
using namespace nb::gui;

Page::Page()
{
}

Page::~Page(void)
{
}

Size Page::measureOverride(const Size & availableSize)
{
	return Size();
}

Size Page::arrangeOverride(const Size & finalSize)
{
	return Size();
}
