#include "newbrush/gui/Panel.h"
#include "newbrush/media/Brush.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/core/MetaObject.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

Panel::Panel()
	: m_children(this)
{
}

void Panel::setZIndex(std::shared_ptr<UIElement> element, int index)
{
}

int Panel::getZIndex(std::shared_ptr<UIElement> element)
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
	static auto dp = DependencyProperty::registerDependency<Panel, std::shared_ptr<Brush>>("Background", nullptr, nullptr, nullptr, nullptr,
		PropertyCategory::Brush(), "元素背景的画笔", 1);
	return dp;
}

UIElementCollection & Panel::children()
{
	return m_children;
}

void Panel::onRender(Viewport2D & drawContext)
{
	for (auto i = 0u; i < m_children.count(); ++i)
	{
		auto child = m_children.childAt(i);
		child->onRender(drawContext);
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

std::shared_ptr<MetaObject> Panel::getMetaObject()
{
	auto meta = MetaObject::get<Panel, UIElement>("面板", "Panel", "面板基类。表示按需要根据规则对子元素进行测量和排列的元素类型。", [] {return nullptr; });
	meta->addProperty(BackgroundProperty(), "画笔", "元素背景的画笔", PropertyDescriptor::Brush);
	return meta;
}
