#include "gles/Quadrangle.h"
#include <array>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;
using namespace nb::gl;

Quadrangle::Quadrangle()
	: Quadrangle(glm::vec2(), glm::vec2(), glm::vec2(), glm::vec2(), 0.0f, 0.0f)
{
}

Quadrangle::Quadrangle(const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3)
	: Quadrangle(p0, p1, p2, p3, 0.0f, 0.0f)
{
}

Quadrangle::Quadrangle(const glm::vec2 & p0, const glm::vec2 & p1, const glm::vec2 & p2, const glm::vec2 & p3, float radiusX, float radiusY)
{
	auto getCenter = [](const glm::vec2 &p0, const glm::vec2 &p1, const glm::vec2 &p2, const glm::vec2 &p3) {
		return glm::vec3((p0 + p1 + p2 + p3) / 4.0f, 0.0f);
	};
	auto center = getCenter(p0, p1, p2, p3);
	if (radiusX > 0.0f && radiusY > 0.0f)
	{
		//限定圆角在矩形半长/宽内
		auto size = glm::vec2(std::fabs(p1.x - p0.x), std::fabs(p2.y - p1.y));
		if (radiusX > size.x * 0.5f)	radiusX = size.x * 0.5f;
		if (radiusY > size.y * 0.5f)	radiusY = size.y * 0.5f;

		constexpr auto arcVertexCount = 20;
		std::vector<Vertex> vertexs(arcVertexCount * 4);
		constexpr auto radianStep = 2 * M_PI / (arcVertexCount - 2);
		//4个椭圆中心
		std::array<glm::vec2, 4> eclipseCenter{ glm::vec2{ radiusX - size.x * 0.5, size.y * 0.5 - radiusY }, glm::vec2{size.x * 0.5 - radiusX, size.y * 0.5 - radiusY},
			glm::vec2{ size.x * 0.5 - radiusX, radiusY - size.y * 0.5 }, glm::vec2{ radiusX - size.x * 0.5, radiusY - size.y * 0.5 } };
		//左上角弧形
		vertexs[0].position = glm::vec3{ radiusX - size.x * 0.5, size.y * 0.5 - radiusY, 0.0f };
		for (int i = 1; i != arcVertexCount; ++i)
		{
			auto radian = radianStep * i;
			vertexs[i].position = glm::vec3(radiusX * cos(radian), radiusY * sin(radian), 0.0);
			vertexs[i].texCoord = glm::vec2(0.5 * cos(radian) + 0.5, 1.0 - (0.5 * sin(radian) + 0.5));
		}
		auto getIndices = [&arcVertexCount]()->std::vector<uint16_t> {
			auto count = 3 * (arcVertexCount - 1);
			std::vector<uint16_t> indices(count);
			for (int i = 0; i != arcVertexCount - 2; ++i)
			{
				int base = 3 * i;
				indices[base] = 0;
				indices[base + 1] = i + 1;
				indices[base + 2] = i + 2;
			}
			indices[count - 3] = 0;
			indices[count - 2] = arcVertexCount - 1;
			indices[count - 1] = 1;
			return indices;
		};
		meshes.push_back(Mesh(vertexs, getIndices()));
	}
	{
		std::vector<Vertex> vertexs{
			Vertex(glm::vec3(p0, 0.0f) - center, glm::vec4(), glm::vec2(0.0, 0.0)),
			Vertex(glm::vec3(p1, 0.0f) - center, glm::vec4(), glm::vec2(1.0, 0.0)),
			Vertex(glm::vec3(p2, 0.0f) - center, glm::vec4(), glm::vec2(1.0, 1.0)),
			Vertex(glm::vec3(p3, 0.0f) - center, glm::vec4(), glm::vec2(0.0, 1.0))
		};
		meshes.push_back(Mesh(vertexs, { 0, 1, 2, 0, 2, 3 }));
	}
	matrix = glm::translate(matrix, glm::vec3(center.x, center.y, center.z));
}
