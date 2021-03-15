#pragma once
#include "newbrush/Mesh.h"
#include "newbrush/Camera.h"
#include "newbrush/Light.h"
#include "newbrush/Animation.h"
#include "newbrush/Node.h"
#include "newbrush/Material.h"
#include "newbrush/Bitmap.h"
#include "newbrush/Texture.h"

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
namespace Assimp {
	class Importer;
}

namespace nb
{

class NB_API ModelImporter
{
public:
	ModelImporter();
	~ModelImporter();

	//加载模型
	//异常：std::runtime_error
	void load(const std::string & path);
	const std::string &path() const;
	
	const ref<Node> &getRoot() const;
	const std::vector<ref<Light>> &getLights() const;
	const std::vector<ref<Material>> &getMaterials() const;
	const std::vector<ref<Storyboard>> &getAnimations() const;

	int32_t getMeshCount() const;
	int32_t getTriangleCount() const;
	int32_t getVertexCount() const;

private:
	void handling();

	void handleCamearas(const aiScene *scene);
	void handleLights(const aiScene *scene);
	void handleMaterials(const aiScene *scene);
	void handleAnimations(const aiScene *scene);
	void handleNodes(const aiScene *scene);

	ref<Texture2D> getTexture(aiMaterial *aMaterial, int aType);
	ref<Node> convertMesh(aiMesh * aMesh);
	void loopNode(aiNode * aNode, ref<Node> nbNode);

	std::string getParentDir(const std::string &path);

	ref<Node> m_root;
	std::vector<ref<Light>> m_lights;
	std::vector<ref<Material>> m_materials;
	std::vector<ref<Storyboard>> m_animations;
	ref<Assimp::Importer> m_importer;
	std::string m_path;
	std::string m_textureDir;
	int32_t m_meshCount;
	int32_t m_triangleCount;
	int32_t m_vertexCount;

	std::map<std::string, ref<Texture2D>> m_bmCache;
};

}