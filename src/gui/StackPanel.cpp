#include "gui/StackPanel.h"

using namespace nb::core;
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

const DependencyProperty StackPanel::OrientationProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, OrientationE>("Orientation", OrientationE::Horizontal);
	return dp;
}

const DependencyProperty StackPanel::ExtentWidthProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentWidth", 0.0f);
	return dp;
}

const DependencyProperty StackPanel::ExtentHeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("ExtentHeight", 0.0f);
	return dp;
}

const DependencyProperty StackPanel::HorizontalOffsetProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("HorizontalOffset", 0.0f);
	return dp;
}

const DependencyProperty StackPanel::VerticalOffsetProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("VerticalOffset", 0.0f);
	return dp;
}

const DependencyProperty StackPanel::ViewportWidthProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportWidth", 0.0f);
	return dp;
}

const DependencyProperty StackPanel::ViewportHeightProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<StackPanel, float>("ViewportHeight", 0.0f);
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
