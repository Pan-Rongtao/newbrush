#include "newbrush/Mesh.h"
#include "newbrush/GLUnit.h"
#include "newbrush/Camera.h"
#include "newbrush/Light.h"
#include "newbrush/Material.h"
#include "newbrush/Shader.h"

using namespace nb;

Mesh::Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, ref<Material> materia)
	: material(materia)
	, vao(0)
	, vbo(0)
	, ebo(0)
{
	setup(vertexs, indices);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Mesh::drawFlags() const
{
	glDisable(GL_CULL_FACE);
//	glDepthFunc(GL_LESS);
}

void Mesh::draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>>& lights) const
{
	if (!material || !material->shader)
		return;

	auto shader = material->shader;
	shader->use();
	drawFlags();

	//计算后的mvp，以及分开的m/v/p
	auto const &m = matrix;
	auto const &vp = camera->getViewProjectionMatrix();

	shader->setMat4("nbM", m);
	shader->setMat4("nbVP", vp);

	//材质更新uniforms
	material->uploadUniform(camera);

	//灯光更新uniforms
	for (auto const &light : lights)
	{
		if(light) light->uploadUniform(shader);
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(0);

	shader->disuse();
}

void Mesh::setup(const std::vector<Vertex>& vertexs, const std::vector<uint16_t>& indices)
{
	if (vertexs.empty() || indices.empty())
		return;

	//vao begin
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vbo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexs.size(), &vertexs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));	//position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));	//color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));	//texture
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));	//normal
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//ebo
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int16_t), &indices[0], GL_STATIC_DRAW);

	//end vao
	glBindVertexArray(0);

	indicesSize = indices.size();
}

//////////////
Cube::Cube()
	: Cube(glm::vec3(0.0f), 1.0f)
{
}

Cube::Cube(const glm::vec3 & center, float uniformLenght)
	: Cube(center, uniformLenght, uniformLenght, uniformLenght)
{
}

Cube::Cube(const glm::vec3 &center, float lenght, float width, float height)
	: Mesh({}, {}, nullptr)
{
	auto vertexs =
	{
		//前一个面（四个点，左上前，右上前，左下前，右下前）
		Vertex{ glm::vec3(-lenght / 2, height / 2, width / 2) },
		Vertex{ glm::vec3(lenght / 2, height / 2, width / 2) },
		Vertex{ glm::vec3(lenght / 2, -height / 2, width / 2) },
		Vertex{ glm::vec3(-lenght / 2, -height / 2, width / 2) },
		//后一个面（四个点，左上后，右上后，右下后，左下后）
		Vertex{ glm::vec3(-lenght / 2, height / 2, -width / 2) },
		Vertex{ glm::vec3(lenght / 2, height / 2, -width / 2) },
		Vertex{ glm::vec3(lenght / 2, -height / 2, -width / 2) },
		Vertex{ glm::vec3(-lenght / 2, -height / 2, -width / 2) }
	};
	//上下左右前后
	std::vector<uint16_t> indices =
	{
		1,4,5, 1,0,4,	//top
		7,3,2, 7,2,6,	//bottom
		0,3,7, 0,7,4,	//left
		1,5,2, 5,6,2,	//right
		0,1,2, 0,2,3,	//front
		4,6,5, 4,7,6,	//back
	};
	setup(vertexs, indices);
}

//////////////////////////
SkyBox::SkyBox()
	: Cube(glm::vec3(0.0f), 1.0f)	//天空盒的尺寸是无影响的，因为shader中使用w替代z
{
}

void SkyBox::drawFlags() const
{
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
}

void SkyBox::draw(const glm::mat4 &matrix, ref<Camera> camera, const std::vector<ref<Light>>& lights) const
{
	auto cm = createRef<PerspectiveCamera>(*(nb::as<PerspectiveCamera>(camera).get()));
	cm->setTranslate(glm::vec3(0.0, 0.0, 0.0));
	Mesh::draw(matrix, cm, lights);
}
