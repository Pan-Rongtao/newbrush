#include "newbrush/gui/StackPanel.h"
#include "newbrush/core/MetaObject.h"

using namespace nb;

StackPanel::StackPanel()
{
}

DependencyProperty StackPanel::OrientationProperty()
{
	static auto dp = DependencyProperty::registerDependency<StackPanel, OrientationE>("Orientation", OrientationE::Horizontal, nullptr, nullptr, nullptr,
		PropertyCategory::Layout(), "子内容是水平排列还是垂直排列", 3);
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
		auto childWidth = child->getValue<float>(WidthProperty());
		auto childHeight = child->getValue<float>(HeightProperty());
		childMeasureSize.width() = std::isnan(childWidth) ? 0.0f : childWidth;
		childMeasureSize.height() = std::isnan(childHeight) ? 0.0f : childHeight;
		child->measure(childMeasureSize);
		auto sz = child->desiredSize();
		bool b = false;
	}
	return availableSize;
}

Size StackPanel::arrangeOverride(const Size & finalSize)
{
	Size ret;
	auto x = 0.0f, y = 0.0f;
	auto selfDesiredSize = desiredSize();
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto childDesiredSize = child->desiredSize();
		auto orientation = getValue<OrientationE>(OrientationProperty());
		if (orientation == OrientationE::Horizontal)
		{
			child->arrage(Rect(x, y, childDesiredSize.width(), selfDesiredSize.height()));
			x += childDesiredSize.width();
			ret.width() += childDesiredSize.width();
			ret.height() = std::max(ret.height(), childDesiredSize.height());
		}
		else
		{
			child->arrage(Rect(x, y, selfDesiredSize.width(), childDesiredSize.height()));
			y += childDesiredSize.height();
			ret.width() = std::max(ret.width(), childDesiredSize.width());
			ret.height() += childDesiredSize.height();
		}
	}
	return finalSize;
}

std::shared_ptr<MetaObject> StackPanel::getMetaObject()
{
	auto meta = MetaObject::get<StackPanel, Panel>("面板", "StackPanel", "栈式面板。可以将包含元素排成一条直线，当添加或移除包含元素时，后面的元素会自动向下或向上移动。", [] {return std::make_shared<StackPanel>(); });
	meta->addProperty(OrientationProperty(), "布局", "子内容是水平排列还是垂直排列", PropertyDescriptor::Enum, "Horizontal|Vertical");
	return meta;
}
