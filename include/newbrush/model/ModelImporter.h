#pragma once
#include "newbrush/model/Mesh.h"
#include "newbrush/model/Camera.h"
#include "newbrush/model/Light.h"
#include "newbrush/model/Animation.h"
#include "newbrush/model/Node.h"
#include "newbrush/model/Material.h"
#include "newbrush/model/Bitmap.h"

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;
namespace Assimp {
	class Importer;
}

namespace nb{

class ModelImporter
{
public:
	ModelImporter();
	~ModelImporter();

	void load(const char * data, int lenght);
	void load(const std::string & path, const std::string &textureDir);

	const NodePtr &getRootNode() const;
	const std::vector<CameraPtr> &getCameras() const;
	const std::vector<LightPtr> &getLights() const;
	const std::vector<MaterialPtr> &getMaterials() const;
	const std::vector<StoryboardPtr> &getAnimations() const;

private:
	void handling();

	void handleCamearas(const aiScene *scene);
	void handleLights(const aiScene *scene);
	void handleMaterials(const aiScene *scene);
	void handleAnimations(const aiScene *scene);
	void handleNodes(const aiScene *scene);

	TextureMipmapPtr getTexture(aiMaterial *aMaterial, int aType);
	MeshNodePtr convertMesh(aiNode * aParentNode, aiMesh * aMesh);
	void loopNode(aiNode * aNode, NodePtr nbNode);

	std::string getParentDir(const std::string &path);

	NodePtr m_root;
	std::vector<CameraPtr> m_cameras;
	std::vector<LightPtr> m_lights;
	std::vector<MaterialPtr> m_materials;
	std::vector<StoryboardPtr> m_animations;
	std::shared_ptr<Assimp::Importer> m_importer;
	std::string m_textureDir;

	std::map<std::string, BitmapPtr> m_bmCache;
};

}