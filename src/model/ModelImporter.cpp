#include "newbrush/model/ModelImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <opengl/GLES2/gl2.h>
#include "newbrush/model/Log.h"

using namespace nb;

#define LOAD_FLAGS	aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices
//#define LOAD_FLAGS aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes | aiProcess_CalcTangentSpace | aiProcess_LimitBoneWeights

TransformPtr convertMatrix(const aiMatrix4x4 &aMat)
{
	TransformPtr ret = std::make_shared<Transform>();

	glm::mat4 mat;
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) mat[j][i] = aMat[i][j];

	ret->setValue(mat);

	return ret;
}

ModelImporter::ModelImporter()
	: m_importer(std::make_shared<Assimp::Importer>())
{
}

ModelImporter::~ModelImporter()
{
	m_importer->FreeScene();
}

void ModelImporter::setPath(const std::string & path)
{
	auto k = getTickCount();
	m_importer->ReadFile(path, LOAD_FLAGS);
	m_textureDir = getParentDir(path);
	auto t0 = nb::getTickCount() - k;

	k = getTickCount();
	handling();
	auto t1 = nb::getTickCount() - k;

	if (m_importer->GetScene())
	{
		Log::info("load [{}] success. assimp cost [{}], post handling cost [{}], all cost [{}].", path, t0, t1, t0 + t1);
	}
	else
	{
		Log::info("load [{}] success. error message:{}", path, m_importer->GetErrorString());
	}
	m_path = path;
}

const std::string & ModelImporter::path() const
{
	return m_path;
}

const NodePtr & ModelImporter::getRootNode() const
{
	return m_root;
}

const std::vector<CameraPtr>& ModelImporter::getCameras() const
{
	return m_cameras;
}

const std::vector<LightPtr>& ModelImporter::getLights() const
{
	return m_lights;
}

const std::vector<MaterialPtr>& ModelImporter::getMaterials() const
{
	return m_materials;
}

const std::vector<StoryboardPtr>& ModelImporter::getAnimations() const
{
	return m_animations;
}

