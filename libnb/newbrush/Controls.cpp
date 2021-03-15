#include "newbrush/Controls.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"

using namespace nb;

Image::Image()
	: m_stretch(StretchE::Origion)
{
}

void Image::setStretch(const StretchE &stretch)
{
	m_stretch = stretch;
}

const StretchE &Image::stretch() const
{
	return m_stretch;
}

void Image::setTexture(ref<Texture2D> texture)
{
	m_texture = texture;
}

ref<Texture2D> Image::texture() const
{
	return m_texture;
}

Size Image::measureOverride(const Size & availableSize)
{
	m_availableSize = availableSize;
	Size textureSize = m_texture ? Size(m_texture->width(), m_texture->height()) : Size();
	Size ret = Size(std::max(availableSize.width, textureSize.width), std::max(availableSize.height, textureSize.height));
	return ret;
}

Size Image::arrangeOverride(const Size & finalSize)
{
	Size textureSize = m_texture ? Size(m_texture->width(), m_texture->height()) : Size();
	if (textureSize.isZero())
		return Size();

	switch (m_stretch)
	{
	case StretchE::Origion:
	{
		return textureSize;
	}
	case StretchE::Fill:
	{
		return m_availableSize;
	}
	case StretchE::Uniform:
	{
		Size sz;
		auto pixelRatio = textureSize.width / textureSize.height;
		auto containerRatio = m_availableSize.width / m_availableSize.height;
		if (pixelRatio < containerRatio)
		{
			sz = { m_availableSize.height * pixelRatio, m_availableSize.height };
		}
		else
		{
			sz = { m_availableSize.width, m_availableSize.width / pixelRatio };
		}
		return sz;
	}
	case StretchE::UniformToFill:
	{
		Size sz;
		auto pixelRatio = textureSize.width / textureSize.height;
		auto containerRatio = m_availableSize.width / m_availableSize.height;
		if (pixelRatio < containerRatio)
		{
			sz = { m_availableSize.width, m_availableSize.width / pixelRatio };
		}
		else
		{
			sz = { m_availableSize.height * pixelRatio, m_availableSize.height };
		}
		return sz;
	}
	default: nbThrowException(std::invalid_argument, "invalid StretchE"); break;
	}
}

void Image::onRender()
{
	Rect rc = getRenderRect();
	if (m_texture)
	{
		Renderer2D::drawImage(rc, glm::mat4(1.0f), m_texture, Rect(0.0f, 0.0f, m_texture->width(), m_texture->height()), false, getOpacity());
	}
}

/////////////////
ButtonBase::ButtonBase()
	: m_isPressed(false)
{
}

bool ButtonBase::isPressed() const
{
	return m_isPressed;
}

void ButtonBase::onTouch(const TouchEventArgs & e)
{
	Node2D::onTouch(e);
	switch (e.action)
	{
	case TouchActionE::down:
	{
		m_isPressed = true;
	}
	break;
	case TouchActionE::enter:
	{
		if (m_leaveWithPressed)
			m_isPressed = true;
	}
	break;
	case TouchActionE::leave:
	{
		m_leaveWithPressed = m_isPressed;
		m_isPressed = false;
	}
	break;
	case TouchActionE::up:
	{
		bool bShouldClick = m_isPressed;
		m_isPressed = false;
		if (bShouldClick)
		{
			onClick();
		}
	}
	break;
	default:
		break;
	}
}

void ButtonBase::onClick()
{
	Click.invoke({this});
}

Polyline::Polyline()
	: Polyline({}, 10.0f)
{
}

Polyline::Polyline(const std::vector<glm::vec2>& points, float size)
	: m_points(points)
	, m_size(size)
{
}

Size Polyline::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polyline::arrangeOverride(const Size & finalSize)
{
	if (m_points.empty())
	{
		return Size(0.0f, 0.0f);
	}
	else
	{
		auto xMinMax = std::minmax_element(m_points.begin(), m_points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.x > p0.x; });
		auto yMinMax = std::minmax_element(m_points.begin(), m_points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.y > p0.y; });
		auto sz = Size(xMinMax.second->x - xMinMax.first->x, yMinMax.second->y - yMinMax.first->y);
		return sz;
	}
}

void Polyline::onRender()
{
	Rect rc = getRenderRect();
	Renderer2D::drawPolyline(background(), m_points, m_size, {rc.x(), rc.y()});
}

////////////////////
Polygon::Polygon()
{
}

Polygon::Polygon(const std::vector<glm::vec2>& points)
	: m_points(points)
{
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
{
	if (m_points.empty())
	{
		return Size(0.0f, 0.0f);
	}
	else
	{
		auto xMinMax = std::minmax_element(m_points.begin(), m_points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.x > p0.x; });
		auto yMinMax = std::minmax_element(m_points.begin(), m_points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.y > p0.y; });
		auto sz = Size(xMinMax.second->x - xMinMax.first->x, yMinMax.second->y - yMinMax.first->y);
		return sz;
	}
}

void Polygon::onRender()
{
	Rect rc = getRenderRect();
	Renderer2D::drawPolygon(background(), m_points, { rc.x(), rc.y() });
}
