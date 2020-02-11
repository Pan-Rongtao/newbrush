#include "newbrush/gui/StackPanel.h"

using namespace nb;
using namespace nb::gui;

StackPanel::StackPanel()
{
}

DependencyProperty StackPanel::OrientationProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, OrientationE>("Orientation", OrientationE::Horizontal);
	return dp;
}

DependencyProperty StackPanel::ExtentWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentWidth", 0.0);
	return dp;
}

DependencyProperty StackPanel::ExtentHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentHeight", 0.0);
	return dp;
}

DependencyProperty StackPanel::HorizontalOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("HorizontalOffset", 0.0);
	return dp;
}

DependencyProperty StackPanel::VerticalOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("VerticalOffset", 0.0);
	return dp;
}

DependencyProperty StackPanel::ViewportWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportWidth", 0.0);
	return dp;
}

DependencyProperty StackPanel::ViewportHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportHeight", 0.0);
	return dp;
}

//如果是Horizontal，水平方向是无限的，垂直方向availableSize.height
//否则如果是Vertical，垂直方向是无限的，水平方向取availableSize.width
Size StackPanel::measureOverride(const Size & availableSize)
{
	Size childMeasureSize;
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto childWidth = child->get<float>(WidthProperty());
		auto childHeight = child->get<float>(HeightProperty());
		childMeasureSize.width() = std::isnan(childWidth) ? 0.0f : childWidth;
		childMeasureSize.height() = std::isnan(childHeight) ? 0.0f : childHeight;
		child->measure(childMeasureSize);
		auto sz = child->get<Size>(DesiredSizeProperty());
		bool b = false;
	}
	return availableSize;
}

Size StackPanel::arrangeOverride(const Size & finalSize)
{
	Size ret;
	auto x = 0.0f, y = 0.0f;
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto desiredSize = child->get<Size>(DesiredSizeProperty());
		auto orientation = get<OrientationE>(OrientationProperty());
		if (orientation == OrientationE::Horizontal)
		{
			child->arrage(Rect(x, y, desiredSize.width(), desiredSize.height()));
			x += desiredSize.width();
			ret.width() += desiredSize.width();
			ret.height() = std::max(ret.height(), desiredSize.height());
		}
		else
		{
			child->arrage(Rect(x, y, desiredSize.width(), desiredSize.height()));
			y += desiredSize.height();
			ret.width() = std::max(ret.width(), desiredSize.width());
			ret.height() += desiredSize.height();
		}
	}
	return finalSize;
}
