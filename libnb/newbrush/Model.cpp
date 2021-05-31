#include "newbrush/Model.h"
#include "newbrush/Log.h"
#include "newbrush/SceneAnimator.h"
#include "assimp/cimport.h"
#include "ghc/filesystem.hpp"

using namespace nb;
using namespace AssimpView;
namespace fs = ghc::filesystem;

#define LOAD_FLAGS	aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_RemoveRedundantMaterials| aiProcess_LimitBoneWeights
//#define LOAD_FLAGS aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights

glm::mat4 toGlmMatrix(const aiMatrix4x4 &aMat)
{
	glm::mat4 mat;
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) mat[j][i] = aMat[i][j];
	return mat;
}

Model::Model()
	: m_triangleCount(0)
	, m_vertexCount(0)
	, m_curFrame(0.0f)
	, m_aScene(nullptr)
{}

Model::~Model()
{
	aiReleaseImport(m_aScene);
}

void Model::load(const std::string & path)
{
	m_triangleCount = m_vertexCount = 0;
	//使用assimp加载模型，设置纹理路径
	auto k = getMilliseconds();
	aiReleaseImport(m_aScene);
	m_aScene = aiImportFile(path.data(), LOAD_FLAGS);
	m_textureDir = fs::path(path).parent_path().string();
	auto t0 = getMilliseconds() - k;
	nbThrowExceptionIf(!m_aScene, std::runtime_error, "load [%s] fail. error message:%s", path.data(), aiGetErrorString());
	//加载模型结束

	//后解析开始
	k = getMilliseconds();
	parseMaterials();
	for (size_t i = 0; i < m_aScene->mNumMeshes; ++i)
	{
		const aiMesh *aMesh = m_aScene->mMeshes[i];
		auto nbMesh = toNBMesh(aMesh);
		m_meshes.push_back(nbMesh);
	}
	mAnimator = createRef<SceneAnimator>(m_aScene);
	auto t1 = getMilliseconds() - k;
	//后解析结束

	Log::info("load [{}] success. assimp cost [{}] ms, post handling cost [{}] ms, all cost [{}] ms. MeshCount[{}], TriangleCount[{}], VertexCount[{}]",
			path, t0, t1, t0 + t1, m_aScene->mNumMeshes, m_triangleCount, m_vertexCount);
}

bool Model::hasAnimation() const
{
	return m_aScene && m_aScene->HasAnimations();
}

void Model::play()
{
	if (hasAnimation())
	{
		uint64_t interval = (uint64_t)(m_aScene->mAnimations[0]->mTicksPerSecond != 0.0 ? m_aScene->mAnimations[0]->mTicksPerSecond : 25);
		m_timer.start(interval);
		m_timer.Tick.clear();
		m_timer.Tick += [this](const EventArgs &e)
		{
			gotoNextFrame();
		};
	}
}

void Model::pause()
{
	m_timer.stop();
}

bool Model::isPlaying() const
{
	return m_timer.isActive();
}

float Model::getFrameCount() const
{
	if (!hasAnimation())
		return 0.0f;

	return (float)m_aScene->mAnimations[0]->mDuration + 1;
}

void Model::gotoFrame(float frame)
{
	auto frameCount = getFrameCount();
	if (frameCount == 0.0f)
		return;

	nbThrowExceptionIf(frame < 0.0f && frame >= frameCount, std::out_of_range, "index[%d] is out of range[0, %d)", (int)frame, (int)frameCount);

	if (mAnimator)
	{
		mAnimator->Calculate(frame);
		m_curFrame = frame;
	}
}

void Model::gotoPrevFrame(bool reverse)
{
	auto frameCount = getFrameCount();
	if (frameCount == 0)
		return;

	auto seconds = m_timer.interval() / 1000.0f;
	auto state = m_curFrame - seconds;
	if (state <= 0.0)
		state = reverse ? frameCount * m_timer.interval() / 1000.0f : 0.0f;
	gotoFrame(state);
}

void Model::gotoNextFrame(bool reverse)
{
	auto frameCount = getFrameCount();
	if (frameCount == 0)
		return;

	auto seconds = m_timer.interval() / 1000.0f;
	auto state = m_curFrame + seconds;
	if (state >= frameCount * m_timer.interval())
		state = reverse ? 0.0f : frameCount * m_timer.interval() / 1000.0f;
	gotoFrame(state);
}

void Model::setRenderAble(const std::string & meshName, bool renderAble)
{
	for (auto mesh : m_meshes)
	{
		if(mesh->name == meshName)
			mesh->renderAble = renderAble;
	}
}

void Model::setMaterial(const std::string & meshName, ref<Material> material)
{
	for (auto mesh : m_meshes)
	{
		if (mesh->name == meshName)
			mesh->material = material;
	}
}

