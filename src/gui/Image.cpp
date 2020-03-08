#include "newbrush/gui/Image.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/ImageSource.h"

using namespace nb;

Image::Image()
	: m_renderObj(std::make_shared<RenderObject>())
{
	m_renderObj->setMaterial(std::make_shared<Material>(Programs::primitive()));
}

void Image::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);//UIElement未做裁剪，所以render区域可能会超出范围
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(glm::vec2(rc.left(), rc.bottom()), glm::vec2(rc.right(), rc.bottom()),
//		glm::vec2(rc.right(), rc.top()), glm::vec2(rc.left(), rc.top())));
//	Renderer()->setModel(std::make_shared<gl::Quadrangle>(rc.width(), rc.height()));
	drawContext.queue(m_renderObj);
}

DependencyProperty Image::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, std::shared_ptr<ImageSource>>("Source", nullptr);
	return dp;
}

DependencyProperty Image::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, StretchE>("Stretch", StretchE::Uniform);
	return dp;
}

void Image::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == SourceProperty())
	{
		auto source = getValue<std::shared_ptr<ImageSource>>(SourceProperty());
		auto bm = source->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
		m_renderObj->material()->textures().push_back(std::make_shared<Texture2D>(*bm));
	}
	else if (args.property == StretchProperty())
	{
		setValue(StretchProperty(), args.newValue.extract<StretchE>());
	}
}

Size Image::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	auto source = getValue<std::shared_ptr<ImageSource>>(SourceProperty());
	auto bm = source->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
	return Size(std::max<float>(availableSize.width(), (float)bm->width()), std::max<float>(availableSize.height(), (float)bm->height()));
}

Size Image::arrangeOverride(const Size & finalSize)
{
	auto stretch = getValue<StretchE>(StretchProperty());
	auto source = getValue<std::shared_ptr<ImageSource>>(SourceProperty());
	auto bm = source->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
	switch (stretch)
	{
	case StretchE::Origion:
	{
		return Size((float)bm->width(), (float)bm->height());
	}
	case StretchE::Fill:
	{
		return m_availableSize;
	}
	case StretchE::Uniform:
	{
		Size sz;
		auto pixelRatio = source->width() / source->heigth();
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
		auto pixelRatio = source->width() / source->heigth();
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
