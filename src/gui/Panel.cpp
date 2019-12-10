#include "gui/Panel.h"
#include "gles/Context.h"

using namespace nb;
using namespace nb::gui;

Panel::Panel()
	: Background([&](shared_ptr<Brush> v) {set(BackgroundProperty(), v); }, [&]()->shared_ptr<Brush>& {return get<shared_ptr<Brush>>(BackgroundProperty()); })
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
	static auto dp = DependencyProperty::registerDependency<Panel, shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

void Panel::onRender(std::shared_ptr<Context> drawContext)
{
	for (auto child : m_children)
	{
		child->onRender(drawContext);
	}
}
