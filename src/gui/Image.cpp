#include "newbrush/gui/Image.h"
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/DependencyProperty.h"
#include <glm/gtc/matrix_transform.hpp>
#include "newbrush/gui/DrawingContext.h"

using namespace nb;

void Image::onRender(DrawingContextPtr dc)
{
	auto imgSource = getValue<ImageSourcePtr>(SourceProperty());
	if (imgSource == nullptr)
	{
		return;
	}

	auto offset = worldOffset();
	auto const &actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);//UIElement未做裁剪，所以render区域可能会超出范围

	dc->drawImage(imgSource, rc);
}

DependencyPropertyPtr Image::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, ImageSourcePtr>("Source", nullptr, onSourcePropertyChanged);
	return dp;
}

DependencyPropertyPtr Image::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, StretchE>("Stretch", StretchE::Uniform, onStretchPropertyChanged);
	return dp;
}

Size Image::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	auto source = getValue<ImageSourcePtr>(SourceProperty());
	Size sourceSize = source ? Size(source->width(), source->height()) : Size();
	return Size(std::max(availableSize.width(), sourceSize.width()), std::max(availableSize.height(), sourceSize.height()));
}

Size Image::arrangeOverride(const Size & finalSize)
{
	auto stretch = getValue<StretchE>(StretchProperty());
	auto source = getValue<ImageSourcePtr>(SourceProperty());
	Size sourceSize = source ? Size(source->width(), source->height()) : Size();
	if (sourceSize.isZero())
		return Size();

	switch (stretch)
	{
	case StretchE::Origion:
	{
		return Size(sourceSize.width(), sourceSize.height());
	}
	case StretchE::Fill:
	{
		return m_availableSize;
	}
	case StretchE::Uniform:
	{
		Size sz;
		auto pixelRatio = sourceSize.width() / sourceSize.height();
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
		auto pixelRatio = sourceSize.width() / sourceSize.height();
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

void Image::onSourcePropertyChanged(DependencyObject * obj, const DependencyPropertyChangedEventArgs & args)
{
}

void Image::onStretchPropertyChanged(DependencyObject * obj, const DependencyPropertyChangedEventArgs & args)
{
	auto self = dynamic_cast<Image*>(obj);
	self->updateLayout();
}
