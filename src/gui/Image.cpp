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
	, Stretch(Uniform)
{
	Source.notify(std::bind(&Image::onSourceChanged, this, std::placeholders::_1, std::placeholders::_2));
	Stretch.notify(std::bind(&Image::onStretchChanged, this, std::placeholders::_1, std::placeholders::_2));
}

void Image::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc;
	switch (Stretch)
	{
	case Stretch::Origion:	rc.setSize((float)Source()->width(), (float)Source()->width());	break;
	case Stretch::Fill:		rc.setSize(ActualSize);											break;
	case Stretch::Uniform:	
	{
		float pixelRatio = Source()->width() / Source()->heigth();
		float containerRatio = ActualSize().width() / ActualSize().height();
		if (pixelRatio < containerRatio)
		{
			rc.setSize(ActualSize().height() * pixelRatio, ActualSize().height());
			rc.moveHorizontal(rc.left() + (ActualSize().width() - rc.width()) / 2);
		}
		else
		{
			rc.setSize(ActualSize().width(), ActualSize().width() / pixelRatio);
			rc.moveVertical(rc.top() + (ActualSize().height() - rc.height()) / 2);
		}
	}
	break;
	case Stretch::UniformToFill:
	{
		auto pixelRatio = Source()->width() / Source()->heigth();
		auto containerRatio = ActualSize().width() / ActualSize().height();
		if (pixelRatio < containerRatio)
		{
			rc.setSize(ActualSize().width(), ActualSize().width() / pixelRatio);
		}
		else
		{
			rc.setSize(ActualSize().height() * pixelRatio, ActualSize().height());
		}
	}
	break;
	default:
		break;
	}
	rc.move(Offset().x(), Offset().y());
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(Vec2(rc.left(), rc.bottom()), 
		Vec2(rc.right(), rc.bottom()), Vec2(rc.right(), rc.top()), Vec2(rc.left(), rc.top())));
	Renderer()->setMaterial(std::make_shared<gl::Material>(gl::PrimitiveProgram::instance()));
	drawContext->queue(Renderer());
	Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(*Source()->Bm()));
}

Size Image::measureOverride(const Size & availableSize)
{
	if (Source())
		return Size(Source()->width(), Source()->heigth());
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