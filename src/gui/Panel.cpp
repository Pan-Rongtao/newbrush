#include "gui/Panel.h"
#include "gles/Quadrangle.h"
#include "gles/Material.h"
#include "gles/Programs.h"
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
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(Vec2(0.0, 100), Vec2(100, 100), Vec2(100, 0.0), Vec2(0.0, 0.0)));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::PrimitiveProgram::instance()));
}

Size Panel::measureOverride(const Size & availableSize)
{
	return UIElement::measureOverride(availableSize);
}

Size Panel::arrangeOverride(const Size & finalSize)
{
	return UIElement::arrangeOverride(finalSize);
}

void Panel::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	static int i = 0;
	if (i++ == 0)
		drawContext->queue(Renderer());
	for (auto child : Children())
	{
		child->onRender(drawContext);
	}
}
