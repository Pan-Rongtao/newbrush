#pragma once
#include "newbrush/Node3D.h"
#include "newbrush/Animation.h"
#include "newbrush/Components.h"
#include "assimp/scene.h"

namespace nb 
{

class NB_API Scene : public Node3D
{
	RTTR_ENABLE(Node3D)
public:
	Scene();

	//摄像头
	void setCamera(ref<PerspectiveCamera> camera);
	ref<PerspectiveCamera> getCamera() const;

	//灯光
	void addLight(ref<Light> light);
	void removeLight(unsigned index);
	unsigned lightCount() const;
	bool hasLight() const;
	ref<Light> getLightAt(unsigned index);
	void clearLights();
	const std::vector<ref<Light>> lights() const;

	virtual void onRender() override;

private:
	ref<PerspectiveCamera> m_camera;
	std::vector<ref<Light>> m_lights;
};

}