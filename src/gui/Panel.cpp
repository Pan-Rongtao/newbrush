#include "gui/Panel.h"
#include "gles/Quadrangle.h"
#include "gles/Material.h"
#include "gles/Programs.h"

using namespace nb::core;
using namespace nb::gui;

Panel::Panel()
{
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(Vec2(0.0, 0.0), Vec2(100.0, 0.0), Vec2(0.0, 100.0), Vec2(100.0, 100.0)));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::PrimitiveProgram::instance()));
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

Size Panel::measureOverride(const Size & availableSize) const
{
	return Size();
}

Size Panel::arrangeOverride(const Size & finalSize) const
{
	return finalSize;
}

void Panel::renderOverride()
{
	Renderer()->draw();
	for (auto child : Children())
	{
		child->renderOverride();
	}
}
