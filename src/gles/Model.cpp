#include "gles/Model.h"
#include <GLES2/gl2.h>

using namespace nb::core;
using namespace nb::gl;

//class Vertex
Vertex::Vertex()
{
}

Vertex::Vertex(const Vec3 & position)
	: m_position(position)
{
}

nb::gl::Vertex::Vertex(const Vec3 & position, const Vec4 & color)
	: m_position(position), m_color(color)
{
}

Vertex::Vertex(const Vec3 & position, const Vec4 & color, const Vec2 & texCoord)
	: m_position(position), m_color(color), m_texCoord(texCoord)
{
}

Vertex::Vertex(const Vec3 & position, const Vec4 & color, const Vec2 & texCoord, const Vec3 & normal)
	: m_position(position)
	, m_color(color)
	, m_texCoord(texCoord)
	, m_normal(normal)
{
}

Vec3 & nb::gl::Vertex::position()
{
	return m_position;
}

const Vec3 & nb::gl::Vertex::position() const
{
	return m_position;
}

Vec4 & nb::gl::Vertex::color()
{
	return m_color;
}

const Vec4 & nb::gl::Vertex::color() const
{
	return m_color;
}

Vec2 & nb::gl::Vertex::texCoord()
{
	return m_texCoord;
}

const Vec2 & nb::gl::Vertex::texCoord() const
{
	return m_texCoord;
}

Vec3 & nb::gl::Vertex::normal()
{
	return m_normal;
}

const Vec3 & nb::gl::Vertex::normal() const
{
	return m_normal;
}

int nb::gl::Vertex::positionDimension()
{
	return 3;
}

int nb::gl::Vertex::colorDimension()
{
	return 4;
}

int nb::gl::Vertex::textureCoordinateDimension()
{
	return 2;
}

int nb::gl::Vertex::normalDimension()
{
	return 3;
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

void Mesh::setPositionAt(uint32_t vertexIndex, const Vec3 &position)
{
	if (positionData() == nullptr)
		NB_THROW_EXCEPTION(std::logic_error, "no position attribute");

	m_vertexs[vertexIndex].position() = position;
}

float *Mesh::positionData()
{
	return hasAttribute(Vertex::positionAttribute) ? m_vertexs[0].position().data() : nullptr;
}

const float *Mesh::positionData() const
{
	return hasAttribute(Vertex::positionAttribute) ? m_vertexs[0].position().data() : nullptr;
}

Vec3 Mesh::positionAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::positionAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no position attribute");

	return m_vertexs[vertexIndex].position();
}

void Mesh::setColorAt(uint32_t vertexIndex, const Vec4 &color)
{
	if (!hasAttribute(Vertex::colorAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no color attribute");

	m_vertexs[vertexIndex].color() = color;
}

float *Mesh::colorData()
{
	return hasAttribute(Vertex::colorAttribute) ? m_vertexs[0].color().data() : nullptr;
}

const float *Mesh::colorData() const
{
	return hasAttribute(Vertex::colorAttribute) ? m_vertexs[0].color().data() : nullptr;
}

Vec4 Mesh::colorAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::colorAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no color attribute");

	return m_vertexs[vertexIndex].color();
}

void Mesh::setTextureCoordinateAt(uint32_t vertexIndex, const Vec2 &texCoord)
{
	if (!hasAttribute(Vertex::textureCoordinateAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no textureCoord attribute");

	m_vertexs[vertexIndex].texCoord() = texCoord;
}

float *Mesh::textureCoordinateData()
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? m_vertexs[0].texCoord().data() : nullptr;
}

const float *Mesh::textureCoordinateData() const
{
	return hasAttribute(Vertex::textureCoordinateAttribute) ? m_vertexs[0].texCoord().data() : nullptr;
}

Vec2 Mesh::textureCoordinateAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::textureCoordinateAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no textureCoord attribute");

	return m_vertexs[vertexIndex].texCoord();
}

void Mesh::setNormalAt(uint32_t vertexIndex, const Vec3 &normal)
{
	if (!hasAttribute(Vertex::normalAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no normal attribute");

	m_vertexs[vertexIndex].normal() = normal;
}

float *Mesh::normalData()
{
	return hasAttribute(Vertex::normalAttribute) ? m_vertexs[0].normal().data() : nullptr;
}

const float *Mesh::normalData() const
{
	return hasAttribute(Vertex::normalAttribute) ? m_vertexs[0].normal().data() : nullptr;
}

Vec3 Mesh::normalAt(uint32_t vertexIndex) const
{
	if (!hasAttribute(Vertex::normalAttribute))
		NB_THROW_EXCEPTION(std::logic_error, "no normal attribute");

	return m_vertexs[vertexIndex].normal();
}

void Mesh::unifyColor(const Vec4 &color)
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
	: m_matrix(Matrix4x4::identity())
	, m_TranslateMatrix(Matrix4x4::identity())
	, m_RotateMatrix(Matrix4x4::identity())
	, m_ScaleMatrix(Matrix4x4::identity())
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

std::vector<Mesh>& nb::gl::Model::meshs()
{
	return m_meshs;
}

const std::vector<Mesh>& nb::gl::Model::meshs() const
{
	return m_meshs;
}

void Model::setMatrix(const Matrix4x4 &matrix)
{
	m_matrix = matrix;
}

const Matrix4x4 &Model::getMatrix() const
{
	return m_matrix;
}

void Model::translate(float x, float y, float z)
{
	m_TranslateMatrix.translate(x, y, z);
	m_matrix = m_TranslateMatrix * m_RotateMatrix * m_ScaleMatrix;
}

void Model::rotate(float angle, float x, float y, float z)
{
	m_RotateMatrix.rotateAngle(angle, x, y, z);
	m_matrix = m_TranslateMatrix * m_RotateMatrix * m_ScaleMatrix;
}

void Model::scale(float x, float y, float z)
{
	m_ScaleMatrix.scale(x, y, z);
	m_matrix = m_TranslateMatrix * m_RotateMatrix * m_ScaleMatrix;
}

bool Model::hitTest(int x, int y) const
{
	return false;
}

bool Model::triangleTest(const Vec3 & a, const Vec3 &b, const Vec3 &c, int x, int y) const
{
/*	CELL::Ray ray = Domain::GetInstance()->GetCamera()->GetPrivateData()->CreateRayFromScreen(x, y);
	float t, u, v;
	CELL::float4 tranVec1 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(a.x(),a.y(),a.z(),1.0);
	CELL::float4 tranVec2 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(b.x(),b.y(),b.z(), 1.0);
	CELL::float4 tranVec3 = modelMatrix().GetPrivateData()->m_matrix * CELL::float4(c.x(),c.y(),c.z(),1.0);

	CELL::float3 v1(tranVec1.x, tranVec1.y, tranVec1.z);
	CELL::float3 v2(tranVec2.x, tranVec2.y, tranVec2.z);
	CELL::float3 v3(tranVec3.x, tranVec3.y, tranVec3.z);
	return CELL::intersectTriangle<float>(ray.getOrigin(), ray.getDirection(), v1, v2, v3, &t, &u, &v);*/
	return false;
}

void Model::cullFace()
{
	glDisable(GL_CULL_FACE);
}