void Model::parseMaterials()
{
	if (!m_aScene) return;

	auto getTexture = [this](aiMaterial *aMaterial, int aType)
	{
		ref<Texture2D> tex;
		aiString originalPath;
		if (aMaterial->GetTexture((aiTextureType)aType, 0, &originalPath) == aiReturn_FAILURE)
		{
			return tex;
		}

		std::string path = m_textureDir + "/" + aiScene::GetShortFilename(originalPath.C_Str());
		auto iter = m_texturesCache.find(path);
		if (iter != m_texturesCache.end())
		{
			tex = iter->second;
		}
		else
		{
			tex = createRef<Texture2D>(path);
			if (!tex->isValid())
				Log::error("load texture [{}] fail.", path);
			m_texturesCache.insert({ path, tex });
		}
		return tex;
	};

	//C4D导出fbx有时候会丢失材质！！目前解决版本是自己构建缺失的材质
	//默认为phong（读取失败时实际上也是phong，只要有specular组件，文档上说的）
	for (auto i = 0u; i != m_aScene->mNumMaterials; ++i)
	{
		aiMaterial *aMaterial = m_aScene->mMaterials[i];
		const char *name = aMaterial->GetName().C_Str();
		aiShadingMode shadingMode = (aiShadingMode)aiShadingMode_Phong;
		aiReturn ret = aMaterial->Get(AI_MATKEY_SHADING_MODEL, shadingMode);
		switch (shadingMode)
		{
		case aiShadingMode_Phong:
		{
			//取颜色
			aiColor3D ambientColor, diffuseColor, specularColor, emissiveColor, transparentColor, reflectiveColor;
			float opacity = 1.0f, shininess = 32.0f;;
			ret = aMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
			ret = aMaterial->Get(AI_MATKEY_OPACITY, opacity);
			ret = aMaterial->Get(AI_MATKEY_SHININESS, shininess);

			//取贴图（aiTextureType_AMBIENT一般都为空，即使C4D导出的有，但它会变成aiTextureType_DIFFUSE；heigt map是高度图，一般用作地v形贴图）
			auto ambientMapping = getTexture(aMaterial, aiTextureType_AMBIENT);
			auto diffuseMapping = getTexture(aMaterial, aiTextureType_DIFFUSE);
			auto specularMapping = getTexture(aMaterial, aiTextureType_SPECULAR);
			auto emissionMapping = getTexture(aMaterial, aiTextureType_EMISSIVE);
			if (specularMapping) Log::warn("[{}] has specularMapping.", name);

			//构建材质
			auto phongMaterial = createRef<PhongMaterial>();
			phongMaterial->name = name;
			phongMaterial->ambientColor = Color::fromRgbF(ambientColor.r, ambientColor.g, ambientColor.b);
			phongMaterial->diffuseColor = Color::fromRgbF(diffuseColor.r, diffuseColor.g, diffuseColor.b);
			phongMaterial->specularColor = Color::fromRgbF(specularColor.r, specularColor.g, specularColor.b);
			phongMaterial->emissionColor = Color::fromRgbF(emissiveColor.r, emissiveColor.g, emissiveColor.b);
			phongMaterial->shineness = shininess;
			phongMaterial->diffuseMapping = diffuseMapping;
			phongMaterial->emissionMapping = emissionMapping;
			phongMaterial->opacity = opacity;

			m_materials.push_back(phongMaterial);
			break;
		}
		default: Log::error("unknown shadingMode"); break;
		}
	}
}

ref<Mesh> Model::toNBMesh(const aiMesh * aMesh)
{
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	vertexs.reserve(aMesh->mNumVertices);
	for (int i = 0; i != aMesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (aMesh->HasPositions())		ver.position = { aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z };
		if (aMesh->mColors[0])			ver.color = { aMesh->mColors[0][i].r, aMesh->mColors[0][i].g, aMesh->mColors[0][i].b, aMesh->mColors[0][i].a };
		if (aMesh->mTextureCoords[0])	ver.texCoord = { aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y };
		if (aMesh->HasNormals())		ver.normal = { aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z };
		vertexs.emplace_back(ver);
	}
	for (int i = 0; i != aMesh->mNumFaces; ++i)
	{
		aiFace face = aMesh->mFaces[i];
		for (int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	for (unsigned int i = 0; i < aMesh->mNumBones; i++) 
	{
		const aiBone* bone = aMesh->mBones[i];
		for (unsigned int k = 0; k < bone->mNumWeights; k++)
		{
			auto b = vertexs[bone->mWeights[k].mVertexId].addBone((float)i, bone->mWeights[k].mWeight);
			if (!b)
			{
				Log::error("mesh[{}]'s vertexs[{}] add bone fail, out of bone range", aMesh->mName.C_Str(), bone->mWeights[k].mVertexId);
			}
		}
	}

	auto nbMesh = createRef<Mesh>(vertexs, indices, m_materials[aMesh->mMaterialIndex]);
	nbMesh->name = aMesh->mName.C_Str();
	nbMesh->hasBone = aMesh->HasBones() && hasAnimation();

	//统计数据
	m_vertexCount += vertexs.size();
	m_triangleCount += indices.size() / 3;
	return nbMesh;
}

void Model::onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights)
{
	if (m_meshes.empty())
		return;

	auto shader = m_meshes[0]->material->shader;
	if (shader)
	{
		shader->use();
		auto const &mat = getTransform()->value();
		shader->setMat4("modelMat", mat);
		shader->disuse();
	}

	for (auto mesh : m_meshes)
	{
		if(mesh->renderAble == false)
			continue;

		auto node = m_aScene->mRootNode->FindNode(mesh->name.data());
		auto nodeMat = mAnimator->GetGlobalTransform(node);
		auto nbMat = toGlmMatrix(nodeMat);

		//上传骨骼矩阵
		if (node)
		{
			auto const &boneMats = mAnimator->GetBoneMatrices(node, 0);
			auto s = mesh->material->shader;
			s->use();
			for (auto i = 0u; i != boneMats.size(); ++i)
			{
				std::string name = "bonesMats[" + std::to_string(i) + "]";
				auto location = shader->getUniformLocation(name.data());
				glUniformMatrix4fv(location, 1, GL_TRUE, (const GLfloat*)&(boneMats[i]));
			}
			s->disuse();
		}

		mesh->draw(nbMat, camera, lights);
	}
}
