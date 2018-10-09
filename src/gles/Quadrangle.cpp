#include "gles/Quadrangle.h"

using namespace nb::core;
using namespace nb::gl;

Quadrangle::Quadrangle()
{
	std::vector<Vertex> vertexs;
	for (int i = 0; i != 4; ++i)
		vertexs.push_back(Vertex());
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
}

Quadrangle::Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3)
{
	std::vector<Vertex> vertexs;
	Vec3 center = getCenter(p0, p1, p2, p3);
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - center, Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(0.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - center, Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(1.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - center, Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(1.0, 1.0)));
	vertexs.push_back(Vertex(Vec3(p3, 0.0f) - center, Vec4(0.0f, 0.0f, 0.0f, 1.0f), Vec2(0.0, 1.0)));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(center.x(), center.y(), center.z());
}

Quadrangle::Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const Vec4 &color)
{
	std::vector<Vertex> vertexs;
	Vec3 center = getCenter(p0, p1, p2, p3);
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - center, color, Vec2(0.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - center, color, Vec2(1.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - center, color, Vec2(1.0, 1.0)));
	vertexs.push_back(Vertex(Vec3(p3, 0.0f) - center, color, Vec2(0.0, 1.0)));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(center.x(), center.y(), center.z());
}

Quadrangle::Quadrangle(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3, const Vec4 &color0, const Vec4 &color1, const Vec4 &color2, const Vec4 &color3)
{
	std::vector<Vertex> vertexs;
	Vec3 center = getCenter(p0, p1, p2, p3);
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - center, color0, Vec2(0.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - center, color1, Vec2(1.0, 0.0)));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - center, color2, Vec2(1.0, 1.0)));
	vertexs.push_back(Vertex(Vec3(p3, 0.0f) - center, color3, Vec2(0.0, 1.0)));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(center.x(), center.y(), center.z());
}

std::vector<uint16_t> Quadrangle::getIndices() const
{
	//ÄæÊ±Õë£¬ÇÒÒþ²Ø±³Ãæ
	unsigned short arr[6] = { 0,1,2, 0,2,3 };
	return std::vector<uint16_t>(arr, arr + 6);
}

Vec3 Quadrangle::getCenter(const nb::core::Vec2 &p0, const nb::core::Vec2 &p1, const nb::core::Vec2 &p2, const nb::core::Vec2 &p3) const
{
	return Vec3((p0 + p1 + p2 + p3) / 4, 0.0f);
}