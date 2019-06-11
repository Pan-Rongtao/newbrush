#include "gles/Quadrangle.h"

using namespace nb::core;
using namespace nb::gl;

Quadrangle::Quadrangle()
	: Quadrangle(glm::vec2(), glm::vec2(), glm::vec2(), glm::vec2(), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
{
}

Quadrangle::Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3)
	: Quadrangle(p0, p1, p2, p3, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
{
}

Quadrangle::Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color)
	: Quadrangle(p0, p1, p2, p3, color, color, color, color)
{
}

Quadrangle::Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2, const glm::vec4 &color3)
{
	auto center = getCenter(p0, p1, p2, p3);
	std::vector<Vertex> vertexs{
		Vertex(glm::vec3(p0, 0.0f) - center, color0, glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(p1, 0.0f) - center, color1, glm::vec2(1.0, 0.0)),
		Vertex(glm::vec3(p2, 0.0f) - center, color2, glm::vec2(1.0, 1.0)),
		Vertex(glm::vec3(p3, 0.0f) - center, color3, glm::vec2(0.0, 1.0))
	};
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(center.x, center.y, center.z);
}

std::vector<uint16_t> Quadrangle::getIndices() const
{
	//ÄæÊ±Õë£¬ÇÒÒþ²Ø±³Ãæ
	return std::vector<uint16_t>{ 0, 1, 2, 0, 2, 3 };
}

glm::vec3 Quadrangle::getCenter(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) const
{
	return glm::vec3((p0 + p1 + p2 + p3) / 4.0f, 0.0f);
}