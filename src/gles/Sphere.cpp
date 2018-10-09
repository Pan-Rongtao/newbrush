#include "gles/Sphere.h"
#include <vector>
#include <math.h>
#include <GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;
//球顶点算法网址：https://www.jianshu.com/p/123c5884f635;
//https://blog.csdn.net/martin20150405/article/details/53888204

#define ES_PI  (3.14159265f)
static const int vSlices = 50;									//把球按维度分成的切片数
static const int hSlices = vSlices / 2;							//经度循环为纬度切片数的一半
static const int vertextCount = (hSlices + 1) * (vSlices + 1);	//顶点数
static const int indicesCount = hSlices * vSlices * 6;			//顶点序列数
static float angleStep = (2.0f * ES_PI) / ((float)vSlices);

Sphere::Sphere(const Vec3 &centerPoint, float r, bool cartesian)
{
	std::vector<Vertex> vertexs;
	if (cartesian)
	{
		for (int i = 0; i < hSlices + 1; ++i)
		{
			for (int j = 0; j < vSlices + 1; ++j)
			{
				int index = i * (vSlices + 1) + j;
				float x = r * sinf(angleStep * (float)i) * sinf(angleStep * (float)j);
				float y = r * cosf(angleStep * (float)i);
				float z = r * sinf(angleStep * (float)i) * cosf(angleStep * (float)j);
				vertexs.push_back(Vertex(Vec3(x, y, z), Vec4(), Vec2((float)j / (float)vSlices, 1.0 - ((float)i / (float)hSlices))));
			}
		}
	}
	else
	{
		for (int i = hSlices; i != -1; --i)
		{
			for (int j = vSlices; j != -1; --j)
			{
				int index = i * (vSlices + 1) + j;
				float x = r * sinf(angleStep * (float)i) * sinf(angleStep * (float)j);
				float y = r * cosf(angleStep * (float)i);
				float z = r * sinf(angleStep * (float)i) * cosf(angleStep * (float)j);
				vertexs.push_back(Vertex(Vec3(x, y, z), Vec4(), Vec2((float)j / (float)vSlices, ((float)i / (float)hSlices))));
			}
		}
	}
	m_meshs.push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(centerPoint.x(), centerPoint.y(), centerPoint.z());
}

void Sphere::cullFace()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

std::vector<uint16_t> Sphere::getIndices() const
{
	unsigned short *data = new unsigned short[indicesCount];
	unsigned short *p = data;
	int x = 0;
	for (int i = 0; i < hSlices; i++)
	{
		for (int j = 0; j < vSlices; j++)
		{
			data[x++] = i * (vSlices + 1) + j;
			data[x++] = (i + 1) * (vSlices + 1) + j;
			data[x++] = (i + 1) * (vSlices + 1) + (j + 1);
			data[x++] = i * (vSlices + 1) + j;
			data[x++] = (i + 1) * (vSlices + 1) + (j + 1);
			data[x++] = i * (vSlices + 1) + (j + 1);
		}
	}
	std::vector<uint16_t> ret(data, data + indicesCount);
	delete[]data;
	return ret;
}
