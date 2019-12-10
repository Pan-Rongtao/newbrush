#pragma once
#include <vector>
#include "../core/Def.h"
#include "../gles/Camera.h"
#include "../gles/Projection.h"

namespace nb {
	
class RenderObject;
class NB_API Viewport2D
{
public:
	void viewport(int x, int y, unsigned int width, unsigned height);

	//入列一个渲染物
	void queue(std::shared_ptr<RenderObject> renderObject);

	//渲染所有渲染物
	void draw();

	Camera		camera;
	Projection	projection;

private:
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}