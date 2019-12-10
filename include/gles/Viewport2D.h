#pragma once
#include <vector>
#include "../core/Def.h"
#include "../gles/Camera.h"

namespace nb {
	
class Camera;
class RenderObject;
class NB_API Viewport2D
{
public:
	//入列一个渲染物
	void queue(std::shared_ptr<RenderObject> renderObject);

	//渲染所有渲染物
	void draw();

private:
	std::shared_ptr<Camera>						m_camera;
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}