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
	Size childMeasureSize;
	for (auto const &child : Children())
	{
		childMeasureSize.width() = (float)(child->Width != NB_DOUBLE_NAN ? child->Width : 0.0);
		childMeasureSize.height() = (float)(child->Height != NB_DOUBLE_NAN ? child->Height : 0.0);
		child->measure(childMeasureSize);
		auto sz = child->DesiredSize();
		bool b = false;
	}
	return availableSize;
}

Size StackPanel::arrangeOverride(const Size & finalSize)
{
	Size ret;
	float x = 0.0f, y = 0.0f;
	for (auto child : Children())
	{
		if (Orientation == OrientationE::Horizontal)
		{
			child->arrage(Rect(x, y, child->DesiredSize().width(), DesiredSize().height()));
			x += child->DesiredSize().width();
			ret.width() += child->DesiredSize().width();
			ret.height() = std::max(ret.height(), child->DesiredSize().height());
		}
		else
		{
			child->arrage(Rect(x, y, DesiredSize().width(), child->DesiredSize().height()));
			y += child->DesiredSize().height();
			ret.width() = std::max(ret.width(), child->DesiredSize().width()); 
			ret.height() += child->DesiredSize().height();
		}
	}
	return ret;
}
