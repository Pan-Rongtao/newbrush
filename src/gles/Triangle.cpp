#include "gles/Triangle.h"
#include <math.h>

using namespace nb::core;
using namespace nb::gl;

Triangle::Triangle()
	: Triangle(glm::vec2(), glm::vec2(), glm::vec2(), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0))
{
}

Triangle::Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2)
	: Triangle(p0, p1, p2, glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0))
{
}

Triangle::Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color)
	: Triangle(p0, p1, p2, color, color, color)
{
}

Triangle::Triangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec4 &color0, const glm::vec4 &color1, const glm::vec4 &color2)
{
	auto c = glm::vec3(center(p0, p1, p2), 0.0f);
	std::vector<Vertex> vertexs{
		Vertex(glm::vec3(p0, 0.0f) - c, color0),
		Vertex(glm::vec3(p1, 0.0f) - c, color1),
		Vertex(glm::vec3(p2, 0.0f) - c, color2) 
	};
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(c.x, c.y, c.z);
}

std::vector<uint16_t> Triangle::getIndices() const
{
	return std::vector<uint16_t>{ 0, 1, 2 };
}

double Triangle::distance(const glm::vec2 & p0, const glm::vec2 & p1) const
{
	return sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y * (p0.y - p1.y)));
}

glm::vec2 Triangle::center(const glm::vec2 & p0, const glm::vec2 & p1, const glm::vec2 & p2) const
{
	double A = distance(p1, p2);
	double B = distance(p0, p2);
	double C = distance(p0, p1);
	double S = A + B + C;
	double x = (A * p0.x + B * p1.x + C * p2.x) / S;
	double y = (A * p0.y + B * p1.y + C * p2.y) / S;
	return glm::vec2((float)x, (float)y);
}
