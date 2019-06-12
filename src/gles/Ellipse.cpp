#include "gles/Ellipse.h"
#include <math.h>

using namespace nb::gl;
using namespace nb::core;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
//顶点越多越圆滑
constexpr int EllipseVertexCount = 50;
constexpr int EllipseIndicesBufferSize = 3 * (EllipseVertexCount - 1);

Ellipse::Ellipse(float x, float y, float a, float b, bool cartesian)
{
	std::vector<Vertex> vertexs;
	//中心点
	vertexs.push_back(Vertex(glm::vec3(), glm::vec4(), glm::vec2(0.5, 0.5)));
	double oneRadian = NB_2PI / (EllipseVertexCount - 2);
	//是否是笛卡尔坐标系，顶点和纹理坐标将不同
	if (cartesian)
	{
		for (int i = 1; i != EllipseVertexCount; ++i)
		{
			double radian = oneRadian * i;
			glm::vec2 texCoord((float)(0.5 * cos(radian) + 0.5), (float)(0.5 * sin(radian) + 0.5));
			vertexs.push_back(Vertex(glm::vec3(a * (float)cos(radian), b * (float)sin(radian), 0.0f), glm::vec4(), texCoord));
		}
	}
	else
	{
		for (int i = EllipseVertexCount - 1; i != 0; --i)
		{
			double radian = oneRadian * i;
			glm::vec2 texCoord((float)(0.5 * cos(radian) + 0.5), (float)(1 - (0.5 * sin(radian) + 0.5)));
			vertexs.push_back(Vertex(glm::vec3((float)(a * cos(radian)), (float)(b * sin(radian)), 0.0f), glm::vec4(), texCoord));
		}
	}
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(x, y, 0.0f);
}

std::vector<uint16_t> Ellipse::getIndices() const
{
	unsigned short data[EllipseIndicesBufferSize];
	for (int i = 0; i != EllipseVertexCount - 2; ++i)
	{
		int base = 3 * i;
		data[base] = 0;
		data[base + 1] = i + 1;
		data[base + 2] = i + 2;
	}
	data[EllipseIndicesBufferSize - 3] = 0;
	data[EllipseIndicesBufferSize - 2] = EllipseVertexCount - 1;
	data[EllipseIndicesBufferSize - 1] = 1;
	std::vector<uint16_t> ret(data, data + EllipseIndicesBufferSize);
	return ret;
}
