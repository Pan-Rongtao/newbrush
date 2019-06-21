#include "gui/Image.h"
#include "gles/Context.h"
#include "gles/RenderObject.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Quadrangle.h"
#include "gles/Program.h"
#include "gles/Texture2D.h"
#include "gles/Storage.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

Image::Image()
	: Source(nullptr)
	, Stretch(StretchE::Uniform)
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(Programs::primitive()));
	
	Source.notify([&](const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new) {
		Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(*Source()->Bm()));
	});
	Stretch.notify([&](const StretchE &_old, const StretchE &_new) {

	});
}

void Image::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	Rect rc(Offset().x(), Offset().y(), ActualSize());//UIElement未做裁剪，所以render区域可能会超出范围
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()), 
		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
	drawContext->queue(Renderer());
}

Size Image::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	return Size(std::max(availableSize.width(), (float)Source()->Bm()->width()), 
		std::max(availableSize.height(), (float)Source()->Bm()->height()));
}

Size Image::arrangeOverride(const Size & finalSize)
{
	switch (Stretch)
	{
	case StretchE::Origion:
	{
		return{ (float)Source()->Bm()->width(), (float)Source()->Bm()->height() };
	}
	case StretchE::Fill:
	{
		return m_availableSize;
	}
	case StretchE::Uniform:
	{
		Size sz;
		float pixelRatio = (float)(Source()->width() / Source()->heigth());
		float containerRatio = m_availableSize.width() / m_availableSize.height();
		if (pixelRatio < containerRatio)
		{
			sz.reset(m_availableSize.height() * pixelRatio, m_availableSize.height());
		}
		else
		{
			sz.reset(m_availableSize.width(), m_availableSize.width() / pixelRatio);
		}
		return sz;
	}
	case StretchE::UniformToFill:
	{
		Size sz;
		auto pixelRatio = Source()->width() / Source()->heigth();
		auto containerRatio = m_availableSize.width() / m_availableSize.height();
		if (pixelRatio < containerRatio)
		{
			sz.reset((float)m_availableSize.width(), (float)(m_availableSize.width() / pixelRatio));
		}
		else
		{
			sz.reset((float)(m_availableSize.height() * pixelRatio), (float)m_availableSize.height());
		}
		return sz;
	}
	default:
		return Size();
	}
}
