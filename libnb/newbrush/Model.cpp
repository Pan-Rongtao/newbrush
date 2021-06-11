#include "newbrush/Model.h"
#include "newbrush/Log.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/ai_assert.h"
#include "assimp/postprocess.h"
#include "ghc/filesystem.hpp"

/*namespace AssimpView是assimp_view的代码，请勿改动*/
namespace AssimpView
{
class AnimEvaluator
{
public:
	AnimEvaluator(const aiAnimation* pAnim) : mAnim(pAnim), mLastTime(0.0) { mLastPositions.resize(pAnim->mNumChannels, std::make_tuple(0, 0, 0)); }
	void Evaluate(double pTime);
	const std::vector<aiMatrix4x4>& GetTransformations() const { return mTransforms; }

protected:
	const aiAnimation* mAnim;
	double mLastTime;
	std::vector<std::tuple<unsigned int, unsigned int, unsigned int> > mLastPositions;
	std::vector<aiMatrix4x4> mTransforms;
};

struct SceneAnimNode 
{
	std::string mName;
	SceneAnimNode* mParent;
	std::vector<SceneAnimNode*> mChildren;
	aiMatrix4x4 mLocalTransform;
	aiMatrix4x4 mGlobalTransform;
	int mChannelIndex;

	SceneAnimNode() : mName(), mParent(nullptr), mChildren(), mLocalTransform(), mGlobalTransform(), mChannelIndex(-1) {}
	SceneAnimNode(const std::string& pName) : mName(pName), mParent(nullptr), mChildren(), mLocalTransform(), mGlobalTransform(), mChannelIndex(-1) {}
	~SceneAnimNode() { for (std::vector<SceneAnimNode*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it) { delete *it; } }
};

class SceneAnimator 
{
public:
	SceneAnimator(const aiScene* pScene, size_t pAnimIndex = 0);
	~SceneAnimator();

	void SetAnimIndex(size_t pAnimIndex);
	void Calculate(double pTime);
	const aiMatrix4x4& GetLocalTransform(const aiNode* node) const;
	const aiMatrix4x4& GetGlobalTransform(const aiNode* node) const;
	const std::vector<aiMatrix4x4>& GetBoneMatrices(const aiNode* pNode, size_t pMeshIndex = 0);
	size_t CurrentAnimIndex() const { return mCurrentAnimIndex; }
	aiAnimation* CurrentAnim() const { return  static_cast<unsigned int>(mCurrentAnimIndex) < mScene->mNumAnimations ? mScene->mAnimations[mCurrentAnimIndex] : NULL;}

protected:
	SceneAnimNode* CreateNodeTree(aiNode* pNode, SceneAnimNode* pParent);
	void UpdateTransforms(SceneAnimNode* pNode, const std::vector<aiMatrix4x4>& pTransforms);
	void CalculateGlobalTransform(SceneAnimNode* pInternalNode);

protected:
	const aiScene* mScene;
	int mCurrentAnimIndex;
	AnimEvaluator* mAnimEvaluator;
	SceneAnimNode* mRootNode;
	typedef std::map<const aiNode*, SceneAnimNode*> NodeMap;
	NodeMap mNodesByName;
	typedef std::map<const char*, const aiNode*> BoneMap;
	BoneMap mBoneNodesByName;
	std::vector<aiMatrix4x4> mTransforms;
};

void AnimEvaluator::Evaluate(double pTime)
{
	double ticksPerSecond = mAnim->mTicksPerSecond != 0.0 ? mAnim->mTicksPerSecond : 25.0;
	pTime *= ticksPerSecond;

	double time = 0.0f;
	if (mAnim->mDuration > 0.0) {
		time = fmod(pTime, mAnim->mDuration);
	}

	if (mTransforms.size() != mAnim->mNumChannels) {
		mTransforms.resize(mAnim->mNumChannels);
	}

	for (unsigned int a = 0; a < mAnim->mNumChannels; ++a) {
		const aiNodeAnim* channel = mAnim->mChannels[a];

		// ******** Position *****
		aiVector3D presentPosition(0, 0, 0);
		if (channel->mNumPositionKeys > 0) {
			unsigned int frame = (time >= mLastTime) ? std::get<0>(mLastPositions[a]) : 0;
			while (frame < channel->mNumPositionKeys - 1) {
				if (time < channel->mPositionKeys[frame + 1].mTime) {
					break;
				}
				++frame;
			}

			unsigned int nextFrame = (frame + 1) % channel->mNumPositionKeys;
			const aiVectorKey& key = channel->mPositionKeys[frame];
			const aiVectorKey& nextKey = channel->mPositionKeys[nextFrame];
			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < 0.0) {
				diffTime += mAnim->mDuration;
			}
			if (diffTime > 0) {
				float factor = float((time - key.mTime) / diffTime);
				presentPosition = key.mValue + (nextKey.mValue - key.mValue) * factor;
			}
			else {
				presentPosition = key.mValue;
			}

			std::get<0>(mLastPositions[a]) = frame;
		}

		// ******** Rotation *********
		aiQuaternion presentRotation(1, 0, 0, 0);
		if (channel->mNumRotationKeys > 0) {
			unsigned int frame = (time >= mLastTime) ? std::get<1>(mLastPositions[a]) : 0;
			while (frame < channel->mNumRotationKeys - 1) {
				if (time < channel->mRotationKeys[frame + 1].mTime) {
					break;
				}
				++frame;
			}

			unsigned int nextFrame = (frame + 1) % channel->mNumRotationKeys;
			const aiQuatKey& key = channel->mRotationKeys[frame];
			const aiQuatKey& nextKey = channel->mRotationKeys[nextFrame];
			double diffTime = nextKey.mTime - key.mTime;
			if (diffTime < 0.0) {
				diffTime += mAnim->mDuration;
			}
			if (diffTime > 0) {
				float factor = float((time - key.mTime) / diffTime);
				aiQuaternion::Interpolate(presentRotation, key.mValue, nextKey.mValue, factor);
			}
			else {
				presentRotation = key.mValue;
			}

			std::get<1>(mLastPositions[a]) = frame;
		}

		// ******** Scaling **********
		aiVector3D presentScaling(1, 1, 1);
		if (channel->mNumScalingKeys > 0) {
			unsigned int frame = (time >= mLastTime) ? std::get<2>(mLastPositions[a]) : 0;
			while (frame < channel->mNumScalingKeys - 1) {
				if (time < channel->mScalingKeys[frame + 1].mTime) {
					break;
				}
				++frame;
			}

			presentScaling = channel->mScalingKeys[frame].mValue;
			std::get<2>(mLastPositions[a]) = frame;
		}

		// build a transformation matrix from it
		aiMatrix4x4& mat = mTransforms[a];
		mat = aiMatrix4x4(presentRotation.GetMatrix());
		mat.a1 *= presentScaling.x; mat.b1 *= presentScaling.x; mat.c1 *= presentScaling.x;
		mat.a2 *= presentScaling.y; mat.b2 *= presentScaling.y; mat.c2 *= presentScaling.y;
		mat.a3 *= presentScaling.z; mat.b3 *= presentScaling.z; mat.c3 *= presentScaling.z;
		mat.a4 = presentPosition.x; mat.b4 = presentPosition.y; mat.c4 = presentPosition.z;
	}

