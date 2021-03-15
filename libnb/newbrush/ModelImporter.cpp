#include "newbrush/ModelImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "newbrush/Log.h"
#include "newbrush/Texture.h"
#include "newbrush/Helper.h"

using namespace nb;

#define LOAD_FLAGS	aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices
//#define LOAD_FLAGS aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights

glm::mat4 convertMatrix(const aiMatrix4x4 &aMat)
{
	glm::mat4 mat;
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) mat[j][i] = aMat[i][j];

	return mat;
}

ModelImporter::ModelImporter()
	: m_importer(createRef<Assimp::Importer>())
	, m_meshCount(0)
	, m_triangleCount(0)
	, m_vertexCount(0)
{
}

ModelImporter::~ModelImporter()
{
	m_importer->FreeScene();
}

void ModelImporter::load(const std::string & path)
{
	auto k = getMilliseconds();
	m_importer->ReadFile(path, LOAD_FLAGS);
	m_textureDir = getParentDir(path);
	auto t0 = nb::getMilliseconds() - k;

	k = getMilliseconds();
	handling();
	auto t1 = nb::getMilliseconds() - k;

	if (m_importer->GetScene())
	{
		Log::info("load [{}] success. assimp cost {} ms, post handling cost {} ms, all cost {} ms. MeshCount={}, TriangleCount={}, VertexCount={}", 
			path, t0, t1, t0 + t1, getMeshCount(), getTriangleCount(), getVertexCount());
	}
	else
	{
		nbThrowException(std::runtime_error, "load [%s] fail. error message:%s", path.data(), m_importer->GetErrorString());
	}
	m_path = path;
}

const std::string & ModelImporter::path() const
{
	return m_path;
}

const ref<Node> & ModelImporter::getRoot() const
{
	return m_root;
}

const std::vector<ref<Light>>& ModelImporter::getLights() const
{
	return m_lights;
}

const std::vector<ref<Material>>& ModelImporter::getMaterials() const
{
	return m_materials;
}

const std::vector<ref<Storyboard>>& ModelImporter::getAnimations() const
{
	return m_animations;
}

int32_t ModelImporter::getMeshCount() const
{
	return m_meshCount;
}

int32_t ModelImporter::getTriangleCount() const
{
	return m_triangleCount;
}

int32_t ModelImporter::getVertexCount() const
{
	return m_vertexCount;
}

void ModelImporter::handling()
{
	m_meshCount = m_triangleCount = m_vertexCount = 0;
	auto scene = m_importer->GetScene();
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return;
	}

	handleCamearas(scene);
	handleLights(scene);
	handleMaterials(scene);
	handleNodes(scene);
	handleAnimations(scene);
}

void ModelImporter::handleCamearas(const aiScene *scene)
{
	for (auto i = 0u; i != scene->mNumCameras; ++i)
	{
		aiCamera *aCamera = scene->mCameras[i];
		aiMatrix4x4 matrix;
		aCamera->GetCameraMatrix(matrix);
		glm::vec3 position = { aCamera->mPosition.x, aCamera->mPosition.y, 3.0 };
		glm::vec3 lookDirection = { aCamera->mLookAt.x, aCamera->mLookAt.y, aCamera->mLookAt.z };
		glm::vec3 up = { aCamera->mUp.x, aCamera->mUp.y, aCamera->mUp.z };
		//auto nbCamera = createRef<Camera>(position, lookDirection, up, 0.0f, -90.0f, aCamera->mHorizontalFOV, aCamera->mAspect, aCamera->mClipPlaneNear, aCamera->mClipPlaneFar);
		//m_cameras.push_back(nbCamera);
	}
}

