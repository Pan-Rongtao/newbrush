#include "gles/Model.h"
#include <GLES2/gl2.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/ext/matrix_projection.hpp>
#include "gles/Egl.h"

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
Mesh::Mesh()
	: Mesh({}, {})
{
}

Mesh::Mesh(const std::vector<Vertex>& vertexs, const std::vector<uint16_t>& indices)
	: m_vertexs(vertexs)
	, m_indices(indices)
{
}

Mesh::Mesh(const Mesh & other)
	: m_vertexs(other.m_vertexs)
	, m_indices(other.m_indices)
{
}

Mesh::Mesh(const Mesh && other)
	: m_vertexs(std::move(other.m_vertexs))
	, m_indices(std::move(other.m_indices))
{

}

void Mesh::operator = (const Mesh &other)
{
	m_vertexs = other.m_vertexs;
	m_indices = other.m_indices;
}

void Mesh::operator = (const Mesh &&other)
{
	m_vertexs = std::move(other.m_vertexs);
	m_indices = std::move(other.m_indices);
}

float *Mesh::positionData()
{
	return !m_vertexs.empty() ? glm::value_ptr(m_vertexs[0].position) : nullptr;
}

const float *Mesh::positionData() const
{
	return const_cast<Mesh *>(this)->positionData();
}

float *Mesh::colorData()
{
	return !m_vertexs.empty() ? glm::value_ptr(m_vertexs[0].color) : nullptr;
}

const float *Mesh::colorData() const
{
	return const_cast<Mesh *>(this)->colorData();
}

float *Mesh::textureCoordinateData()
{
	return !m_vertexs.empty() ? glm::value_ptr(m_vertexs[0].texCoord) : nullptr;
}

const float *Mesh::textureCoordinateData() const
{
	return const_cast<Mesh *>(this)->textureCoordinateData();
}

float *Mesh::normalData()
{
	return !m_vertexs.empty() ? glm::value_ptr(m_vertexs[0].normal) : nullptr;
}

const float *Mesh::normalData() const
{
	return const_cast<Mesh *>(this)->normalData();
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
	, m_mode(GL_TRIANGLES)
{
}

Model::Model(const Model & other)
	: m_matrix(other.m_matrix)
	, m_translateMatrix(other.m_translateMatrix)
	, m_rotateMatrix(other.m_rotateMatrix)
	, m_scaleMatrix(other.m_scaleMatrix)
	, m_meshes(other.m_meshes)
	, m_mode(GL_TRIANGLES)
{
}

Model::Model(const Model && other)
	: m_matrix(other.m_matrix)
	, m_translateMatrix(other.m_translateMatrix)
	, m_rotateMatrix(other.m_rotateMatrix)
	, m_scaleMatrix(other.m_scaleMatrix)
	, m_meshes(std::move(other.m_meshes))
	, m_mode(GL_TRIANGLES)
{
}

void Model::operator=(const Model & other)
{
	m_matrix = other.m_matrix;
	m_translateMatrix = other.m_translateMatrix;
	m_rotateMatrix = other.m_rotateMatrix;
	m_scaleMatrix = other.m_scaleMatrix;
	m_meshes = other.m_meshes;
	m_mode = other.m_mode;
}

void Model::operator=(const Model && other)
{
	m_matrix = other.m_matrix;
	m_translateMatrix = other.m_translateMatrix;
	m_rotateMatrix = other.m_rotateMatrix;
	m_scaleMatrix = other.m_scaleMatrix;
	m_meshes = std::move(other.m_meshes);
	m_mode = other.m_mode;
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

//https://stackoverflow.com/questions/29997209/opengl-c-mouse-ray-picking-glmunproject
bool Model::sightHitTest(float xNormalized, float yNormalized) const
{
	glm::mat4 invVP = glm::inverse(nb::gl::getProjection()->matrix() * nb::gl::getCamera()->matrix());
	glm::vec4 screenPos = glm::vec4(xNormalized, -yNormalized, 1.0f, 1.0f);
	glm::vec4 worldPos = invVP * screenPos;
	glm::vec3 raypos = nb::gl::getCamera()->posotion();
	glm::vec3 raydir = glm::normalize(glm::vec3(worldPos));
	return intersect(raypos, raydir);
}

bool Model::orthoHitTest(float x, float y)
{
	glm::vec3 raypos(x, y, 10000.0f);
	glm::vec3 raydir(0.0f, 0.0f, -1.0f);
	return intersect(raypos, raydir);
}

void Model::cullFace()
{
	glDisable(GL_CULL_FACE);
}

void Model::setDrawMode(unsigned int mode)
{
	m_mode = mode;
}

unsigned int Model::drawMode() const
{
	return m_mode;
}

glm::mat4x4 Model::rotate_fix(glm::mat4x4 const& m, float radian, glm::vec3 const& v)
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

bool Model::intersect(const glm::vec3 & raypos, const glm::vec3 & raydir) const
{
	for (auto const &mesh : meshes())
	{
		auto idxs = mesh.indices();
		for (auto i = 0u; i + 3 <= mesh.indices().size(); i += 3)
		{
			auto p0 = mesh.vertexs()[idxs[i + 0]].position;
			auto p1 = mesh.vertexs()[idxs[i + 1]].position;
			auto p2 = mesh.vertexs()[idxs[i + 2]].position;
			glm::vec2 bary;
			float d;
			auto m = getMatrix();
			if (glm::intersectRayTriangle(raypos, raydir, glm::vec3(m * glm::vec4(p0, 1.0)), glm::vec3(m * glm::vec4(p1, 1.0)), glm::vec3(m * glm::vec4(p2, 1.0)), bary, d))
				return true;
		}
	}
	return false;
}
