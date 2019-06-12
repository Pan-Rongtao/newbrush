#include "gles/Model.h"
#include <GLES2/gl2.h>
#include "glm/gtc/matrix_transform.hpp"

using namespace nb::core;
using namespace nb::gl;

//class Vertex
Vertex::Vertex()
{
}

Vertex::Vertex(const glm::vec3 & position)
	: m_position(position)
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color)
	: m_position(position), m_color(color)
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color, const glm::vec2 & texCoord)
	: m_position(position), m_color(color), m_texCoord(texCoord)
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color, const glm::vec2 & texCoord, const glm::vec3 & normal)
	: m_position(position)
	, m_color(color)
	, m_texCoord(texCoord)
	, m_normal(normal)
{
}

glm::vec3 &Vertex::position()
{
	return m_position;
}

const glm::vec3 &Vertex::position() const
{
	return m_position;
}

glm::vec4 &Vertex::color()
{
	return m_color;
}

const glm::vec4 &Vertex::color() const
{
	return m_color;
}

glm::vec2 &Vertex::texCoord()
{
	return m_texCoord;
}

const glm::vec2 &Vertex::texCoord() const
{
	return m_texCoord;
}

glm::vec3 &Vertex::normal()
{
	return m_normal;
}

const glm::vec3 &Vertex::normal() const
{
	return m_normal;
}

//class Mesh
Mesh::Mesh(const EnumFlags<Vertex::VertexAttribute>& attributes)
	: m_attributes(attributes)
{
}

Mesh::Mesh(const EnumFlags<Vertex::VertexAttribute>& attributes, const std::vector<Vertex>& vertexs, const std::vector<uint16_t>& indices)
	: m_attributes(attributes)
	, m_vertexs(vertexs)
	, m_indices(indices)
{
}

bool Mesh::hasAttribute(Vertex::VertexAttribute attr) const
{
	return m_attributes.testFlag(attr);
}

uint32_t Mesh::vertexCount() const
{
	return m_vertexs.size();
}

void Mesh::setPositionAt(uint32_t vertexIndex, const glm::vec3 &position)
{
	if (positionData() == nullptr)
		NB_THROW_EXCEPTION(std::logic_error, "no position attribute");

	m_vertexs[vertexIndex].position() = position;
}

float *Mesh::positionData()
{
	return hasAttribute(Vertex::positionAttribute) ? &(m_vertexs[0].position()[0]) : nullptr;
}

const float *Mesh::positionData() const
{
	return hasAttribute(Vertex::positionAttribute) ? &(m_vertexs[0].position()[0]) : nullptr;
}

glm::vec3 Mesh::positionAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::positionAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no position attribute");

	return m_vertexs[vertexIndex].position();
}

void Mesh::setColorAt(uint32_t vertexIndex, const glm::vec4 &color)
{
	if (!hasAttribute(Vertex::colorAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no color attribute");

	m_vertexs[vertexIndex].color() = color;
}

float *Mesh::colorData()
{
	return hasAttribute(Vertex::colorAttribute) ? &(m_vertexs[0].color()[0]) : nullptr;
}

const float *Mesh::colorData() const
{
	return hasAttribute(Vertex::colorAttribute) ? &(m_vertexs[0].color()[0]) : nullptr;
}

glm::vec4 Mesh::colorAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::colorAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no color attribute");

	return m_vertexs[vertexIndex].color();
}

void Mesh::setTextureCoordinateAt(uint32_t vertexIndex, const glm::vec2 &texCoord)
{
	if (!hasAttribute(Vertex::textureCoordinateAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no textureCoord attribute");

	m_vertexs[vertexIndex].texCoord() = texCoord;
}

float *Mesh::textureCoordinateData()
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? &(m_vertexs[0].texCoord()[0]) : nullptr;
}

const float *Mesh::textureCoordinateData() const
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? &(m_vertexs[0].texCoord()[0]) : nullptr;
}

glm::vec2 Mesh::textureCoordinateAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::textureCoordinateAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no textureCoord attribute");

	return m_vertexs[vertexIndex].texCoord();
}

