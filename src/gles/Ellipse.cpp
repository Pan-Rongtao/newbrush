#include "gles/Ellipse.h"
#include <math.h>

using namespace nb::gl;
using namespace nb::core;

//椭圆的点计算公式为：x = a * cos(α); y = b * sin(α)
//顶点越多越圆滑
#define ELLIPSE_VERTEX_COUNT	50
#define ELLIPSE_INDICES_SIZE	3 * (ELLIPSE_VERTEX_COUNT - 1)
Ellipse::Ellipse(const Vec2 &center, float a, float b, bool cartesian)
{
	std::vector<Vertex> vertexs;
	//中心点
	vertexs.push_back(Vertex(Vec3(), Vec4(), Vec2(0.5, 0.5)));
	double oneRadian = (2 * nb::pi()) / (ELLIPSE_VERTEX_COUNT - 2);
	//是否是笛卡尔坐标系，顶点和纹理坐标将不同
	if (cartesian)
	{
		for (int i = 1; i != ELLIPSE_VERTEX_COUNT; ++i)
		{
			double radian = oneRadian * i;
			Vec2 texCoord((float)(0.5 * cos(radian) + 0.5), (float)(0.5 * sin(radian) + 0.5));
			vertexs.push_back(Vertex(Vec3(a * (float)cosf(radian), b * (float)sinf(radian), 0.0f), Vec4(), texCoord));
		}
	}
	else
	{
		for (int i = ELLIPSE_VERTEX_COUNT - 1; i != 0; --i)
		{
			double radian = oneRadian * i;
			Vec2 texCoord((float)(0.5 * cos(radian) + 0.5), (float)(1 - (0.5 * sin(radian) + 0.5)));
			vertexs.push_back(Vertex(Vec3((float)(a * cosf(radian)), (float)(b * sinf(radian)), 0.0f), Vec4(), texCoord));
		}
	}
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(center.x(), center.y(), 0.0f);
}

std::vector<uint16_t> Ellipse::getIndices() const
{
	unsigned short data[ELLIPSE_INDICES_SIZE];
	for (int i = 0; i != ELLIPSE_VERTEX_COUNT - 2; ++i)
	{
		int base = 3 * i;
		data[base] = 0;
		data[base + 1] = i + 1;
		data[base + 2] = i + 2;
	}
	data[ELLIPSE_INDICES_SIZE - 3] = 0;
	data[ELLIPSE_INDICES_SIZE - 2] = ELLIPSE_VERTEX_COUNT - 1;
	data[ELLIPSE_INDICES_SIZE - 1] = 1;
	std::vector<uint16_t> ret(data, data + ELLIPSE_INDICES_SIZE);
	return ret;
}