void ModelImporter::handleLights(const aiScene *scene)
{
	for (auto i = 0u; i != scene->mNumLights; ++i)
	{
		aiLight *aLight = scene->mLights[i];
		switch (aLight->mType)
		{
		case aiLightSource_AMBIENT:
		{
			auto ambientLight = createRef<AmbientLight>();
			ambientLight->name = aLight->mName.C_Str();
			ambientLight->ambient = Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b);
			ambientLight->diffuse = Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b);
			ambientLight->specular = Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b);
			m_lights.push_back(ambientLight);
			break;
		}
		case aiLightSource_DIRECTIONAL:
		{
			auto directionalLight = createRef<DirectionalLight>();
			directionalLight->name = aLight->mName.C_Str();
			directionalLight->ambient = Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b);
			directionalLight->diffuse = Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b);
			directionalLight->specular = Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b);
			directionalLight->direction = { aLight->mDirection.x, aLight->mDirection.y, aLight->mDirection.z };
			m_lights.push_back(directionalLight);
			break;
		}
		case aiLightSource_POINT:
		{
			auto pointLight = createRef<PointLight>();
			pointLight->name = aLight->mName.C_Str();
			pointLight->ambient = Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b);
			pointLight->diffuse = Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b);
			pointLight->specular = Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b);
			pointLight->position = /*{ aLight->mPosition.x, aLight->mPosition.y, aLight->mPosition.z }*/glm::vec3(0.0f, 5.0f, 5.0f); //assimp读取到的都是{0,0,0}
			pointLight->linearAttenuation = aLight->mAttenuationLinear;
			pointLight->constantAttenuation = aLight->mAttenuationConstant;
			pointLight->quadraticAttenuation = aLight->mAttenuationQuadratic;
			m_lights.push_back(pointLight); 
			break;
		}
		case aiLightSource_SPOT:
		{
			auto spotLight = createRef<SpotLight>();
			spotLight->name = aLight->mName.C_Str();
			spotLight->ambient = Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b);
			spotLight->diffuse = Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b);
			spotLight->specular = Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b);
			spotLight->position = /*{ aLight->mPosition.x, aLight->mPosition.y, aLight->mPosition.z }*/glm::vec3(0.0f, 5.0f, 5.0f); //assimp读取到的都是{0,0,0}
			spotLight->linearAttenuation = aLight->mAttenuationLinear;
			spotLight->constantAttenuation = aLight->mAttenuationConstant;
			spotLight->quadraticAttenuation = aLight->mAttenuationQuadratic;
			spotLight->direction = { aLight->mDirection.x, aLight->mDirection.y, aLight->mDirection.z };
			spotLight->innerConeAngle = aLight->mAngleInnerCone;
			spotLight->outerConeAngle = aLight->mAngleOuterCone;
			m_lights.push_back(spotLight);
			break;
		}
		default: Log::error("aiLightSource_UNDEFINED"); break;
		}
	}
}

void ModelImporter::handleMaterials(const aiScene *scene)
{
	for (auto i = 0u; i != scene->mNumMaterials; ++i)
	{
		aiMaterial *aMaterial = scene->mMaterials[i];

		aiShadingMode shadingMode = (aiShadingMode)aiShadingMode_Phong;	//默认为phong（读取失败时实际上也是phong，只要有specular组件，文档上说的）
		aiReturn ret = aMaterial->Get(AI_MATKEY_SHADING_MODEL, shadingMode);
		switch (shadingMode)
		{
		case aiShadingMode_Phong:
		{
			//取颜色
			aiColor3D ambientColor, diffuseColor, specularColor, emissiveColor, transparentColor, reflectiveColor;
			float opacity = 1.0f;
			ret = aMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
			ret = aMaterial->Get(AI_MATKEY_OPACITY, opacity);
			
			//取贴图（heigt map是高度图，一般用作地形贴图）
			auto diffuseMapping = getTexture(aMaterial, aiTextureType_DIFFUSE);
			auto specularMapping = getTexture(aMaterial, aiTextureType_SPECULAR);
			auto emissionMapping = getTexture(aMaterial, aiTextureType_EMISSIVE);
			if (specularMapping) Log::info("[{}] has specularMapping.", aMaterial->GetName().C_Str());
			if (emissionMapping) Log::info("[{}] has emissionMapping.", aMaterial->GetName().C_Str());

			//其他
			float shininess = 32.0f;
			ret = aMaterial->Get(AI_MATKEY_SHININESS, shininess);

			//构建材质
			auto phongMaterial = createRef<PhongMaterial>();
			phongMaterial->name = aMaterial->GetName().C_Str();
			phongMaterial->ambient = Color::fromRgbF(ambientColor.r, ambientColor.g, ambientColor.b);
			phongMaterial->diffuse = Color::fromRgbF(diffuseColor.r, diffuseColor.g, diffuseColor.b);
			phongMaterial->specular = Color::fromRgbF(specularColor.r, specularColor.g, specularColor.b);
			phongMaterial->emission = Color::fromRgbF(emissiveColor.r, emissiveColor.g, emissiveColor.b);
			phongMaterial->shineness = shininess;
			phongMaterial->diffuseMapping = diffuseMapping;
			phongMaterial->opacity = opacity;

			m_materials.push_back(phongMaterial);
			break;
		}
		default: Log::error("unknown shadingMode"); break;
		}
	}
}