void Mesh::setNormalAt(uint32_t vertexIndex, const glm::vec3 &normal)
{
	if (!hasAttribute(Vertex::normalAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no normal attribute");

	m_vertexs[vertexIndex].normal() = normal;
}

float *Mesh::normalData()
{
	return hasAttribute(Vertex::normalAttribute) ? &(m_vertexs[0].normal()[0]) : nullptr;
}

const float *Mesh::normalData() const
{
	return hasAttribute(Vertex::normalAttribute) ? &(m_vertexs[0].normal()[0]) : nullptr;
}

glm::vec3 Mesh::normalAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::normalAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no normal attribute");

	return m_vertexs[vertexIndex].normal();
}

void Mesh::unifyColor(const glm::vec4 &color)
{
	if (!hasAttribute(Vertex::colorAttribute))	return;
	for (int i = 0; i != vertexCount(); ++i)
		setColorAt(i, color);
}

const std::vector<uint16_t> &Mesh::indices() const
{
	return m_indices;
}

////////////////////////class Model
Model::Model()
	: m_matrix(1)
	, m_translateMatrix(1)
	, m_rotateMatrix(1)
	, m_scaleMatrix(1)
{
}

Model::~Model()
{
}

uint32_t Model::meshCount() const
{
	return m_meshs.size();
}

Mesh & Model::mesh(uint32_t index)
{
	if (index >= meshCount())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, meshCount());

	return m_meshs[index];
}

const Mesh & Model::mesh(uint32_t index) const
{
	if (index >= meshCount())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d)", index, 0, meshCount());

	return m_meshs[index];
}

std::vector<Mesh>& Model::meshs()
{
	return m_meshs;
}

const std::vector<Mesh>& Model::meshs() const
{
	return m_meshs;
}

void Model::setMatrix(const glm::mat4x4 &matrix)
{
	m_matrix = matrix;
}

const glm::mat4x4 &Model::getMatrix() const
{
	return m_matrix;
}

void Model::translate(float x, float y, float z)
{
	m_translateMatrix = glm::translate(m_translateMatrix, glm::vec3(x, y, z));
	m_matrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
}

void Model::rotate(float angle, float x, float y, float z)
{
	m_rotateMatrix = glm::rotate(m_rotateMatrix, glm::radians(angle), glm::vec3(x, y, z));
	m_matrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
}

void Model::scale(float x, float y, float z)
{
	m_scaleMatrix = glm::scale(m_scaleMatrix, glm::vec3(x, y, z));
	m_matrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix;
}

bool Model::hitTest(int x, int y) const
{
	return false;
}

bool Model::triangleTest(const glm::vec3 & a, const glm::vec3 &b, const glm::vec3 &c, int x, int y) const
{
/*	CELL::Ray ray = Domain::GetInstance()->GetCamera()->GetPrivateData()->CreateRayFromScreen(x, y);
	float t, u, v;
	CELL::float4 tranVec1 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(a.x(),a.y(),a.z(),1.0);
	CELL::float4 tranglm::vec2 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(b.x(),b.y(),b.z(), 1.0);
	CELL::float4 tranglm::vec3 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(c.x(),c.y(),c.z(),1.0);

	CELL::float3 v1(tranVec1.x, tranVec1.y, tranVec1.z);
	CELL::float3 v2(tranglm::vec2.x, tranglm::vec2.y, tranglm::vec2.z);
	CELL::float3 v3(tranglm::vec3.x, tranglm::vec3.y, tranglm::vec3.z);
	return CELL::intersectTriangle<float>(ray.getOrigin(), ray.getDirection(), v1, v2, v3, &t, &u, &v);*/
	return false;
}

void Model::cullFace()
{
	glDisable(GL_CULL_FACE);
}
