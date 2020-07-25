#include "newbrush/gui/panels/Panel.h"
#include "newbrush/core/media/Brush.h"

using namespace nb;

Panel::Panel()
	: m_children(this)
{
}

void Panel::setZIndex(UIElementPtr element, int index)
{
}

int Panel::getZIndex(UIElementPtr element)
{
	return 0;
}

Panel::Panel(const Panel & other)
	: m_children(other.m_children)
{
	m_children.changeLogicalParent(this);
}

Panel::Panel(const Panel && other)
	: m_children(std::move(other.m_children))
{
	m_children.changeLogicalParent(this);
}

Panel & Panel::operator=(const Panel & other)
{
	m_children = other.m_children;
	m_children.changeLogicalParent(this);
	return *this;
}

Panel & Panel::operator=(const Panel && other)
{
	m_children = std::move(other.m_children);
	m_children.changeLogicalParent(this);
	return *this;
}

DependencyPropertyPtr Panel::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Panel, BrushPtr>("Background", nullptr, nullptr, nullptr, nullptr);
	return dp;
}

UIElementCollection & Panel::children()
{
	return m_children;
}

void Panel::onRender(DrawingContextPtr dc)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		child->onRender(dc);
	}
}

uint32_t Panel::childrenCount() const
{
	return m_children.count();
}

UIElement *Panel::getChild(uint32_t index)
{
	return m_children.childAt(index).get();
}
