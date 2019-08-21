#include "gles/Triangle.h"
#include <math.h>

using namespace nb;
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
	meshes().push_back(Mesh(vertexs, { 0, 1, 2 }));
	translate(c.x, c.y, c.z);
}

glm::vec2 Triangle::center(const glm::vec2 & p0, const glm::vec2 & p1, const glm::vec2 & p2) const
{
	auto distance = [](const glm::vec2 & p0, const glm::vec2 & p1) {
		return std::hypotf(p0.x - p1.x, p0.y - p1.y);
	};
	auto A = distance(p1, p2);
	auto B = distance(p0, p2);
	auto C = distance(p0, p1);
	auto S = A + B + C;
	auto x = (A * p0.x + B * p1.x + C * p2.x) / S;
	auto y = (A * p0.y + B * p1.y + C * p2.y) / S;
	return glm::vec2(x, y);
}
