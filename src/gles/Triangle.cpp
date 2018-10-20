#include "gles/Triangle.h"
#include <math.h>

using namespace nb::core;
using namespace nb::gl;

Triangle::Triangle()
{
	std::vector<Vertex> vertexs;
	for (int i = 0; i != 3; ++i)
		vertexs.push_back(Vertex());
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
}

Triangle::Triangle(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2)
{
	Vec3 c = Vec3(center(p0, p1, p2), 0.0f);
	std::vector<Vertex> vertexs;
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - c));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - c));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - c));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(c.x(), c.y(), 0.0f);
}

Triangle::Triangle(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec4 &color)
{
	Vec3 c = Vec3(center(p0, p1, p2), 0.0f);
	std::vector<Vertex> vertexs;
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - c, color));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - c, color));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - c, color));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(c.x(), c.y(), 0.0f);
}

Triangle::Triangle(const Vec2 &p0, const Vec2 &p1, const Vec2 &p2, const Vec4 &color0, const Vec4 &color1, const Vec4 &color2)
{
	Vec3 c = Vec3(center(p0, p1, p2), 0.0f);
	std::vector<Vertex> vertexs;
	vertexs.push_back(Vertex(Vec3(p0, 0.0f) - c, color0));
	vertexs.push_back(Vertex(Vec3(p1, 0.0f) - c, color1));
	vertexs.push_back(Vertex(Vec3(p2, 0.0f) - c, color2));
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(c.x(), c.y(), 0.0f);
}

std::vector<uint16_t> Triangle::getIndices() const
{
	unsigned short arr[3] = { 0, 1, 2 };
	return std::vector<uint16_t>(arr, arr + 3);
}

double Triangle::distance(const nb::core::Vec2 & p0, const nb::core::Vec2 & p1) const
{
	return sqrt((p0.x() - p1.x()) * (p0.x() - p1.x()) + (p0.y() - p1.y() * (p0.y() - p1.y())));
}

Vec2 Triangle::center(const nb::core::Vec2 & p0, const nb::core::Vec2 & p1, const nb::core::Vec2 & p2) const
{
	double A = distance(p1, p2);
	double B = distance(p0, p2);
	double C = distance(p0, p1);
	double S = A + B + C;
	double x = (A * p0.x() + B * p1.x() + C * p2.x()) / S;
	double y = (A * p0.y() + B * p1.y() + C * p2.y()) / S;
	return Vec2((float)x, (float)y);
}
