#include "newbrush/gui/Image.h"
#include "newbrush/gles/Viewport2D.h"
#include "newbrush/gles/RenderObject.h"
#include "newbrush/gles/Model.h"
#include "newbrush/gles/Material.h"
#include "newbrush/gles/Program.h"
#include "newbrush/gles/Texture2D.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/gui/Window.h"
#include "newbrush/core/DependencyProperty.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;

Image::Image()
	: m_renderObj(std::make_shared<RenderObject>(std::make_shared<Model>(std::vector<Mesh>{ Mesh() }), Programs::image()))
{
	auto &mesh = m_renderObj->model()->meshes[0];
	auto &vertexs = mesh.vertexs;
	auto &indices = mesh.indices;
	vertexs.resize(4);
	vertexs[0].texCoord = glm::vec2(0.0, 1.0);
	vertexs[1].texCoord = glm::vec2(1.0, 1.0);
	vertexs[2].texCoord = glm::vec2(1.0, 0.0);
	vertexs[3].texCoord = glm::vec2(0.0, 0.0);
	indices.insert(indices.begin(), { 0, 1, 2, 0, 2, 3 });
}

void Image::onRender(Viewport2D & drawContext)
{
	auto offset = worldOffset();
	auto const &actualSize = getValue<Size>(ActualSizeProperty());
	Rect rc(offset.x(), offset.y(), actualSize);//UIElement未做裁剪，所以render区域可能会超出范围
	auto c = rc.center();
	auto &vertexs = m_renderObj->model()->meshes[0].vertexs;
	vertexs[0].position = glm::vec3{ -rc.width()* 0.5, rc.height() * 0.5, 0.0f };
	vertexs[1].position = glm::vec3{ rc.width() * 0.5, rc.height() * 0.5, 0.0f };
	vertexs[2].position = glm::vec3{ rc.width() * 0.5, -rc.height() * 0.5, 0.0f };
	vertexs[3].position = glm::vec3{ -rc.width() * 0.5, -rc.height() * 0.5, 0.0f };

	drawContext.queue(m_renderObj);
	m_renderObj->model()->matrix = glm::translate(glm::mat4(1.0), glm::vec3(c.x(), c.y(), 0.0f));
}

DependencyPropertyPtr Image::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, ImageSourcePtr>("Source", nullptr, onSourcePropertyChanged, nullptr, nullptr);
	return dp;
}

DependencyPropertyPtr Image::StretchProperty()
{
	static auto dp = DependencyProperty::registerDependency<Image, StretchE>("Stretch", StretchE::Uniform, onStretchPropertyChanged, nullptr, nullptr);
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
	auto newSource = args.newValue().get_value<ImageSourcePtr>();
	auto &stream = newSource->stream();
	auto self = dynamic_cast<Image*>(obj);
	auto texture = std::make_shared<Texture2D>();
	auto glFormatAndType = Texture::getGlFormatAndType(newSource->channels());
	texture->update((const unsigned char *)stream.data(), (int)newSource->width(), (int)newSource->height(), glFormatAndType.first, glFormatAndType.second);
	auto &material = self->m_renderObj->model()->meshes[0].material;
	material.textures().push_back(texture);
	self->updateLayout();
}

void Image::onStretchPropertyChanged(DependencyObject * obj, const DependencyPropertyChangedEventArgs & args)
{
	auto self = dynamic_cast<Image*>(obj);
	self->updateLayout();
}