void ModelImporter::handleAnimations(const aiScene *scene)
{
	for (auto i = 0u; i != scene->mNumAnimations; ++i)
	{
		auto aAnimation = scene->mAnimations[i];
		auto duration = aAnimation->mDuration * aAnimation->mTicksPerSecond;

		auto storyboard = createRef<Storyboard>();
		storyboard->name = aAnimation->mName.C_Str();
		//storyboard->setDuration(TimeSpan::fromMilliseconds((int)duration));
		m_animations.push_back(storyboard);

		for (auto j = 0u; j != aAnimation->mNumChannels; ++j)
		{
			auto aChannel = aAnimation->mChannels[j];
			auto nbNode = TreeHelper::find(m_root, aChannel->mNodeName.C_Str());
			//平移关键帧帧动画
			{
				auto translateAnimation = createRef<Vec3AnimationUsingKeyFrames>();
				translateAnimation->duration = TimeSpan::fromMilliseconds((int)duration);
				translateAnimation->setTarget(nbNode);
				translateAnimation->setTargetPropertyName("Translate");
				bool allKeysEqual = true;
				for (auto k = 0u; k != aChannel->mNumPositionKeys; ++k)
				{
					auto aKey = aChannel->mPositionKeys[k];
					//对比出有key不一样，表示key集合不是完全一样的，
					//达到此case后不再对比，否则一直对比下去
					auto nbKeyValue = glm::vec3(aKey.mValue.x, aKey.mValue.y, aKey.mValue.z);
					if (allKeysEqual && k != 0)
					{
						auto aPrevKey = aChannel->mPositionKeys[k - 1];
						auto nbPrevKeyValue = glm::vec3(aPrevKey.mValue.x, aPrevKey.mValue.y, aPrevKey.mValue.z);
						auto bEqual = glm::all(glm::equal(nbKeyValue, nbPrevKeyValue, 0.0001f));
						allKeysEqual &= bEqual;
					}
					auto keyTime = (int)(aKey.mTime / aChannel->mNumPositionKeys * duration);
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), nbKeyValue);
					translateAnimation->keyFrames().insert(nbKeyFrame);
				}
				if (aChannel->mNumPositionKeys == 1 || !allKeysEqual)
				{
					storyboard->children().push_back(translateAnimation);
				}
			}
			//旋转关键帧帧动画
			{
				auto rotateAnimation = createRef<Vec3AnimationUsingKeyFrames>();
				rotateAnimation->duration = TimeSpan::fromMilliseconds((int)duration);
				rotateAnimation->setTarget(nbNode);
				rotateAnimation->setTargetPropertyName("Rotate");
				bool allKeysEqual = true;
				for (auto k = 0u; k != aChannel->mNumRotationKeys; ++k)
				{
					auto aKey = aChannel->mRotationKeys[k];
					auto nbKeyValue = glm::vec3(aKey.mValue.x, aKey.mValue.y, aKey.mValue.z);
					if (allKeysEqual && k != 0)
					{
						auto aPrevKey = aChannel->mRotationKeys[k - 1];
						auto nbPrevKeyValue = glm::vec3(aPrevKey.mValue.x, aPrevKey.mValue.y, aPrevKey.mValue.z);
						auto bEqual = glm::all(glm::equal(nbKeyValue, nbPrevKeyValue, 0.0001f));
						allKeysEqual &= bEqual;
					}

					auto keyTime = (int)(aKey.mTime / aChannel->mNumRotationKeys * duration);
					aiQuaternion aQuat = aKey.mValue;
					glm::quat q(aQuat.w, aQuat.x, aQuat.y, aQuat.z);
					auto rMatrix = glm::mat4_cast(q);
					glm::vec3 rotate;
					glm::extractEulerAngleYXZ(rMatrix, rotate.y, rotate.x, rotate.z);
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), rotate);
					rotateAnimation->keyFrames().insert(nbKeyFrame);
				}
				/*
				rotateAnimation->StateChanged += [](const EventArgs &args) {
					auto tl = static_cast<Timeline *>(args.sender);
					auto state = tl->currentState();
					Log::info("animation state chaged = {}", state);
				};
				rotateAnimation->Process += [](const EventArgs &args) {
					auto tl = static_cast<Timeline *>(args.sender);
					auto time = tl->getCurrentTime();
					auto progress = tl->getCurrentProgress();
					//auto v = target ? target->int8_v : -1;
					Log::info("animation procesing: time[{}], progress[{}]", time.toString().data(), progress);
				};
				rotateAnimation->Completed += [](const EventArgs &args) {
					Log::info("animation complete");
				};
				*/
				if (aChannel->mNumRotationKeys == 1 || !allKeysEqual)
				{
					storyboard->children().push_back(rotateAnimation);
				}
			}
			//缩放关键帧帧动画
			{
				auto scaleAnimation = createRef<Vec3AnimationUsingKeyFrames>();
				scaleAnimation->duration = TimeSpan::fromMilliseconds((int)duration);
				scaleAnimation->setTarget(nbNode);
				scaleAnimation->setTargetPropertyName("Scale");
				bool allKeysEqual = true;
				for (auto k = 0u; k != aChannel->mNumScalingKeys; ++k)
				{
					auto aKey = aChannel->mScalingKeys[k];
					auto keyTime = (int)(aKey.mTime / aChannel->mNumScalingKeys * duration);
					auto nbKeyValue = glm::vec3(aKey.mValue.x, aKey.mValue.y, aKey.mValue.z);
					if (allKeysEqual && k != 0)
					{
						auto aPrevKey = aChannel->mScalingKeys[k - 1];
						auto nbPrevKeyValue = glm::vec3(aPrevKey.mValue.x, aPrevKey.mValue.y, aPrevKey.mValue.z);
						auto bEqual = glm::all(glm::equal(nbKeyValue, nbPrevKeyValue, 0.0001f));
						allKeysEqual &= bEqual;
					}
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), nbKeyValue);
					scaleAnimation->keyFrames().insert(nbKeyFrame);
				}
				if (aChannel->mNumScalingKeys == 1 || !allKeysEqual)
				{
					storyboard->children().push_back(scaleAnimation);
				}
			}
		}
	}
}

