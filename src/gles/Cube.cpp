#include "newbrush/gles/Cube.h"
#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace nb;

Cube::Cube()
	: Cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
{}

Cube::Cube(float x, float y, float z, float lenght, float width, float height)
{
	std::vector<Vertex> vertexs{
		Vertex(glm::vec3(-lenght / 2, height / 2, width / 2)),
		Vertex(glm::vec3(lenght / 2, height / 2, width / 2)),
		Vertex(glm::vec3(lenght / 2, -height / 2, width / 2)),
		Vertex(glm::vec3(-lenght / 2, -height / 2, width / 2)),
		Vertex(glm::vec3(lenght / 2, height / 2, -width / 2)),
		Vertex(glm::vec3(-lenght / 2, height / 2, -width / 2)),
		Vertex(glm::vec3(-lenght / 2, -height / 2, -width / 2)),
		Vertex(glm::vec3(lenght / 2, -height / 2, -width / 2))
	};
	meshes.push_back(Mesh(vertexs, {
		3,2,1, 3,1,0,
		7,6,5, 7,5,4,
		0,5,6, 0,6,3,
		1,2,7, 1,7,4,
		0,1,5, 1,4,5,
		3,6,7, 3,7,2, }));
	matrix = glm::translate(matrix, glm::vec3(x, y, z));
}

void Cube::preprocess()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}
