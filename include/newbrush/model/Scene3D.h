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
	Scene3D();
	Scene3D(float width, float height);

	void setWidth(float width);
	float width() const;

	void setHeight(float height);
	float height() const;

	//摄像机
	void setCamera(CameraPtr camera);
	CameraPtr camera();

	//灯光
	void setLights(const std::vector<LightPtr> &lights);
	std::vector<LightPtr> &lights();
	const std::vector<LightPtr> &lights() const;

	//模型
	void load(const std::string &path);
	void setModel(NodePtr model);
	NodePtr model();

	void draw();

	void playAnimation();

private:
	void resize();
	void loopDraw(NodePtr node);

	float m_width;
	float m_height;
	NodePtr m_model;
	CameraPtr m_camera;
	std::vector<LightPtr> m_lights;
	std::vector<StoryboardPtr> m_animations;
};

using Scene3DPtr = std::shared_ptr<Scene3D>;
}