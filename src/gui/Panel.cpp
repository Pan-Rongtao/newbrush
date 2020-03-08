#include "newbrush/gui/Panel.h"
#include "newbrush/gles/Viewport2D.h"

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

DependencyProperty Panel::BackgroundProperty()
{
	static auto dp = DependencyProperty::registerDependency<Panel, std::shared_ptr<Brush>>("Background", nullptr);
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
