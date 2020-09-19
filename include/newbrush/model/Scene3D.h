#pragma once
#include "newbrush/model/Light.h"
#include "newbrush/model/Camera.h"
#include "newbrush/model/Node.h"
#include "newbrush/model/Animation.h"

namespace nb {

class NB_API Scene3D : public Object
{
	RTTR_ENABLE(Object)
public:
	Scene3D(int width, int height);

	void resize(int width, int height);

	//摄像机
	void setCamera(CameraPtr camera);
	CameraPtr camera();

	//灯光
	void addLight(LightPtr light);
	void removeLight(LightPtr light);
	void removeLightAt(uint32_t index);
	LightPtr lightAt(uint32_t index);
	uint32_t lightCount() const;

	//模型
	void setModel(NodePtr model);
	NodePtr model();

	void load(const std::string &path, const std::string &textureDir = "");

	void draw();

	void playAnimation();

private:
	void loopDraw(NodePtr node);

	CameraPtr m_camera;
	std::vector<LightPtr> m_lights;
	NodePtr m_model;
	std::vector<StoryboardPtr> m_animations;
};

using Scene3DPtr = std::shared_ptr<Scene3D>;
}