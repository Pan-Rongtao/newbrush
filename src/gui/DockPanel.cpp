#include "newbrush/gui/DockPanel.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

DockPanel::DockPanel()
{
}

void DockPanel::setDock(UIElementPtr element, DockE dock)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	element->setValue(DockProperty(), dock);
}

DockE DockPanel::getDock(UIElementPtr element)
{
	if (!element) { nbThrowException(std::invalid_argument, "element is null"); }
	return element->getValue(DockProperty()).get_value<DockE>();
}

DependencyPropertyPtr DockPanel::DockProperty()
{
	static auto dp = DependencyProperty::registerDependency<DockPanel, DockE>("Dock", DockE::Left, nullptr, nullptr, nullptr,
		PropertyCategory::Layout(), "子元素在父DockPanel中的位置", 3);
	return dp;
}

DependencyPropertyPtr DockPanel::LastChildFillProperty()
{
	static auto dp = DependencyProperty::registerDependency<DockPanel, bool>("LastChildFill", false, nullptr, nullptr, nullptr,
		PropertyCategory::Layout(), "最后一个子元素是否拉伸以填充剩余的可用空间", 5);
	return dp;
}

//当测量一个子元素时，遵循这样的原则：如果该子元素已经是最后一个元素，它的分配将受到LastChildFill的影响；
//如果LastChildFill为true，将所有的remainSize供给它测量；否则走另一个分支：
//当Dock是在左右停靠，它的measure宽为它Width（未指定时为0），高为它的Height（未指定时为remainSize.height)
//每一个子元素measure后，将留下remainSize，供余下的子元素测量，一直到所有的子元素测量完成。
Size DockPanel::measureOverride(const Size & availableSize)
{
	Size remainSize = availableSize;
	for (int i = 0; i != m_children.count(); ++i)
	{
		auto const &child = m_children.childAt(i);
		Size childMeasureSize;
		auto lastChildFill = getValue<bool>(LastChildFillProperty());
		if (lastChildFill && (i == m_children.count() - 1))
		{
			childMeasureSize = remainSize;
		}
		else
		{
			auto dock = getDock(child);
			if (dock == DockE::Left || dock == DockE::Right)
			{
				auto childWidth = child->getValue<float>(WidthProperty());
				auto width = std::isnan(childWidth) ? 0.0f : childWidth;
				auto height = remainSize.height();
				childMeasureSize.reset(width, height);
				remainSize.width() -= childMeasureSize.width();
			}
			else
			{
				auto width = remainSize.width();
				auto childHeight = child->getValue<float>(HeightProperty());
				auto height = std::isnan(childHeight) ? 0.0f : childHeight;
				childMeasureSize.reset(width, height);
				remainSize.height() -= childMeasureSize.height();
			}
		}
		child->measure(childMeasureSize);
	}
	return availableSize;
}

Size DockPanel::arrangeOverride(const Size & finalSize)
{
	Rect remainRect(0.0f, 0.0f, finalSize);
	for (int i = 0; i != m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		auto childDesiredSize = child->desiredSize();
		Rect childArrageRect;
		auto lastChildFill = getValue<bool>(LastChildFillProperty());
		if (lastChildFill && (i == m_children.count() - 1))
		{
			childArrageRect = remainRect;
		}
		else
		{
			auto dock = getDock(child);
			auto w = 0.0f, h = 0.0f;
			switch (dock)
			{
			case DockE::Left:
			{
				auto childWidth = child->getValue<float>(WidthProperty());
				w = std::isnan(childWidth) ? remainRect.width() : childDesiredSize.width();
				h = remainRect.height();
				childArrageRect = Rect(remainRect.leftTop(), w, h);
				remainRect.moveOffsetLeft(childDesiredSize.width());
				break;
			}
			case DockE::Right:
			{
				auto childWidth = child->getValue<float>(WidthProperty());
				w = std::isnan(childWidth) ? remainRect.width() : childDesiredSize.width();
				h = remainRect.height();
				childArrageRect = Rect(remainRect.right() - childDesiredSize.width(), remainRect.y(), w, h);
				remainRect.moveOffsetRight(-childDesiredSize.width());
				break;
			}
			case DockE::Top:
			{
				auto childHeight = child->getValue<float>(HeightProperty());
				w = remainRect.width();
				h = std::isnan(childHeight) ? remainRect.height() : childDesiredSize.height();
				childArrageRect = Rect(remainRect.leftTop(), w, h);
				remainRect.moveOffsetTop(childDesiredSize.height());
				break;
			}
			case DockE::Bottom:
			{
				auto childHeight = child->getValue<float>(HeightProperty());
				w = remainRect.width();
				h = std::isnan(childHeight) ? remainRect.height() : childDesiredSize.height();
				childArrageRect = Rect(remainRect.x(), remainRect.bottom() - childDesiredSize.height(), w, h);
				remainRect.moveOffsetBottom(-childDesiredSize.height());
				break;
			}
			default:
				break;
			}
		}
		child->arrage(childArrageRect);
	}
	return finalSize;
}