void ModelImporter::handling()
{
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
		auto nbCamera = std::make_shared<Camera>(position, lookDirection, up, 0.0f, -90.0f, aCamera->mHorizontalFOV, aCamera->mAspect, aCamera->mClipPlaneNear, aCamera->mClipPlaneFar);
		m_cameras.push_back(nbCamera);
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
			AmbientLightPtr ambientLight = std::make_shared<AmbientLight>();
			ambientLight->setName(aLight->mName.C_Str());
			ambientLight->setAmbient(Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b));
			ambientLight->setDiffuse(Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b));
			ambientLight->setSpecular(Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b));
			m_lights.push_back(ambientLight);
			break;
		}
		case aiLightSource_DIRECTIONAL:
		{
			DirectionalLightPtr directionalLight = std::make_shared<DirectionalLight>();
			directionalLight->setName(aLight->mName.C_Str());
			directionalLight->setAmbient(Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b));
			directionalLight->setDiffuse(Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b));
			directionalLight->setSpecular(Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b));
			directionalLight->setDirection({ aLight->mDirection.x, aLight->mDirection.y, aLight->mDirection.z });
			m_lights.push_back(directionalLight);
			break;
		}
		case aiLightSource_POINT:
		{
			auto pointLight = std::make_shared<PointLight>();
			pointLight->setName(aLight->mName.C_Str());
			pointLight->setAmbient(Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b));
			pointLight->setDiffuse(Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b));
			pointLight->setSpecular(Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b));
			pointLight->setPosition(/*{ aLight->mPosition.x, aLight->mPosition.y, aLight->mPosition.z }*/glm::vec3(0.0f, 5.0f, 5.0f)); //assimp读取到的都是{0,0,0}
			pointLight->setLinearAttenuation(aLight->mAttenuationLinear);
			pointLight->setConstantAttenuation(aLight->mAttenuationConstant);
			pointLight->setQuadraticAttenuation(aLight->mAttenuationQuadratic);
			m_lights.push_back(pointLight); 
			break;
		}
		case aiLightSource_SPOT:
		{
			auto spotLight = std::make_shared<SpotLight>();
			spotLight->setName(aLight->mName.C_Str());
			spotLight->setAmbient(Color::fromRgbF(aLight->mColorAmbient.r, aLight->mColorAmbient.g, aLight->mColorAmbient.b));
			spotLight->setDiffuse(Color::fromRgbF(aLight->mColorDiffuse.r, aLight->mColorDiffuse.g, aLight->mColorDiffuse.b));
			spotLight->setSpecular(Color::fromRgbF(aLight->mColorSpecular.r, aLight->mColorSpecular.g, aLight->mColorSpecular.b));
			spotLight->setPosition(/*{ aLight->mPosition.x, aLight->mPosition.y, aLight->mPosition.z }*/glm::vec3(0.0f, 5.0f, 5.0f)); //assimp读取到的都是{0,0,0}
			spotLight->setLinearAttenuation(aLight->mAttenuationLinear);
			spotLight->setConstantAttenuation(aLight->mAttenuationConstant);
			spotLight->setQuadraticAttenuation(aLight->mAttenuationQuadratic);
			spotLight->setDirection({ aLight->mDirection.x, aLight->mDirection.y, aLight->mDirection.z });
			spotLight->setInnerConeAngle(aLight->mAngleInnerCone);
			spotLight->setOuterConeAngle(aLight->mAngleOuterCone); 
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
			ret = aMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
			ret = aMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissiveColor);
			
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
			PhongMaterialPtr phongMaterial = std::make_shared<PhongMaterial>();
			phongMaterial->setName(aMaterial->GetName().C_Str());
			phongMaterial->setAmbient(Color::fromRgbF(ambientColor.r, ambientColor.g, ambientColor.b));
			phongMaterial->setDiffuse(Color::fromRgbF(diffuseColor.r, diffuseColor.g, diffuseColor.b));
			phongMaterial->setSpecular(Color::fromRgbF(specularColor.r, specularColor.g, specularColor.b));
			phongMaterial->setEmission(Color::fromRgbF(emissiveColor.r, emissiveColor.g, emissiveColor.b));
			phongMaterial->setShineness(shininess);
			phongMaterial->setDiffuseMapping(diffuseMapping);
			//phongMaterial->setSpecularMapping(specularMapping);
			//phongMaterial->setEmissionMapping(emissionMapping);

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

		auto storyboard = std::make_shared<Storyboard>();
		storyboard->setName(aAnimation->mName.C_Str());
		storyboard->setDuration(TimeSpan::fromMilliseconds((int)duration));
		m_animations.push_back(storyboard);

		for (auto j = 0u; j != aAnimation->mNumChannels; ++j)
		{
			auto aChannel = aAnimation->mChannels[j];
			auto nbNode = m_root->find(aChannel->mNodeName.C_Str());
			//平移关键帧帧动画
			{
				auto translateAnimation = std::make_shared<Vec3AnimationUsingKeyFrames>();
				translateAnimation->setTargetPropertyName("Position");
				translateAnimation->setTarget(nbNode->transform());
				for (auto k = 0u; k != aChannel->mNumPositionKeys; ++k)
				{
					auto aKey = aChannel->mPositionKeys[k];
					auto keyTime = (int)(aKey.mTime / aChannel->mNumPositionKeys * duration);
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), glm::vec3(aKey.mValue.x, aKey.mValue.y, aKey.mValue.z));
					translateAnimation->keyFrames().insert(nbKeyFrame);
				}
				storyboard->children().push_back(translateAnimation);
			}
			//旋转关键帧帧动画
			{
				auto rotateAnimation = std::make_shared<Vec3AnimationUsingKeyFrames>();
				rotateAnimation->setTarget(nbNode->transform());
				rotateAnimation->setTargetPropertyName("Rotate");
				for (auto k = 0u; k != aChannel->mNumRotationKeys; ++k)
				{
					auto aKey = aChannel->mRotationKeys[k];
					auto keyTime = (int)(aKey.mTime / aChannel->mNumRotationKeys * duration);
					aiQuaternion aQuat = aKey.mValue;
					glm::quat q(aQuat.w, aQuat.x, aQuat.y, aQuat.z);
					auto rMatrix = glm::mat4_cast(q);
					glm::vec3 rotate;
					glm::extractEulerAngleYXZ(rMatrix, rotate.y, rotate.x, rotate.z);
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), rotate);
					rotateAnimation->keyFrames().insert(nbKeyFrame);
				}
				storyboard->children().push_back(rotateAnimation);
			}
			//缩放关键帧帧动画
			{
				auto scaleAnimation = std::make_shared<Vec3AnimationUsingKeyFrames>();
				scaleAnimation->setTarget(nbNode->transform());
				scaleAnimation->setTargetPropertyName("Scale");
				for (auto k = 0u; k != aChannel->mNumScalingKeys; ++k)
				{
					auto aKey = aChannel->mScalingKeys[k];
					auto keyTime = (int)(aKey.mTime / aChannel->mNumScalingKeys * duration);
					auto nbKeyFrame = Vec3KeyFrame(TimeSpan::fromMilliseconds(keyTime), glm::vec3(aKey.mValue.x, aKey.mValue.y, aKey.mValue.z));
					scaleAnimation->keyFrames().insert(nbKeyFrame);
				}
				storyboard->children().push_back(scaleAnimation);
			}
		}
	}
}

