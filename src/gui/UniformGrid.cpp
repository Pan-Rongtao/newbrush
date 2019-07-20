#include "gui/UniformGrid.h"

using namespace nb::core;
using namespace nb::gui;

Size UniformGrid::measureOverride(const nb::core::Size & availableSize)
{
	for (auto child : Children())
	{
		auto w = availableSize.width() / Columns;
		auto h = availableSize.height() / Rows;
		child->measure(Size(w, h));
	}
	return availableSize;
}

Size UniformGrid::arrangeOverride(const nb::core::Size & finalSize)
{
	for (auto i = 0u; i != Children().size(); ++i)
	{
		auto child = Children()[i];
		auto row = (i + FirstColumn()) % Columns();
		auto col = (i + +FirstColumn()) / Columns();
		auto x = row * child->DesiredSize().width();
		auto y = col * child->DesiredSize().height();
		child->arrage(Rect(x, y, child->DesiredSize()));
	}
	return finalSize;
}
