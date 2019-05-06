#include "gui/Image.h"
#include "gles/Context.h"
#include "gles/RenderObject.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Quadrangle.h"
#include "gles/Programs.h"
#include "gles/Texture2D.h"
#include "gles/Storage.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

Image::Image()
	: Source(nullptr)
	, Stretch(Origion)
{
	Source.notify(std::bind(&Image::onSourceChanged, this, std::placeholders::_1, std::placeholders::_2));
	Stretch.notify(std::bind(&Image::onStretchChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void Image::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(Vec2(Offset().x(), Offset().y() + RenderSize().height()), Vec2(Offset().x() + RenderSize().width(), 
		Offset().y() + RenderSize().height()), Vec2(Offset().x() + RenderSize().width(), Offset().y()), Vec2(Offset().x(), Offset().y())));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::PrimitiveProgram::instance()));
	drawContext->queue(Renderer());
//	Renderer()->storage()->insert("unif_colorMode", 1);
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>("e:/Pics/5.jpg"));
}

Size Image::measureOverride(const Size & availableSize)
{
	if (Source())
		return Size(Source()->Width, Source()->Height);
	else
		return Size();
}

Size Image::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void Image::onSourceChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{
}

void Image::onStretchChanged(const nb::gui::Stretch &_old, const nb::gui::Stretch &_new)
{
	
}