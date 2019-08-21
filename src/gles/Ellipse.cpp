#include "gles/Ellipse.h"
#include <math.h>

using namespace nb;
using namespace nb::gl;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
//顶点越多越圆滑
constexpr int		EllipseVertexCount			= 50;
constexpr int		EllipseIndicesBufferSize	= 3 * (EllipseVertexCount - 1);
constexpr auto		EllipseRadianStep			= NB_2PI / (EllipseVertexCount - 2);

Ellipse::Ellipse(float x, float y, float a, float b, bool cartesian)
{
	std::vector<Vertex> vertexs{ Vertex(glm::vec3(), glm::vec4(), glm::vec2(0.5, 0.5)) };//中心点
	//是否是笛卡尔坐标系，顶点和纹理坐标将不同
	if (cartesian)
	{
		for (int i = 1; i != EllipseVertexCount; ++i)
		{
			auto radian = EllipseRadianStep * i;
			glm::vec2 texCoord(0.5 * cos(radian) + 0.5, 0.5 * sin(radian) + 0.5);
			vertexs.push_back(Vertex(glm::vec3(a * cos(radian), b * sin(radian), 0.0), glm::vec4(), texCoord));
		}
	}
	else
	{
		for (int i = EllipseVertexCount - 1; i != 0; --i)
		{
			auto radian = EllipseRadianStep * i;
			glm::vec2 texCoord(0.5 * cos(radian) + 0.5, 1 - (0.5 * sin(radian) + 0.5));
			vertexs.push_back(Vertex(glm::vec3(a * cos(radian), b * sin(radian), 0.0), glm::vec4(), texCoord));
		}
	}
	meshes().push_back(Mesh(vertexs, getIndices()));
	translate(x, y, 0.0f);
}

std::vector<uint16_t> Ellipse::getIndices() const
{
	std::vector<uint16_t> indices(EllipseIndicesBufferSize);
	for (int i = 0; i != EllipseVertexCount - 2; ++i)
	{
		int base = 3 * i;
		indices[base] = 0;
		indices[base + 1] = i + 1;
		indices[base + 2] = i + 2;
	}
	indices[EllipseIndicesBufferSize - 3] = 0;
	indices[EllipseIndicesBufferSize - 2] = EllipseVertexCount - 1;
	indices[EllipseIndicesBufferSize - 1] = 1;
	return indices;
}
