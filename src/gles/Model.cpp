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
	: Vertex(position, glm::vec4(), glm::vec2(), glm::vec3())
{
}

Vertex::Vertex(const glm::vec3 & position, const glm::vec4 & color)
	: Vertex(position, color, glm::vec2(), glm::vec3())
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

float *Mesh::positionData()
{
	return hasAttribute(Vertex::positionAttribute) ? &(m_vertexs[0].position[0]) : nullptr;
}

const float *Mesh::positionData() const
{
	return hasAttribute(Vertex::positionAttribute) ? &(m_vertexs[0].position[0]) : nullptr;
}

float *Mesh::colorData()
{
	return hasAttribute(Vertex::colorAttribute) ? &(m_vertexs[0].color[0]) : nullptr;
}

const float *Mesh::colorData() const
{
	return hasAttribute(Vertex::colorAttribute) ? &(m_vertexs[0].color[0]) : nullptr;
}

float *Mesh::textureCoordinateData()
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? &(m_vertexs[0].texCoord[0]) : nullptr;
}

const float *Mesh::textureCoordinateData() const
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? &(m_vertexs[0].texCoord[0]) : nullptr;
}

float *Mesh::normalData()
{
	return hasAttribute(Vertex::normalAttribute) ? &(m_vertexs[0].normal[0]) : nullptr;
}

const float *Mesh::normalData() const
{
	return hasAttribute(Vertex::normalAttribute) ? &(m_vertexs[0].normal[0]) : nullptr;
}

std::vector<Vertex> &Mesh::vertexs()
{
	return m_vertexs;
}

const std::vector<Vertex> &Mesh::vertexs() const
{
	return m_vertexs;
}

void Mesh::unifyColor(const glm::vec4 &color)
{
	if (!hasAttribute(Vertex::colorAttribute))	return;
	for (int i = 0; i != m_vertexs.size(); ++i)
		m_vertexs[i].color = color;
}

const std::vector<uint16_t> &Mesh::indices() const
{
	return m_indices;
}

////////////////////////class Model
Model::Model()
	: m_matrix(1.0f)
	, m_translateMatrix(1.0f)
	, m_rotateMatrix(1.0f)
	, m_scaleMatrix(1.0f)
{
}

std::vector<Mesh>& Model::meshes()
{
	return m_meshes;
}

const std::vector<Mesh>& Model::meshes() const
{
	return m_meshes;
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

glm::mat4x4 rotate_fix(glm::mat4x4 const& m, float radian, glm::vec3 const& v)
{
	float const a = radian;
	float const c = cos(a);
	float const s = sin(a);
	glm::mat4x4 Result;

	glm::vec3 axis = normalize(v);

	Result[0][0] = c + (static_cast<float>(1) - c)      * axis.x     * axis.x;
	Result[0][1] = (static_cast<float>(1) - c) * axis.x * axis.y - s * axis.z;
	Result[0][2] = (static_cast<float>(1) - c) * axis.x * axis.z + s * axis.y;
	Result[0][3] = static_cast<float>(0);

	Result[1][0] = (static_cast<float>(1) - c) * axis.y * axis.x + s * axis.z;
	Result[1][1] = c + (static_cast<float>(1) - c) * axis.y * axis.y;
	Result[1][2] = (static_cast<float>(1) - c) * axis.y * axis.z - s * axis.x;
	Result[1][3] = static_cast<float>(0);

	Result[2][0] = (static_cast<float>(1) - c) * axis.z * axis.x - s * axis.y;
	Result[2][1] = (static_cast<float>(1) - c) * axis.z * axis.y + s * axis.x;
	Result[2][2] = c + (static_cast<float>(1) - c) * axis.z * axis.z;
	Result[2][3] = static_cast<float>(0);

	Result[3] = glm::vec4(0, 0, 0, 1);
	return Result * m;
}

void Model::rotate(float angle, float x, float y, float z)
{
	m_rotateMatrix = rotate_fix(m_rotateMatrix, glm::radians(angle), glm::vec3(x, y, z));
	//如果使用rotate_slow（已经被我修改成跟自己写的一样），拖动鼠标旋转则表现为跟之前版本一致
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
