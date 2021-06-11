/******************************************
*	节点有三种类型：
*	MeshNode：可渲染
*	AnimationNode：动画节点（包含骨骼节点）
*	BoneNode：骨骼节点（同时属于动画节点）
*	DirNode：空节点
*
*	其中，在C4D中，mesh也可以是dir。由于我们
*	在model内部不再使用树形结构，因此可以让他们互斥
*******************************************/
#pragma once
#include "newbrush/Node3D.h"
#include "newbrush/Components.h"
#include "newbrush/Animation.h"


struct aiMesh;
struct aiScene;
namespace AssimpView { class SceneAnimator; }

namespace nb
{
class NB_API Model : public Node3D
{
public:
	Model();
	~Model();

	void load(const std::string & path);

	bool hasAnimation() const;
	void play();
	void pause();
	bool isPlaying() const;
	float getFrameCount() const;
	void gotoFrame(float frame);
	void gotoPrevFrame(bool reverse = true);
	void gotoNextFrame(bool reverse = true);

	void setRenderAble(const std::string &meshName, bool renderAble);
	void setMaterial(const std::string &meshName, ref<Material> material);
	void setMaterial(ref<Material> material);
	
protected:
	virtual void onRender(ref<Camera> camera, const std::vector<ref<Light>> &lights) override;

private:
	void parseMaterials();
	ref<Mesh> toNBMesh(const aiMesh *aMesh);

	std::vector<ref<Material>> m_materials;
	std::vector<ref<Mesh>> m_meshes;
	std::map<std::string, ref<Texture2D>> m_texturesCache;
	std::string m_textureDir;
	uint32_t m_triangleCount, m_vertexCount;
	const aiScene *m_aScene;

	Timer m_timer;
	float m_curFrame;
	ref<AssimpView::SceneAnimator> mAnimator;
};

}