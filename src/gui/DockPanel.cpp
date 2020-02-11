#include "newbrush/gui/DockPanel.h"

using namespace nb;
using namespace nb::gui;

DockPanel::DockPanel()
{
}

void DockPanel::setDock(std::shared_ptr<UIElement> element, DockE dock)
{
	if (m_children.contains(element))
		DependencyProperty::registerAttached(element, AttachedPropertyDock, dock);
}

DockE DockPanel::getDock(std::shared_ptr<UIElement> element)
{
	auto v = DependencyProperty::findAttached(element, AttachedPropertyDock);
	return v.isEmpty() ? DockE::Left : v.extract<DockE>();
}

DependencyProperty DockPanel::LastChildFillProperty()
{
	static auto dp = DependencyProperty::registerDependency<DockPanel, bool>("LastChildFill", false);
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
		auto lastChildFill = get<bool>(LastChildFillProperty());
		if (lastChildFill && (i == m_children.count() - 1))
		{
			childMeasureSize = remainSize;
		}
		else
		{
			auto dock = getDock(child);
			if (dock == DockE::Left || dock == DockE::Right)
			{
				auto childWidth = child->get<float>(WidthProperty());
				auto width = std::isnan(childWidth) ? 0.0f : childWidth;
				auto height = remainSize.height();
				childMeasureSize.reset(width, height);
				remainSize.width() -= childMeasureSize.width();
			}
			else
			{
				auto width = remainSize.width();
				auto childHeight = child->get<float>(HeightProperty());
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
		auto childDesiredSize = child->get<Size>(DesiredSizeProperty());
		Rect childArrageRect;
		auto lastChildFill = get<bool>(LastChildFillProperty());
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
				auto childWidth = child->get<float>(WidthProperty());
				w = std::isnan(childWidth) ? remainRect.width() : childDesiredSize.width();
				h = remainRect.height();
				childArrageRect = Rect(remainRect.leftTop(), w, h);
				remainRect.moveOffsetLeft(childDesiredSize.width());
				break;
			}
			case DockE::Right:
			{
				auto childWidth = child->get<float>(WidthProperty());
				w = std::isnan(childWidth) ? remainRect.width() : childDesiredSize.width();
				h = remainRect.height();
				childArrageRect = Rect(remainRect.right() - childDesiredSize.width(), remainRect.y(), w, h);
				remainRect.moveOffsetRight(-childDesiredSize.width());
				break;
			}
			case DockE::Top:
			{
				auto childHeight = child->get<float>(HeightProperty());
				w = remainRect.width();
				h = std::isnan(childHeight) ? remainRect.height() : childDesiredSize.height();
				childArrageRect = Rect(remainRect.leftTop(), w, h);
				remainRect.moveOffsetTop(childDesiredSize.height());
				break;
			}
			case DockE::Bottom:
			{
				auto childHeight = child->get<float>(HeightProperty());
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
