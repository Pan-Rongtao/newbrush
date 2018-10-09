#include "gui/WrapPanel.h"

using namespace nb::core;
using namespace nb::gui;

WrapPanel::WrapPanel()
{
}

WrapPanel::~WrapPanel()
{
}

Size WrapPanel::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size WrapPanel::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}
