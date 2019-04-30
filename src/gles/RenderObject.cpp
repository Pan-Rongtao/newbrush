#include "gles/RenderObject.h"
#include "gles/Program.h"
#include "gles/Texture.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include "gles/Material.h"
#include "core/Matrix4x4.h"
#include <GLES2/gl2.h>
#include "gles/Model.h"
#include "gles/Storage.h"
#ifdef WIN32
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#endif

using namespace nb::core;
using namespace nb::gl;

RenderObject::RenderObject()
: m_renderable(true)
, m_storage(std::make_shared<Storage>())
{
}

RenderObject::RenderObject(bool bRenderable)
: m_renderable(bRenderable)
, m_storage(std::make_shared<Storage>())
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material)
: m_renderable(true)
, m_model(model)
, m_material(material)
, m_storage(std::make_shared<Storage>())
{
}

RenderObject::RenderObject(std::shared_ptr<Model> model, std::shared_ptr<Material> material, bool bRenderable)
: m_renderable(bRenderable)
, m_model(model)
, m_material(material)
, m_storage(std::make_shared<Storage>())
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
		printf("load [%s] fail, error:%s\r\n", path.data(), importer.GetErrorString());
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

std::shared_ptr<Material> nb::gl::RenderObject::material() const
{
	return m_material;
}

void RenderObject::setStorage(std::shared_ptr<Storage> storage)
{
	m_storage = storage;
}

std::shared_ptr<Storage> RenderObject::storage()
{
	return m_storage;
}

void RenderObject::draw() const
{
	if (!material())
		return;
	auto program = m_material->program();
	auto textures = m_material->textures();
	if (!m_renderable || !m_model || m_model->meshCount() == 0 || !m_material || !program)
		return;

	program->use();
	m_model->cullFace();
	//uniform只需更新依次即可，不必每个mesh都更新
	//计算后的mvp
	{
		Matrix4x4 matMvp = Projection::instance()->matrix() * Camera::instance()->matrix() * m_model->getMatrix();
		program->uniform(program->getUniformLocation("nb_Mvp"), matMvp);
	}
	//分开的mvp
	{
		program->uniform(program->getUniformLocation("nb_P"), Projection::instance()->matrix());
		program->uniform(program->getUniformLocation("nb_V"), Camera::instance()->matrix());
		program->uniform(program->getUniformLocation("nb_M"), m_model->getMatrix());
	}
	//storage中的uniform
	for (auto iter = m_storage->beg(); iter != m_storage->end(); ++iter)
	{
		int location = program->getUniformLocation(iter->first.data());
		const Any &v = iter->second;
		if (v.type() == typeid(bool))			program->uniform(location, any_cast<bool>(v));
		else if (v.type() == typeid(int))		program->uniform(location, any_cast<int>(v));
		else if (v.type() == typeid(float))		program->uniform(location, any_cast<float>(v));
		else if (v.type() == typeid(double))	program->uniform(location, (float)any_cast<double>(v));
		else if (v.type() == typeid(Vec2))		program->uniform(location, any_cast<Vec2>(v));
		else if (v.type() == typeid(Vec3))		program->uniform(location, any_cast<Vec3>(v));
		else if (v.type() == typeid(Vec4))		program->uniform(location, any_cast<Vec4>(v));
		else if (v.type() == typeid(Matrix2x2))	program->uniform(location, any_cast<Matrix2x2>(v));
		else if (v.type() == typeid(Matrix3x3))	program->uniform(location, any_cast<Matrix3x3>(v));
		else if (v.type() == typeid(Matrix4x4))	program->uniform(location, any_cast<Matrix4x4>(v));
	}

	//依次绘制meshs
	for (int i = 0; i != m_model->meshCount(); ++i)
	{
		const Mesh &mesh = m_model->mesh(i);
		//检查各个顶点位置、颜色、向量、纹理坐标属性，如果有则传到gpu
		if (mesh.hasAttribute(Vertex::positionAttribute))
			program->vertexAttributePointer(Program::positionLocation, Vertex::positionDimension(), 12 * sizeof(float), mesh.positionData());

		if (mesh.hasAttribute(Vertex::colorAttribute))
			program->vertexAttributePointer(Program::colorLocation, Vertex::colorDimension(), 12 * sizeof(float), mesh.colorData());

		if (mesh.hasAttribute(Vertex::normalAttribute))
			program->vertexAttributePointer(Program::normalLocation, Vertex::normalDimension(), 12 * sizeof(float), mesh.normalData());

		if (mesh.hasAttribute(Vertex::textureCoordinateAttribute) && !textures.empty())
		{
			int nTexCoord = Program::texCoordLocaltion;
			textures[0]->bind();
			program->vertexAttributePointer(nTexCoord, Vertex::textureCoordinateDimension(), 12 * sizeof(float), mesh.textureCoordinateData());
		}

		glDrawElements(GL_TRIANGLES, (int)mesh.indices().size(), GL_UNSIGNED_SHORT, mesh.indices().data());
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
		m_model->meshs().push_back(processMesh(mesh, scene));
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
		if (mesh->HasPositions())		ver.position() = Vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		if (mesh->mColors[0])			ver.color() = Vec4(mesh->mColors[0][i].r, mesh->mColors[0][i].g, mesh->mColors[0][i].b, mesh->mColors[0][i].a);
		if (mesh->mTextureCoords[0])	ver.texCoord() = nb::core::Vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		if (mesh->HasNormals())			ver.normal() = nb::core::Vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
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
	return Mesh(Vertex::positionAttribute | Vertex::colorAttribute | Vertex::textureCoordinateAttribute | Vertex::normalAttribute, vertexs, indices);
}
