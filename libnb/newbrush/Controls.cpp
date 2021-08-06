﻿#include "newbrush/Controls.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"
#include <queue>

using namespace nb;

void Panel::onRender()
{
	drawBrush(background());
	for (auto child : children())
	{
		child->onRender();
	}
}

WrapPanel::WrapPanel()
	: WrapPanel(OrientationE::Horizontal)
{}

WrapPanel::WrapPanel(OrientationE orientation)
	: m_orientation(orientation)
	, m_itemWidth(NAN)
	, m_itemHeight(NAN)
{}

void WrapPanel::setOrientation(OrientationE orientation)
{
	m_orientation = orientation;
}

OrientationE WrapPanel::orientation() const
{
	return m_orientation;
}

void WrapPanel::setItemWidth(float width)
{
	m_itemWidth = width;
}

float WrapPanel::itemWidth() const
{
	return m_itemWidth;
}

void WrapPanel::setItemHeight(float height)
{
	m_itemHeight = height;
}

float WrapPanel::itemHeight() const
{
	return m_itemHeight;
}

//当测量一个子元素时，遵循这样的原则：每个子元素的childMeasureSize，如果设置了ItemWidth和ItemHeight，则measure宽高固定为ItemWidth,ItemHeight。
//否则取availableSize
Size WrapPanel::measureOverride(const Size & availableSize)
{
	Size childMeasureSize;
	for (auto child : children())
	{
		auto childWidth = child->width();
		auto childHeight = child->height();
		childMeasureSize.width = !std::isnan(m_itemWidth) ? m_itemWidth : !std::isnan(childWidth) ? childWidth : 0.0f;
		childMeasureSize.height = !std::isnan(m_itemHeight) ? m_itemHeight : !std::isnan(childHeight) ? childHeight : 0.0f;
		child->measure(childMeasureSize);
	}
	return availableSize;
}
//arrange两个方向维度进行：
//当Orientation == OrientationE::Horizontal时，分两种情况：1、指定了ItemHeight，则每一行高度为ItemHeight，累加每个item，当累加宽度超过finnalSize.width时，换行；2、未指定ItemHeight，先遍历items，确定行信息（每一行的开头下标，以及最高项作为该行的高）
//当Orientation == OrientationE::Vertical时，分两种情况：1、指定了ItemWdith，则每一行高度为ItemWidth，累加每个item，当累加高度超过finalSize.height时，换列；2、未指定ItemWidth，先遍历items，确定列信息（每一列的开头下标，以及最宽项作为该列的宽）
Size WrapPanel::arrangeOverride(const Size & finalSize)
{
	//计算行（列）信息，返回没行（列）的起始index和高（宽）std::queue<std::pair<int, float>>
	auto calcLinesInfo = [&]()->std::queue<std::pair<int, float>>
	{
		std::queue<std::pair<int, float>> ret;
		if (!hasChild())
			return ret;

		auto sum = 0.0f;
		ret.push({ 0, 0.0f });
		for (int i = 0; i != childCount(); ++i)
		{
			auto child = getChildAt(i);
			auto one = 0.0f;
			auto maxLen = 0.0f;
			auto const &childDesiredSize = child->getDesiredSize();
			if (m_orientation == OrientationE::Horizontal)
			{
				maxLen = finalSize.width;
				one = !std::isnan(m_itemWidth) ? m_itemWidth : childDesiredSize.width;
			}
			else
			{
				maxLen = finalSize.height;
				one = !std::isnan(m_itemHeight) ? m_itemHeight : childDesiredSize.height;
			}

			if (sum + one <= maxLen)
			{
				ret.back().first = i;
				ret.back().second = std::max<float>(ret.back().second, m_orientation == OrientationE::Horizontal ? childDesiredSize.height : childDesiredSize.width);
				sum += one;
			}
			else
			{
				ret.push({ i, (m_orientation == OrientationE::Horizontal ? childDesiredSize.height : childDesiredSize.width) });
				sum = one;
			}
		}
		return ret;
	};

	auto x = 0.0f;
	auto y = 0.0f;
	Rect arrangeRect;
	if (m_orientation == OrientationE::Horizontal)
	{
		//指定了ItemHeight，每个item的高度都为iItemHeight
		//否则，需要先计算每一行的最高item作为那一行的高度
		if (!std::isnan(m_itemHeight))
		{
			for (auto child : children())
			{
				auto const &childDesiredSize = child->getDesiredSize();
				auto w = !std::isnan(m_itemWidth) ? m_itemWidth : childDesiredSize.width;
				//如果该行放置得下，或者child的arrage.width大于finalSize.width且尝试放置child在新行的第一个，不换行，否则换行
				if ((x + w <= finalSize.width) || (x == 0.0 && w > finalSize.width))
				{
					arrangeRect.reset(x, y, w, m_itemHeight);
					x += w;
				}
				else
				{
					y += m_itemHeight;
					arrangeRect.reset(0.0, y, w, m_itemHeight);
					x = w;
				}
				child->arrage(arrangeRect);
			}
		}
		else
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != childCount(); ++i)
			{
				auto child = getChildAt(i);
				auto const &childDesiredSize = child->getDesiredSize();
				auto w = !std::isnan(m_itemWidth) ? m_itemWidth : childDesiredSize.width;
				if (i <= linesInfo.front().first)
				{
					arrangeRect.reset(x, y, w, linesInfo.front().second);
					x += w;
				}
				else
				{
					y += linesInfo.front().second;
					linesInfo.pop();
					arrangeRect.reset(0.0, y, w, linesInfo.front().second);
					x = w;
				}
				child->arrage(arrangeRect);
			}
		}
	}
	else//垂直方向
	{
		//指定了ItemWidth，则每一列高度为ItemWidth
		//否则，需要先计算每一列的最宽item作为那一列的宽度
		if (!std::isnan(m_itemWidth))
		{
			for (auto child : children())
			{
				auto const &childDesiredSize = child->getDesiredSize();
				auto h = !std::isnan(m_itemHeight) ? m_itemHeight : childDesiredSize.height;
				//如果该列放置得下，或者child的arrage.height大于finalSize.width且尝试放置child在新列的第一个，不换列，否则换列
				if ((y + h <= finalSize.height) || (y == 0.0 && h > finalSize.height))
				{
					arrangeRect.reset(x, y, m_itemWidth, h);
					y += h;
				}
				else
				{
					x += m_itemWidth;
					arrangeRect.reset(x, 0.0f, m_itemWidth, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
		else
		{
			auto linesInfo = calcLinesInfo();
			for (int i = 0; i != childCount(); ++i)
			{
				auto child = getChildAt(i);
				auto const &childDesiredSize = child->getDesiredSize();
				auto h = !std::isnan(m_itemHeight) ? m_itemHeight : childDesiredSize.height;
				if (i <= linesInfo.front().first)
				{
					arrangeRect.reset(x, y, linesInfo.front().second, h);
					y += h;
				}
				else
				{
					x += linesInfo.front().second;
					linesInfo.pop();
					arrangeRect.reset(x, 0.0f, linesInfo.front().second, h);
					y = h;
				}
				child->arrage(arrangeRect);
			}
		}
	}
	return finalSize;
}

Image::Image()
	: m_stretch(StretchE::Origion)
{}

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
		Renderer2D::drawImage(rc, glm::mat4(1.0f), TextureFrame(m_texture), getOpacity());
	}
}

///////////////////
TextBlock::TextBlock(const std::string & text)
	: m_text(text)
	, m_color(Colors::black)
{}

void TextBlock::setText(const std::string & text)
{
	m_text = text;
}

const std::string & TextBlock::text() const
{
	return m_text;
}

void TextBlock::setColor(const Color &color)
{
	m_color = color;
}

const Color & TextBlock::color() const
{
	return m_color;
}

Size TextBlock::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size TextBlock::arrangeOverride(const Size & finalSize)
{
	return finalSize;
}

void TextBlock::onRender()
{
	Rect rc = getRenderRect();
	auto font = m_font ? m_font : FontLibrary::getDefaultFont();
	Renderer2D::drawText(font, rc.leftTop(), m_text, glm::vec4(m_color.rf(), m_color.gf(), m_color.bf(), m_color.af()));
}


/////////////////
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
		m_leaveWithPressed = false;
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
{}

Polyline::Polyline(const std::vector<glm::vec2>& points, float size)
	: m_size(size)
{
	setPoints(points);
}

void Polyline::setPoints(const std::vector<glm::vec2> &points)
{
	m_points = points;
	m_box = TreeHelper::getBox(m_points);
}

const std::vector<glm::vec2> &Polyline::points() const
{
	return m_points;
}

Size Polyline::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polyline::arrangeOverride(const Size & finalSize)
{
	return Size(m_box.z, m_box.w);
}

void Polyline::onRender()
{
	Rect rc = getRenderRect();
	Renderer2D::drawPolyline(background(), m_points, m_size, { rc.x(), rc.y() });
}

////////////////////
Polygon::Polygon()
	: Polygon(std::vector<glm::vec2>{})
{}

Polygon::Polygon(const std::vector<glm::vec2>& points)
{
	setPoints(points);
}

void Polygon::setPoints(const std::vector<glm::vec2>& points)
{
	m_points = points;
	m_box = TreeHelper::getBox(m_points);
}

const std::vector<glm::vec2>& Polygon::points() const
{
	return m_points;
}

Size Polygon::measureOverride(const Size & availableSize)
{
	return availableSize;
}

Size Polygon::arrangeOverride(const Size & finalSize)
{
	return Size(m_box.z, m_box.w);
}

void Polygon::onRender()
{
	Rect rc = getRenderRect();
	Renderer2D::drawPolygon(background(), m_points, { rc.x(), rc.y() });
}

////////////////////
void Visual3D::setMaterial(ref<Material> material)
{
	m_mesh->material = material;
}

ref<Material> Visual3D::material() const
{
	return m_mesh->material;
}

Cube::Cube()
	: Cube(glm::vec3(0.0f), 1.0f)
{}

Cube::Cube(const glm::vec3 & center, float uniformLenght)
	: Cube(center, uniformLenght, uniformLenght, uniformLenght)
{}

Cube::Cube(const glm::vec3 &center, float lenght, float width, float height)
{
/*	//前一个面（四个点，左上前，右上前，左下前，右下前）
	//后一个面（四个点，左上后，右上后，右下后，左下后）
	Vertex vtLUF, vtRUF, vtLDF, vtRDF, vtLUB, vtRUB, vtRDB, vtLDB;
	vtLUF.position = { -lenght / 2, height / 2, width / 2 };
	//vtLUF.uv = { 1.0f, 0.0f };
	vtRUF.position = { lenght / 2, height / 2, width / 2 };
	//vtRUF.uv = { 1.0f, 0.0f };
	vtLDF.position = { lenght / 2, -height / 2, width / 2 };
	//vtLDF.uv = { 1.0f, 0.0f };
	vtRDF.position = { -lenght / 2, -height / 2, width / 2 };
	//vtRDF.uv = { 0.0f, 0.0f };
	vtLUB.position = { -lenght / 2, height / 2, -width / 2 };
	//vtLUB.uv = { 0.0f, 1.0f };
	vtRUB.position = { lenght / 2, height / 2, -width / 2 };
	//vtRUB.uv = { 1.0f, 1.0f };
	vtRDB.position = { lenght / 2, -height / 2, -width / 2 };
	//vtRDB.uv = { 1.0f, 0.0f };
	vtLDB.position = { -lenght / 2, -height / 2, -width / 2 };
	//vtLDB.uv = { 0.0f, 0.0f };
	auto vertexs = { vtLUF, vtRUF, vtLDF, vtRDF, vtLUB, vtRUB, vtRDB, vtLDB };
	//上下左右前后
	std::vector<uint16_t> indices =
	{
		1,4,5, 1,0,4,	//top
		7,3,2, 7,2,6,	//bottom
		0,3,7, 0,7,4,	//left
		1,5,2, 5,6,2,	//right
		0,1,2, 0,2,3,	//front
		4,6,5, 4,7,6,	//back
	};
	m_mesh = createRef<Mesh>(vertexs, indices, nullptr);*/
		
	std::vector<Vertex> vertexs;
	vertexs.reserve(36);

	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, -height, -lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 0.0f }));

	vertexs.emplace_back(Vertex({ -width, -height, lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, -height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, height, lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, lenght }, { 0.0f, 0.0f }));

	vertexs.emplace_back(Vertex({ -width, height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, height, lenght }, { 1.0f, 0.0f }));

	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, -height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, -height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, -height, lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 0.0f }));

	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, -height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, -height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, -height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, -height, -lenght }, { 0.0f, 1.0f }));

	vertexs.emplace_back(Vertex({ -width, height, -lenght }, { 0.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, height, -lenght }, { 1.0f, 1.0f }));
	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ width, height, lenght }, { 1.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, height, lenght }, { 0.0f, 0.0f }));
	vertexs.emplace_back(Vertex({ -width, height, -lenght }, { 0.0f, 1.0f }));

	m_mesh = createRef<Mesh>(vertexs, nullptr);
}