	mLastTime = time;
}

const aiMatrix4x4 IdentityMatrix;
SceneAnimator::SceneAnimator(const aiScene* pScene, size_t pAnimIndex)
	: mScene(pScene)
	, mCurrentAnimIndex(-1)
	, mAnimEvaluator(nullptr)
	, mRootNode(nullptr)
{
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i) {
		const aiMesh* mesh = pScene->mMeshes[i];
		for (unsigned int n = 0; n < mesh->mNumBones; ++n) {
			const aiBone* bone = mesh->mBones[n];
			auto node = pScene->mRootNode->FindNode(bone->mName);
			mBoneNodesByName[bone->mName.data] = node;
		}
	}
	SetAnimIndex(pAnimIndex);
}

SceneAnimator::~SceneAnimator() {
	delete mRootNode;
	delete mAnimEvaluator;
}

void SceneAnimator::SetAnimIndex(size_t pAnimIndex) {
	if (pAnimIndex == static_cast<unsigned int>(mCurrentAnimIndex)) {
		return;
	}

	delete mRootNode;  mRootNode = nullptr;
	delete mAnimEvaluator;  mAnimEvaluator = nullptr;
	mNodesByName.clear();

	mCurrentAnimIndex = static_cast<int>(pAnimIndex);
	mRootNode = CreateNodeTree(mScene->mRootNode, nullptr);
	if (static_cast<unsigned int>(mCurrentAnimIndex) >= mScene->mNumAnimations) {
		return;
	}

	mAnimEvaluator = new AnimEvaluator(mScene->mAnimations[mCurrentAnimIndex]);
}

void SceneAnimator::Calculate(double pTime) {
	if (!mAnimEvaluator) {
		return;
	}

	mAnimEvaluator->Evaluate(pTime);
	UpdateTransforms(mRootNode, mAnimEvaluator->GetTransformations());
}

const aiMatrix4x4& SceneAnimator::GetLocalTransform(const aiNode* node) const {
	NodeMap::const_iterator it = mNodesByName.find(node);
	if (it == mNodesByName.end()) {
		return IdentityMatrix;
	}

	return it->second->mLocalTransform;
}

const aiMatrix4x4& SceneAnimator::GetGlobalTransform(const aiNode* node) const {
	NodeMap::const_iterator it = mNodesByName.find(node);
	if (it == mNodesByName.end()) {
		return IdentityMatrix;
	}

	return it->second->mGlobalTransform;
}

