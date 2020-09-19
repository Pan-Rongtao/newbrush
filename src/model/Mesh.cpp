#include "newbrush/model/Mesh.h"
#include <GLES2/gl2.h>

using namespace nb;

//class Vertex
Vertex::Vertex()
{
}

Vertex::Vertex(const glm::vec3 & position)
	: Vertex(position, glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(), glm::vec3())
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color)
	: Vertex(position, color, glm::vec2(), glm::vec3())
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec2 & texCoord)
	: Vertex(position, glm::vec4(0.0, 0.0, 0.0, 1.0), texCoord, glm::vec3())
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color, const glm::vec2 & texCoord)
	: Vertex(position, color, texCoord, glm::vec3())
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color, const glm::vec2 & texCoord, const glm::vec3 & normal)
	: position(position)
	, color(color)
	, texCoord(texCoord)
	, normal(normal)
{
}

//class Mesh
Mesh::Mesh()
	: Mesh({}, {}, nullptr)
{
}

Mesh::Mesh(const std::vector<Vertex>& _vertexs, const std::vector<uint16_t>& _indices)
	: Mesh(_vertexs, _indices, nullptr)
{
}

Mesh::Mesh(const std::vector<Vertex> &vertexs, const std::vector<uint16_t> &indices, MaterialPtr materia)
	: vertexs(vertexs)
	, indices(indices)
	, material(materia)
	, matrix(1.0f)
	, mode(GL_TRIANGLES)
{
}

Mesh::Mesh(const Mesh & other)
	: vertexs(other.vertexs)
	, indices(other.indices)
	, material(other.material)
	, matrix(other.matrix)
	, mode(other.mode)
{
}

Mesh::Mesh(const Mesh && other)
	: vertexs(std::move(other.vertexs))
	, indices(std::move(other.indices))
	, material(std::move(other.material))
	, matrix(std::move(other.matrix))
	, mode(std::move(other.mode))
{
}

void Mesh::operator = (const Mesh &other)
{
	vertexs = other.vertexs;
	indices = other.indices;
	material = other.material;
	matrix = other.matrix;
	mode = other.mode;
}

void Mesh::operator = (const Mesh &&other)
{
	vertexs = std::move(other.vertexs);
	indices = std::move(other.indices);
	material = std::move(other.material);
	matrix = std::move(other.matrix);
	mode = std::move(other.mode);
}

float *Mesh::positionData()
{
	return !vertexs.empty() ? glm::value_ptr(vertexs[0].position) : nullptr;
}

const float *Mesh::positionData() const
{
	return const_cast<Mesh *>(this)->positionData();
}

float *Mesh::colorData()
{
	return !vertexs.empty() ? glm::value_ptr(vertexs[0].color) : nullptr;
}

const float *Mesh::colorData() const
{
	return const_cast<Mesh *>(this)->colorData();
}

float *Mesh::textureCoordinateData()
{
	return !vertexs.empty() ? glm::value_ptr(vertexs[0].texCoord) : nullptr;
}

const float *Mesh::textureCoordinateData() const
{
	return const_cast<Mesh *>(this)->textureCoordinateData();
}

float *Mesh::normalData()
{
	return !vertexs.empty() ? glm::value_ptr(vertexs[0].normal) : nullptr;
}

const float *Mesh::normalData() const
{
	return const_cast<Mesh *>(this)->normalData();
}

void Mesh::unifyColor(const glm::vec4 &color)
{
	for (auto &vertex : vertexs)
		vertex.color = color;
}

uint32_t Mesh::triangleCount() const
{
	return indices.size() / 3;
}

void Mesh::draw(CameraPtr camera, const std::vector<LightPtr>& lights) const
{
	if (!material || !material->program())
		return;

	auto program = material->program();
	program->use();

	//更新顶点数据
	program->vertexAttributePointer(Program::nbPositionLocation, Vertex::positionDimension, Vertex::stride, positionData());
	program->vertexAttributePointer(Program::nbColorLocation, Vertex::colorDimension, Vertex::stride, colorData());
	program->vertexAttributePointer(Program::nbNormalLocation, Vertex::normalDimension, Vertex::stride, normalData());
	program->vertexAttributePointer(Program::nbTexCoordLocaltion, Vertex::texCoordDimension, Vertex::stride, textureCoordinateData());
	//计算后的mvp，以及分开的m/v/p
	auto m = matrix;
	auto v = camera->viewMatrix();
	auto p = camera->projectionMatrix();
	auto mvp = p * v * m;
	program->uniform(program->getUniformLocation(Program::nbMvpStr), mvp);
	program->uniform(program->getUniformLocation(Program::nbMStr), m);
	program->uniform(program->getUniformLocation(Program::nbVStr), v);
	program->uniform(program->getUniformLocation(Program::nbPStr), p);

	//材质更新uniforms
	material->uploadUniform(camera);

	//灯光更新uniforms
	for (auto const &light : lights)
	{
		auto uniformPairs = light->toUniforms();
		for (auto const &one : uniformPairs)
		{
			auto location = program->getUniformLocation(one.first.data());
			auto const &v = one.second;
			program->uniformVar(location, v);
		}
	}

	glDrawElements(mode, indices.size(), GL_UNSIGNED_SHORT, indices.data());
	program->disuse();
}
