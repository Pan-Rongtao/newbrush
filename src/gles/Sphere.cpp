#include "gles/Sphere.h"
#include <vector>
#include <math.h>
#include <GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;
//球顶点算法网址：
//https://www.jianshu.com/p/123c5884f635;
//https://blog.csdn.net/martin20150405/article/details/53888204

constexpr int vSlices = 50;										//把球按维度分成的切片数
constexpr int hSlices = vSlices / 2;							//经度循环为纬度切片数的一半
constexpr int vertextCount = (hSlices + 1) * (vSlices + 1);		//顶点数
constexpr int indicesCount = hSlices * vSlices * 6;				//顶点序列数
constexpr double angleStep = (2.0f * NB_PI) / ((float)vSlices);	//每个扇形的角度

Sphere::Sphere(float x, float y, float z, float r, bool cartesian)
{
	std::vector<Vertex> vertexs;
	if (cartesian)
	{
		for (int i = 0; i < hSlices + 1; ++i)
		{
			for (int j = 0; j < vSlices + 1; ++j)
			{
				int index = i * (vSlices + 1) + j;
				float x = (float)(r * sin(angleStep * i) * sin(angleStep * j));
				float y = (float)(r * cos(angleStep * i));
				float z = (float)(r * sin(angleStep * i) * cos(angleStep * j));
				vertexs.push_back(Vertex(glm::vec3(x, y, z), glm::vec4(), glm::vec2((float)j / (float)vSlices, 1.0f - ((float)i / (float)hSlices))));
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
				float x = (float)(r * sin(angleStep * (float)i) * sin(angleStep * (float)j));
				float y = (float)(r * cos(angleStep * (float)i));
				float z = (float)(r * sin(angleStep * (float)i) * cos(angleStep * (float)j));
				vertexs.push_back(Vertex(glm::vec3(x, y, z), glm::vec4(), glm::vec2((float)j / (float)vSlices, ((float)i / (float)hSlices))));
			}
		}
	}
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(x, y, z);
}

void Sphere::cullFace()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

std::vector<uint16_t> Sphere::getIndices() const
{
	unsigned short data[indicesCount];
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
	return ret;
}
