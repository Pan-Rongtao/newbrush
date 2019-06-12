#include "gles/Cube.h"
#include <GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;

Cube::Cube()
{
	std::vector<Vertex> vertexs;
	for (int i = 0; i != 8; ++i)
		vertexs.push_back(Vertex());
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
}

Cube::Cube(float x, float y, float z, float lenght, float width, float height)
{
	std::vector<Vertex> vertexs;
	vertexs.push_back(Vertex(glm::vec3(-lenght / 2, height / 2, width / 2)));
	vertexs.push_back(Vertex(glm::vec3(lenght / 2, height / 2, width / 2)));
	vertexs.push_back(Vertex(glm::vec3(lenght / 2, -height / 2, width / 2)));
	vertexs.push_back(Vertex(glm::vec3(-lenght / 2, -height / 2, width / 2)));
	vertexs.push_back(Vertex(glm::vec3(lenght / 2, height / 2, -width / 2)));
	vertexs.push_back(Vertex(glm::vec3(-lenght / 2, height / 2, -width / 2)));
	vertexs.push_back(Vertex(glm::vec3(-lenght / 2, -height / 2, -width / 2)));
	vertexs.push_back(Vertex(glm::vec3(lenght / 2, -height / 2, -width / 2)));
	meshes().push_back(Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, getIndices()));
	translate(x, y, z);
}

void Cube::cullFace()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

std::vector<uint16_t> Cube::getIndices() const
{
	uint16_t data[] = {
		3,2,1, 3,1,0,
		7,6,5, 7,5,4,
		0,5,6, 0,6,3,
		1,2,7, 1,7,4,
		0,1,5, 1,4,5,
		3,6,7, 3,7,2,
	};
	return std::vector<uint16_t>(data, data + 36);
}