void ModelImporter::handleNodes(const aiScene *scene)
{
	m_root = createRef<Node>(scene->mRootNode->mName.C_Str());
	auto transform = convertMatrix(scene->mRootNode->mTransformation);
	m_root->setTransform(transform);
	loopNode(scene->mRootNode, m_root);
}

ref<Node> ModelImporter::convertMesh(aiMesh * aMesh)
{
	//把AIMESH放入一个Mesh中
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	for (int i = 0; i != aMesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (aMesh->HasPositions())		ver.position	= { aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z };
		if (aMesh->mColors[0])			ver.color		= { aMesh->mColors[0][i].r, aMesh->mColors[0][i].g, aMesh->mColors[0][i].b, aMesh->mColors[0][i].a };
		if (aMesh->mTextureCoords[0])	ver.texCoord	= { aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y };
		if (aMesh->HasNormals())		ver.normal		= { aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z };
		vertexs.push_back(ver);
	}
	for (int i = 0; i != aMesh->mNumFaces; ++i)
	{
		aiFace face = aMesh->mFaces[i];
		for (int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto index = aMesh->mMaterialIndex;
	auto nbMaterial = m_materials[index];

	auto nbMesh = createRef<Mesh>(vertexs, indices, nbMaterial);
	auto nbNode = createRef<Node>(aMesh->mName.C_Str());
	nbNode->setMesh(nbMesh);

	//统计数据
	++m_meshCount;
	m_vertexCount += vertexs.size();
	m_triangleCount += indices.size() / 3;

	return nbNode;
}

ref<Texture2D> ModelImporter::getTexture(aiMaterial *aMaterial, int aType)
{
	ref<Texture2D> ret;
	aiString originalPath;
	aiReturn r = aMaterial->GetTexture((aiTextureType)aType, 0, &originalPath);
	if (r == aiReturn_FAILURE)
	{
		return ret;
	}

	ref<Bitmap> bm;
	std::string path = m_textureDir + "/" + aiScene::GetShortFilename(originalPath.C_Str());
	auto iter = m_bmCache.find(path);
	if (iter != m_bmCache.end())
	{
		ret = iter->second;
	}
	else
	{
		bm = createRef<Bitmap>(path);
		ret = createRef<Texture2D>();
		if (bm->isValid())
		{
			ret->update(path);
		}
		else
		{
			Log::error("load texture [{}] fail.", path);
		}
		m_bmCache.insert({ path, ret });
	}
	
	return ret;
}

void ModelImporter::loopNode(aiNode * aNode, ref<Node> nbNode)
{
	auto isNode = [](aiNode * aNode) {return aNode->mNumChildren > 0; };
	auto isMesh = [](aiNode * aNode) {return aNode->mNumMeshes > 0; };

	if (isMesh(aNode))
	{
		auto transform = convertMatrix(aNode->mTransformation);
		for (int i = 0; i != aNode->mNumMeshes; ++i)
		{
			auto aMesh = m_importer->GetScene()->mMeshes[aNode->mMeshes[i]];
			auto nbMeshNode = convertMesh(aMesh);
			nbMeshNode->setTransform(transform);
			nbNode->addChild(nbMeshNode);
		}
	}

	for (auto i = 0u; i != aNode->mNumChildren; ++i)
	{
		auto aGroup = aNode->mChildren[i];
		//如果aGroup不是mesh，则是node，直接addChild
		//否则是mesh的话，不要addChild，等到下次loopNode会遍历node->mMeshes依次添加
		//这样做可以防止如果一个aGroup执行addChild两次，增加一级层次，比如root/mesh变成root/mesh/mesh
		if (!isMesh(aGroup))
		{
			auto nbGroup = createRef<Node>(aGroup->mName.C_Str());
			auto transform = convertMatrix(aGroup->mTransformation);
			nbGroup->setTransform(transform);
			nbNode->addChild(nbGroup);
			loopNode(aGroup, nbGroup);
		}
		else
		{
			loopNode(aGroup, nbNode);
		}
	}
	
}

std::string ModelImporter::getParentDir(const std::string & path)
{
	auto n = path.rfind('/');
	if (n == std::string::npos)
	{
		n = path.rfind('\\');
	}
	return n == std::string::npos ? "./" : path.substr(0, n + 1);
}