void Cube::onRender(ref<Camera> camera, const std::vector<ref<Light>>& lights)
{
	auto const &mat = getTransform() ? getTransform()->value() : Transform::identityMatrix4();
	m_mesh->draw(mat, camera, lights, GL_TRIANGLES, false);
}

SkyBox::SkyBox()	//天空盒的尺寸是无影响的，因为shader中使用w替代z
{
	//前一个面（四个点，左上前，右上前，左下前，右下前）
	//后一个面（四个点，左上后，右上后，右下后，左下后）
	Vertex vtLUF(glm::vec3({ -1.0f, 1.0f, 1.0f }));
	Vertex vtRUF(glm::vec3({ 1.0f, 1.0f, 1.0f }));
	Vertex vtLDF(glm::vec3({ 1.0f, -1.0f, 1.0f }));
	Vertex vtRDF(glm::vec3({ -1.0f, -1.0f, 1.0f }));
	Vertex vtLUB(glm::vec3({ -1.0f, 1.0f, -1.0f }));
	Vertex vtRUB(glm::vec3({ 1.0f, 1.0f, -1.0f }));
	Vertex vtRDB(glm::vec3({ 1.0f, -1.0f, -1.0f }));
	Vertex vtLDB(glm::vec3({ -1.0f, -1.0f, -1.0f }));
	auto vertexs = { vtLUF, vtRUF, vtLDF, vtRDF, vtLUB, vtRUB, vtRDB, vtLDB };
	//上下左右前后
	std::vector<uint16_t> indices =
	{
		1,4,5, 1,0,4,	//top
		7,3,2, 7,2,6,	//bottom
		0,3,7, 0,7,4,	//left
		1,5,2, 5,6,2,	//right
		0,1,2, 0,2,3,	//front
		4,6,5, 4,7,6,	//back
	};
	m_mesh = createRef<Mesh>(vertexs, indices, nullptr);
}

void SkyBox::onRender(ref<Camera> camera, const std::vector<ref<Light>>& lights)
{
	GLint oldCullFace = -1, oldDepthFunc = -1;
	glGetIntegerv(GL_CULL_FACE, &oldCullFace);
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);

	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	
	auto cm = std::make_shared<PerspectiveCamera>(*(as<PerspectiveCamera>(camera).get()));
	cm->setTranslate(glm::vec3(0.0));
	auto const &mat = getTransform() ? getTransform()->value() : Transform::identityMatrix4();
	m_mesh->draw(mat, cm, lights);

	oldCullFace ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	glDepthFunc(oldDepthFunc);
}
