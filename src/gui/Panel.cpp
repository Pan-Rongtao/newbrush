#include "gui/Panel.h"
#include "gles/Quadrangle.h"
#include "gles/Material.h"
#include "gles/Program.h"
#include "gles/Context.h"

using namespace nb;
using namespace nb::gui;

Panel::Panel()
	: Background([&](shared_ptr<Brush> v) {set(BackgroundProperty(), v); }, [&]() {return get<shared_ptr<Brush>>(BackgroundProperty()); })
{
}

Panel::~Panel()
{
}

void Panel::setZIndex(std::shared_ptr<UIElement> element, int index)
{
}

int Panel::getZIndex(std::shared_ptr<UIElement> element)
{
	return 0;
}

const DependencyProperty Panel::BackgroundProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Panel, shared_ptr<Brush>>("Background", nullptr);
	return dp;
}

void Panel::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	for (auto child : m_children)
	{
		child->onRender(drawContext);
	}
}
