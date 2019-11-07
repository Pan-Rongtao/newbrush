#include "gles/Model.h"
#include <GLES2/gl2.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/ext/matrix_projection.hpp>
#include "gles/Egl.h"

using namespace nb;
using namespace nb::gl;

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
	: vertexs(vertexs)
	, indices(indices)
{
}

Mesh::Mesh(const Mesh & other)
	: vertexs(other.vertexs)
	, indices(other.indices)
{
}

Mesh::Mesh(const Mesh && other)
	: vertexs(std::move(other.vertexs))
	, indices(std::move(other.indices))
{

}

void Mesh::operator = (const Mesh &other)
{
	vertexs = other.vertexs;
	indices = other.indices;
}

void Mesh::operator = (const Mesh &&other)
{
	vertexs = std::move(other.vertexs);
	indices = std::move(other.indices);
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

////////////////////////class Model
Model::Model()
	: matrix(1.0f)
	, mode(GL_TRIANGLES)
{
}

Model::Model(const Model & other)
	: matrix(other.matrix)
	, meshes(other.meshes)
	, mode(GL_TRIANGLES)
{
}

Model::Model(const Model && other)
	: matrix(std::move(other.matrix))
	, meshes(std::move(other.meshes))
	, mode(GL_TRIANGLES)
{
}

void Model::operator=(const Model & other)
{
	matrix = other.matrix;
	meshes = other.meshes;
	mode = other.mode;
}

void Model::operator=(const Model && other)
{
	matrix = std::move(other.matrix);
	meshes = std::move(other.meshes);
	mode = other.mode;
}

void Model::preprocess()
{
	glDisable(GL_CULL_FACE);
}

//https://stackoverflow.com/questions/29997209/opengl-c-mouse-ray-picking-glmunproject
bool Model::sightHitTest(float xNormalized, float yNormalized) const
{
	glm::mat4 invVP = glm::inverse(nb::gl::getProjection()->matrix * nb::gl::getCamera()->matrix);
	glm::vec4 screenPos = glm::vec4(xNormalized, -yNormalized, 1.0f, 1.0f);
	glm::vec4 worldPos = invVP * screenPos;
	glm::vec3 raypos = nb::gl::getCamera()->position();
	glm::vec3 raydir = glm::normalize(glm::vec3(worldPos));
	return intersect(raypos, raydir);
}

bool Model::orthoHitTest(float x, float y) const
{
	glm::vec3 raypos(x, y, 10000.0f);
	glm::vec3 raydir(0.0f, 0.0f, -1.0f);
	return intersect(raypos, raydir);
}

bool Model::intersect(const glm::vec3 & raypos, const glm::vec3 & raydir) const
{
	for (auto const &mesh : meshes)
	{
		const auto &idxs = mesh.indices;
		for (auto i = 0u; i + 3 <= idxs.size(); i += 3)
		{
			auto p0 = mesh.vertexs[idxs[i + 0]].position;
			auto p1 = mesh.vertexs[idxs[i + 1]].position;
			auto p2 = mesh.vertexs[idxs[i + 2]].position;
			glm::vec2 bary;
			float d;
			if (glm::intersectRayTriangle(raypos, raydir, glm::vec3(matrix * glm::vec4(p0, 1.0)), glm::vec3(matrix * glm::vec4(p1, 1.0)), glm::vec3(matrix * glm::vec4(p2, 1.0)), bary, d))
				return true;
		}
	}
	return false;
}
