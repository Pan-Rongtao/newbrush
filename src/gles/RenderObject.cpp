#include "gles/RenderObject.h"
#include <GLES2/gl2.h>
#include "gles/Camera.h"
#include "gles/Projection.h"
#include "gles/Egl.h"
#include "core/Log.h"
#ifdef WIN32
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#endif

using namespace nb;
using namespace nb::gl;

RenderObject::RenderObject()
	: RenderObject(nullptr, nullptr, true)
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model)
	: RenderObject(model, nullptr, true)
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material)
	: RenderObject(model, material, true)
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material, bool bRenderable)
	: m_renderable(bRenderable)
	, m_model(model)
	, m_material(material)
{
}

void RenderObject::loadFromFile(const std::string & path)
{
#ifdef WIN32
	m_model = std::make_shared<Model>();
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Log::error("load [%s] fail:%s", path.data(), importer.GetErrorString());
		return;
	}

	loopNode(scene->mRootNode, scene);
#endif
}

void RenderObject::setRenderable(bool bRenderable)
{
	m_renderable = bRenderable;
}

bool RenderObject::renderable() const
{
	return m_renderable;
}

void RenderObject::setModel(std::shared_ptr<Model> model)
{
	m_model = model;
}

std::shared_ptr<Model> RenderObject::model()
{
	return m_model;
}

void RenderObject::setMaterial(std::shared_ptr<Material> material)
{
	m_material = material;
}

std::shared_ptr<Material> RenderObject::material()
{
	return m_material;
}

void RenderObject::storeUniform(const std::string & name, const Any & v)
{
	m_uniforms[name] = v;
}

void RenderObject::draw() const
{
	if (!m_renderable || !m_model || m_model->meshes.empty() || !m_material || !m_material->program())
		return;

	auto program = m_material->program();
	auto textures = m_material->textures();
	program->use();
	m_model->preprocess();
	//计算后的mvp，以及分开的m/v/p
	{
		auto const &m = m_model->matrix;
		auto const &v = nb::gl::getCamera()->matrix;
		auto const &p = nb::gl::getProjection()->matrix;
		auto mvp = p * v * m;
		program->uniform(program->getUniformLocation(Program::nbMvpStr), mvp);
		program->uniform(program->getUniformLocation(Program::nbMStr), m);
		program->uniform(program->getUniformLocation(Program::nbVStr), v);
		program->uniform(program->getUniformLocation(Program::nbPStr), p);
	}
	//storage中的uniform
	for (auto const &iter : m_uniforms)
	{
		auto location = program->getUniformLocation(iter.first.data());
		auto const &v = iter.second;
		if (v.type() == typeid(bool))							program->uniform(location, any_cast<bool>(v));
		else if (v.type() == typeid(int))						program->uniform(location, any_cast<int>(v));
		else if (v.type() == typeid(float))						program->uniform(location, any_cast<float>(v));
		else if (v.type() == typeid(double))					program->uniform(location, (float)any_cast<double>(v));
		else if (v.type() == typeid(glm::vec2))					program->uniform(location, any_cast<glm::vec2>(v));
		else if (v.type() == typeid(glm::vec3))					program->uniform(location, any_cast<glm::vec3>(v));
		else if (v.type() == typeid(glm::vec4))					program->uniform(location, any_cast<glm::vec4>(v));
		else if (v.type() == typeid(glm::mat2x2))				program->uniform(location, any_cast<glm::mat2x2>(v));
		else if (v.type() == typeid(glm::mat3x3))				program->uniform(location, any_cast<glm::mat3x3>(v));
		else if (v.type() == typeid(glm::mat4x4))				program->uniform(location, any_cast<glm::mat4x4>(v));
		else if (v.type() == typeid(glm::ivec2))				program->uniform(location, any_cast<glm::ivec2>(v));
		else if (v.type() == typeid(glm::ivec3))				program->uniform(location, any_cast<glm::ivec3>(v));
		else if (v.type() == typeid(glm::ivec4))				program->uniform(location, any_cast<glm::ivec4>(v));
		else if (v.type() == typeid(std::vector<int>))			program->uniform(location, any_cast<std::vector<int>>(v));
		else if (v.type() == typeid(std::vector<float>))		program->uniform(location, any_cast<std::vector<float>>(v));
		else if (v.type() == typeid(std::vector<glm::vec2>))	program->uniform(location, any_cast<std::vector<glm::vec2>>(v));
		else if (v.type() == typeid(std::vector<glm::vec3>))	program->uniform(location, any_cast<std::vector<glm::vec3>>(v));
		else if (v.type() == typeid(std::vector<glm::vec4>))	program->uniform(location, any_cast<std::vector<glm::vec4>>(v));
		else if (v.type() == typeid(std::vector<glm::mat2x2>))	program->uniform(location, any_cast<std::vector<glm::mat2x2>>(v));
		else if (v.type() == typeid(std::vector<glm::mat3x3>))	program->uniform(location, any_cast<std::vector<glm::mat3x3>>(v));
		else if (v.type() == typeid(std::vector<glm::mat4x4>))	program->uniform(location, any_cast<std::vector<glm::mat4x4>>(v));
		else if (v.type() == typeid(std::vector<glm::ivec2>))	program->uniform(location, any_cast<std::vector<glm::ivec2>>(v));
		else if (v.type() == typeid(std::vector<glm::ivec3>))	program->uniform(location, any_cast<std::vector<glm::ivec3>>(v));
		else if (v.type() == typeid(std::vector<glm::ivec4>))	program->uniform(location, any_cast<std::vector<glm::ivec4>>(v));
		else													Log::warn("%s is not a supported type for glsl.", v.type().name());
		
	}

	//依次绘制meshs
	for (auto const &mesh : m_model->meshes)
	{
		program->vertexAttributePointer(Program::nbPositionLocation, Vertex::positionDimension, Vertex::stride, mesh.positionData());
		program->vertexAttributePointer(Program::nbColorLocation, Vertex::colorDimension, Vertex::stride, mesh.colorData());
		program->vertexAttributePointer(Program::nbNormalLocation, Vertex::normalDimension, Vertex::stride, mesh.normalData());
		if (!textures.empty())
		{
			textures[0]->bind();
			program->vertexAttributePointer(Program::nbTexCoordLocaltion, Vertex::texCoordDimension, Vertex::stride, mesh.textureCoordinateData());
		}

		glDrawElements(m_model->mode, (int)mesh.indices.size(), GL_UNSIGNED_SHORT, mesh.indices.data());
		if (!textures.empty())
			textures[0]->unbind();
	}

	program->disuse();
}

void RenderObject::loopNode(aiNode * node, const aiScene * scene)
{
#ifdef WIN32
	for (int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_model->meshes.push_back(processMesh(mesh, scene));
	}
	for (int i = 0; i != node->mNumChildren; ++i)
		loopNode(node->mChildren[i], scene);
#endif
}

Mesh RenderObject::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
#ifdef WIN32
	for (int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (mesh->HasPositions())		ver.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
		if (mesh->mColors[0])			ver.color = { mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a };
		if (mesh->mTextureCoords[0])	ver.texCoord = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		if (mesh->HasNormals())			ver.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
		vertexs.push_back(ver);
	}

	for (int i = 0; i != mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
#endif
	return Mesh(vertexs, indices);
}
