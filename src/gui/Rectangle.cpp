#include "gui/Rectangle.h"
#include "gles/Quadrangle.h"
#include "gles/Material.h"
#include "gles/Programs.h"
#include "gles/Context.h"

using namespace nb::core;
using namespace nb::gui;

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Renderer()->setModel(std::make_shared<gl::Quadrangle>());
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::PrimitiveProgram::instance()));
	drawContext->queue(Renderer());
}

Size Rectangle::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Rectangle::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}