void ModelImporter::handleNodes(const aiScene *scene)
{
	m_root = std::make_shared<Node>(std::string(scene->mRootNode->mName.C_Str()));
	auto transform = convertMatrix(scene->mRootNode->mTransformation);
	m_root->setTransform(transform);
	loopNode(scene->mRootNode, m_root);
}

MeshNodePtr ModelImporter::convertMesh(aiNode * aParentNode, aiMesh * aMesh)
{
	//把AIMESH放入一个Mesh中
	std::vector<Vertex> vertexs;
	std::vector<uint16_t> indices;
	for (int i = 0; i != aMesh->mNumVertices; ++i)
	{
		Vertex ver;
		if (aMesh->HasPositions())		ver.position = { aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z };
		if (aMesh->mColors[0])			ver.color = { aMesh->mColors[0][i].r, aMesh->mColors[0][i].g, aMesh->mColors[0][i].b, aMesh->mColors[0][i].a };
		if (aMesh->mTextureCoords[0])	ver.texCoord = { aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y };
		if (aMesh->HasNormals())		ver.normal = { aMesh->mNormals[i].x, aMesh->mNormals[i].y, aMesh->mNormals[i].z };
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

	auto nbMesh = std::make_shared<Mesh>(vertexs, indices, nbMaterial);
	auto nbMeshNode = std::make_shared<MeshNode>(aMesh->mName.C_Str(), nbMesh);
	return nbMeshNode;
}

TexturePtr ModelImporter::getTexture(aiMaterial *aMaterial, int aType)
{
	TexturePtr ret;
	aiString originalPath;
	aiReturn r = aMaterial->GetTexture((aiTextureType)aType, 0, &originalPath);
	if (r == aiReturn_FAILURE)
	{
		return ret;
	}

	BitmapPtr bm;
	std::string path = m_textureDir + "/" + aiScene::GetShortFilename(originalPath.C_Str());
	auto iter = m_bmCache.find(path);
	if (iter != m_bmCache.end())
	{
		bm = iter->second;
	}
	else
	{
		bm = std::make_shared<Bitmap>(path);
		m_bmCache.insert({ path, bm });
	}

	if (bm->isValid())
	{
		ret = std::make_shared<Texture>(TextureTypeE::Texture2D);
		auto glFormatAndType = Texture::getGlFormatAndType(bm->channels());
		ret->update(0, bm->data(), bm->width(), bm->height(), glFormatAndType.first, glFormatAndType.second);
		ret->genMipmap();
	}
	else
	{
		Log::error("load texture [{}] fail.", path);
	}

	return ret;
}

void ModelImporter::loopNode(aiNode * aNode, NodePtr nbNode)
{
	//如果有mesh，表示该节点下仅由就是mesh类型
	for (int i = 0; i != aNode->mNumMeshes; ++i)
	{
		auto aMesh = m_importer->GetScene()->mMeshes[aNode->mMeshes[i]];
		auto nbMeshNode = convertMesh(aNode, aMesh);
		nbNode->addChild(nbMeshNode);
	}

	for (auto i = 0u; i != aNode->mNumChildren; ++i)
	{
		auto aGroup = aNode->mChildren[i];
		auto nbGroup = std::make_shared<Node>(std::string(aGroup->mName.C_Str()));
		auto transform = convertMatrix(aGroup->mTransformation);
		nbGroup->setTransform(transform);
		nbNode->addChild(nbGroup);
		loopNode(aGroup, nbGroup);
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
