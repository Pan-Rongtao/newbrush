#include "gles/Polyline.h"
#include <opengl/GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;

Polyline::Polyline()
	: Polyline(std::vector<glm::vec2>())
{
}

Polyline::Polyline(const std::vector<glm::vec2>& points)
{
	setDrawMode(GL_LINE_STRIP);//GL_LINE_LOOP

	auto center = glm::vec3(0.0f);
	if (!points.empty())
	{
		auto xMinMax = std::minmax_element(points.begin(), points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.x > p0.x; });
		auto yMinMax = std::minmax_element(points.begin(), points.end(), [](const glm::vec2 &p0, const glm::vec2 &p1) { return p1.y > p0.y; });
		auto center = glm::vec3((xMinMax.second->x - xMinMax.first->x) / 2.0f, (yMinMax.second->y - yMinMax.first->y) / 2.0f, 0.0f);
	}
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	for (int i = 0; i != points.size(); ++i)
	{
		vertexs.push_back(Vertex(glm::vec3(points[i], 0.0f) - center, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		indices.push_back(i);
	}
	meshes().push_back(Mesh(vertexs, indices));
	translate(center.x, center.y, center.z);
}
