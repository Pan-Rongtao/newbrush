#include "gui/StackPanel.h"

using namespace nb::core;
using namespace nb::gui;

StackPanel::StackPanel()
{
}

StackPanel::~StackPanel()
{
}

Size StackPanel::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size StackPanel::arrangeOverride(const Size & finalSize) const
{
	return Size();
}