const std::vector<aiMatrix4x4>& SceneAnimator::GetBoneMatrices(const aiNode* pNode, size_t pMeshIndex /* = 0 */) {
	ai_assert(pMeshIndex < pNode->mNumMeshes);
	size_t meshIndex = pNode->mMeshes[pMeshIndex];
	ai_assert(meshIndex < mScene->mNumMeshes);
	const aiMesh* mesh = mScene->mMeshes[meshIndex];

	// resize array and initialize it with identity matrices
	mTransforms.resize(mesh->mNumBones, aiMatrix4x4());

	//修改点：与assimp_viewer不同，不需要计算globalInverseMeshTransform
	// calculate the mesh's inverse global transform
	//aiMatrix4x4 globalInverseMeshTransform = GetGlobalTransform( pNode);
	//globalInverseMeshTransform.Inverse();

	// Bone matrices transform from mesh coordinates in bind pose to mesh coordinates in skinned pose
	// Therefore the formula is offsetMatrix * currentGlobalTransform * inverseCurrentMeshTransform
	for (size_t a = 0; a < mesh->mNumBones; ++a) {
		const aiBone* bone = mesh->mBones[a];
		const aiMatrix4x4& currentGlobalTransform = GetGlobalTransform(mBoneNodesByName[bone->mName.data]);
		mTransforms[a] = /*globalInverseMeshTransform * */currentGlobalTransform * bone->mOffsetMatrix;
	}

	return mTransforms;
}

SceneAnimNode* SceneAnimator::CreateNodeTree(aiNode* pNode, SceneAnimNode* pParent) {
	// create a node
	SceneAnimNode* internalNode = new SceneAnimNode(pNode->mName.data);
	internalNode->mParent = pParent;
	mNodesByName[pNode] = internalNode;

	// copy its transformation
	internalNode->mLocalTransform = pNode->mTransformation;
	CalculateGlobalTransform(internalNode);

	// find the index of the animation track affecting this node, if any
	if (static_cast<unsigned int>(mCurrentAnimIndex) < mScene->mNumAnimations) {
		internalNode->mChannelIndex = -1;
		const aiAnimation* currentAnim = mScene->mAnimations[mCurrentAnimIndex];
		for (unsigned int a = 0; a < currentAnim->mNumChannels; a++) {
			if (currentAnim->mChannels[a]->mNodeName.data == internalNode->mName) {
				internalNode->mChannelIndex = a;
				break;
			}
		}
	}

	// continue for all child nodes and assign the created internal nodes as our children
	for (unsigned int a = 0; a < pNode->mNumChildren; ++a) {
		SceneAnimNode* childNode = CreateNodeTree(pNode->mChildren[a], internalNode);
		internalNode->mChildren.push_back(childNode);
	}

	return internalNode;
}

void SceneAnimator::UpdateTransforms(SceneAnimNode* pNode, const std::vector<aiMatrix4x4>& pTransforms) {
	if (pNode->mChannelIndex != -1) {
		ai_assert(static_cast<unsigned int>(pNode->mChannelIndex) < pTransforms.size());
		pNode->mLocalTransform = pTransforms[pNode->mChannelIndex];
	}

	CalculateGlobalTransform(pNode);
	for (std::vector<SceneAnimNode*>::iterator it = pNode->mChildren.begin(); it != pNode->mChildren.end(); ++it) {
		UpdateTransforms(*it, pTransforms);
	}
}

void SceneAnimator::CalculateGlobalTransform(SceneAnimNode* pInternalNode)
{
	pInternalNode->mGlobalTransform = pInternalNode->mLocalTransform;
	SceneAnimNode* node = pInternalNode->mParent;
	while (node)
	{
		pInternalNode->mGlobalTransform = node->mLocalTransform * pInternalNode->mGlobalTransform;
		node = node->mParent;
	}
}

}

using namespace nb;
using namespace AssimpView;
namespace fs = ghc::filesystem;

#define LOAD_FLAGS	aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_RemoveRedundantMaterials| aiProcess_LimitBoneWeights
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

	Log::info("load [{}] success. [assimp|post handing|all] cost [{}+{}={}] ms. [Meshs,Triangles,Vertexs] counts [{},{},{}].",
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

void Model::setMaterial(ref<Material> material)
{
	for (auto mesh : m_meshes)
	{
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
		if (aMesh->mTextureCoords[0])	ver.uv = { aMesh->mTextureCoords[0][i].x, aMesh->mTextureCoords[0][i].y };
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
		shader->setMat4("u_rootMatrix", mat);
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
		if (node && mesh->hasBone)
		{
			auto const &boneMats = mAnimator->GetBoneMatrices(node, 0);
			auto s = mesh->material->shader;
			s->use();
			for (auto i = 0u; i != boneMats.size(); ++i)
			{
				std::string name = "u_bonesMatrixs[" + std::to_string(i) + "]";
				auto location = shader->getUniformLocation(name.data());
				glUniformMatrix4fv(location, 1, GL_TRUE, (const GLfloat*)&(boneMats[i]));
			}
			s->disuse();
		}

		mesh->draw(nbMat, camera, lights);
	}
}
