#include "gui/Panel.h"
#include "gles/Quadrangle.h"
#include "gles/Material.h"
#include "gles/Program.h"
#include "gles/Context.h"

using namespace nb::core;
using namespace nb::gui;

Panel::Panel()
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

void Panel::init()
{
}

void Panel::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	for (auto child : Children())
	{
		child->onRender(drawContext);
	}
}
