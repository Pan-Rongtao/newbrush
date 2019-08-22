#include "gui/StackPanel.h"

using namespace nb;
using namespace nb::gui;

StackPanel::StackPanel()
	: Orientation([&](OrientationE v) {set(OrientationProperty(), v); }, [&]() {return get<OrientationE>(OrientationProperty()); })
	, ExtentWidth([&]() {return get<float>(ExtentWidthProperty()); })
	, ExtentHeight([&]() {return get<float>(ExtentHeightProperty()); })
	, HorizontalOffset([&]() {return get<float>(HorizontalOffsetProperty()); })
	, VerticalOffset([&]() {return get<float>(VerticalOffsetProperty()); })
	, ViewportWidth([&]() {return get<float>(ViewportWidthProperty()); })
	, ViewportHeight([&]() {return get<float>(ViewportHeightProperty()); })
{
}

DependencyProperty StackPanel::OrientationProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, OrientationE>("Orientation", OrientationE::Horizontal);
	return dp;
}

DependencyProperty StackPanel::ExtentWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentWidth");
	return dp;
}

DependencyProperty StackPanel::ExtentHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentHeight");
	return dp;
}

DependencyProperty StackPanel::HorizontalOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("HorizontalOffset");
	return dp;
}

DependencyProperty StackPanel::VerticalOffsetProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("VerticalOffset");
	return dp;
}

DependencyProperty StackPanel::ViewportWidthProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportWidth");
	return dp;
}

DependencyProperty StackPanel::ViewportHeightProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportHeight");
	return dp;
}

//如果是Horizontal，水平方向是无限的，垂直方向availableSize.height
//否则如果是Vertical，垂直方向是无限的，水平方向取availableSize.width
Size StackPanel::measureOverride(const Size & availableSize)
{
	Size childMeasureSize;
	for (auto const &child : m_children)
	{
		childMeasureSize.width() = std::isnan(child->Width()) ? 0.0f : child->Width();
		childMeasureSize.height() = std::isnan(child->Height()) ? 0.0f : child->Height();
		child->measure(childMeasureSize);
		auto sz = child->DesiredSize();
		bool b = false;
	}
	return availableSize;
}

Size StackPanel::arrangeOverride(const Size & finalSize)
{
	Size ret;
	auto x = 0.0f, y = 0.0f;
	for (auto child : m_children)
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
	return finalSize;
}
