#include "gui/Image.h"
#include "gles/Context.h"
#include "gles/RenderObject.h"
#include "gles/Model.h"
#include "gles/Material.h"
#include "gles/Quadrangle.h"
#include "gles/Program.h"
#include "gles/Texture2D.h"
#include "gles/Storage.h"
#include "gui/ImageSource.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

Image::Image()
	: Source([&](shared_ptr<ImageSource> v) {set(SourceProperty(), v); }, [&]() {return get<shared_ptr<ImageSource>>(SourceProperty()); })
	, Stretch([&](StretchE v) {set(StretchProperty(), v); }, [&]() {return get<StretchE>(StretchProperty()); })
{
	Renderer()->setMaterial(std::make_shared<gl::Material>(Programs::primitive()));
	PropertyChanged += [&](const PropertyChangedArgs &arg)
	{
		if (arg.dp == SourceProperty())
		{
			Renderer()->material()->textures().push_back(std::make_shared<Texture2D>(*Source()->Bm()));
		}
		else if (arg.dp == StretchProperty())
		{
			set(StretchProperty(), any_cast<StretchE>(arg.value));
		}
	};

}

void Image::onRender(std::shared_ptr<nb::gl::Context> drawContext)
{
	auto offset = worldOffset();
	Rect rc(offset.x(), offset.y(), ActualSize());//UIElement未做裁剪，所以render区域可能会超出范围
	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
	drawContext->queue(Renderer());
}

DependencyProperty Image::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, shared_ptr<ImageSource>>("Source");
	return dp;
}

DependencyProperty Image::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, StretchE>("Stretch", StretchE::Uniform);
	return dp;
}

Size Image::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	return Size(std::max<float>(availableSize.width(), (float)Source()->Bm()->width()), std::max<float>(availableSize.height(), (float)Source()->Bm()->height()));
}

Size Image::arrangeOverride(const Size & finalSize)
{
	switch (Stretch())
	{
	case StretchE::Origion:
	{
		return Size((float)Source()->Bm()->width(), (float)Source()->Bm()->height());
	}
	case StretchE::Fill:
	{
		return m_availableSize;
	}
	case StretchE::Uniform:
	{
		Size sz;
		auto pixelRatio = Source()->width() / Source()->heigth();
		auto containerRatio = m_availableSize.width() / m_availableSize.height();
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
			sz.reset(m_availableSize.width(), m_availableSize.width() / pixelRatio);
		}
		else
		{
			sz.reset(m_availableSize.height() * pixelRatio, m_availableSize.height());
		}
		return sz;
	}
	default:
		return Size();
	}
}
