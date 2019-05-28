#include "gui/StackPanel.h"

using namespace nb::core;
using namespace nb::gui;

StackPanel::StackPanel()
{
	ExtentWidth.getter([&]()->double & {return m_extentWidth; });
	ExtentHeight.getter([&]()->double & {return m_extentHeight; });
	HorizontalOffset.getter([&]()->double & {return m_horizontalOffset; });
	VerticalOffset.getter([&]()->double & {return m_verticalOffset; });
	ViewportWidth.getter([&]()->double & {return m_viewportWidth; });
	ViewportHeight.getter([&]()->double & {return m_viewportHeight; });
}

StackPanel::~StackPanel()
{
}

//如果是Horizontal，水平方向是无限的，垂直方向availableSize.height
//否则如果是Vertical，垂直方向是无限的，水平方向取availableSize.width
Size StackPanel::measureOverride(const Size & availableSize)
{
	Size ret;
	for (auto child : Children())
	{
		if (Orientation == OrientationE::Horizontal)
		{
			child->measure(Size((float)NB_DOUBLE_MAX, availableSize.height()));
			ret.width() += child->DesiredSize().width();
			ret.height() = availableSize.height();
		}
		else
		{
			child->measure(Size(availableSize.width(), (float)NB_DOUBLE_MAX));
			ret.width() = availableSize.width();
			ret.height() += child->DesiredSize().height();
		}
	}
	return ret;
}

Size StackPanel::arrangeOverride(const Size & finalSize)
{
	Size ret;
	float xOffset = 0.0f, yOffset = 0.0f;
	for (auto child : Children())
	{
		if (Orientation == OrientationE::Horizontal)
		{
			child->arrage(Rect(xOffset, yOffset, child->DesiredSize().width(), DesiredSize().height()));
			xOffset += child->DesiredSize().width();
			ret.width() += child->DesiredSize().width();
			ret.height() = std::max(ret.height(), child->DesiredSize().height());
		}
		else
		{
			child->arrage(Rect(xOffset, yOffset, DesiredSize().width(), child->DesiredSize().height()));
			yOffset += child->DesiredSize().height();
			ret.width() = std::max(ret.width(), child->DesiredSize().width()); 
			ret.height() += child->DesiredSize().height();
		}
	}
	return ret;
}
