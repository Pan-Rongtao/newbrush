#pragma once
#include "newbrush/Light.h"
#include "newbrush/Camera.h"
#include "newbrush/Node.h"
#include "newbrush/Animation.h"
#include "newbrush/Mesh.h"

namespace nb 
{

class NB_API Scene : public Node
{
	RTTR_ENABLE(Node)
public:
	Scene();

	void setCamera(ref<PerspectiveCamera> camera);
	ref<PerspectiveCamera> getCamera() const;

	virtual void onResize(float width, float height) override;

	std::vector<ref<Light>> lights;
	std::vector<ref<Storyboard>> animations;

	virtual void onRender() override;

private:
	void loopDraw(ref<Node> node);

	ref<PerspectiveCamera> m_camera;
};

}