#include "gles/Quadrangle.h"
#include <array>
#include <math.h>

using namespace nb;
using namespace nb::gl;

Quadrangle::Quadrangle()
	: Quadrangle(0.0f, 0.0f)
{
}

Quadrangle::Quadrangle(float width, float height)
	: m_width(width)
	, m_height(height)
	, m_radiusX(0.0f)
	, m_radiusY(0.0f)
{
	meshes.push_back(Mesh());
	update();
}

void Quadrangle::setWidth(float width)
{
	if (width != m_width)
	{
		m_width = width;
		update();
	}
}

void Quadrangle::setHeight(float height)
{
	if (height != m_height)
	{
		m_height = height;
		update();
	}
}

void Quadrangle::setRadiuX(float radiusX)
{
	if (radiusX != m_radiusX)
	{
		m_radiusX = radiusX;
		update();
	}
}

void Quadrangle::setRadiuY(float radiusY)
{
	if (radiusY != m_radiusY)
	{
		m_radiusY = radiusY;
		update();
	}
}

void Quadrangle::update()
{
	//四个角点位置
	std::array<glm::vec3, 4> cornerPoints{ glm::vec3{ -m_width * 0.5, m_height * 0.5, 0.0f }, glm::vec3{ m_width * 0.5, m_height * 0.5, 0.0f }, glm::vec3{ m_width * 0.5, -m_height * 0.5, 0.0f }, glm::vec3{ -m_width * 0.5, -m_height * 0.5, 0.0f } };
	bool radius = (m_radiusX > 0.0f && m_radiusY > 0.0f);
	constexpr auto connerVertexSize = 20;
	constexpr auto connerIndicesSize = 3 * (connerVertexSize - 2);
	constexpr auto radianStep = M_PI_2 / (connerVertexSize - 2);
	auto &vertexs = meshes[0].vertexs;
	auto &indices = meshes[0].indices;
	vertexs.resize(radius ? connerVertexSize : 4);
	indices.resize(radius ? connerIndicesSize : 6);
	if (radius)
	{
		//限定圆角在矩形半长/宽内
		auto radiusX = m_radiusX <= m_width * 0.5f ? m_radiusX : m_width * 0.5f;
		auto radiusY = m_radiusY <= m_height * 0.5f ? m_radiusY : m_height * 0.5f;

		auto fillConnerVertexs = [&vertexs, &indices, &connerVertexSize, &connerIndicesSize, &radianStep](const glm::vec3 &center, float radiusX, float radiusY, float radianSpan, int beg) {
			for (auto i = 0u; i < connerVertexSize; ++i)
			{
				//填充顶点属性
				if (i == 0)
				{
					vertexs[beg].position = center;
				}
				else
				{
					auto radian = radianStep * (i - 1) + radianSpan;
					vertexs[beg + i].position = glm::vec3(radiusX * cos(radian), radiusY * sin(radian), 0.0) + center;
					vertexs[beg + i].color = vertexs[0].color;
					vertexs[beg + i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
				}
				//填充顶点序列
				if(i >= 0 && i < connerVertexSize - 2)
				{
					int base = 3 * i;
					indices[base] = beg;
					indices[base + 1] = beg + i + 1;
					indices[base + 2] = beg + i + 2;
				}
			}
		};
		//左上角弧形
		auto leftTopConnerCenter = glm::vec3{ radiusX - m_width * 0.5, radiusY - m_height * 0.5, 0.0f };
		fillConnerVertexs(leftTopConnerCenter, radiusX, radiusY, (float)M_PI, connerVertexSize * 0);

	}
	else
	{
		vertexs[0].position = cornerPoints[0];	vertexs[0].texCoord = glm::vec2(0.0, 0.0);
		vertexs[1].position = cornerPoints[1];	vertexs[1].texCoord = glm::vec2(1.0, 0.0);
		vertexs[2].position = cornerPoints[2];	vertexs[2].texCoord = glm::vec2(1.0, 1.0);
		vertexs[3].position = cornerPoints[3];	vertexs[3].texCoord = glm::vec2(0.0, 1.0);
		meshes[0].indices = { 0, 1, 2, 0, 2, 3 };
	}
}
