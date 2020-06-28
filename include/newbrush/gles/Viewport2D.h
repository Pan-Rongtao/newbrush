#pragma once
#include <vector>
#include "newbrush/core/Def.h"
#include "newbrush/gles/Camera.h"
#include "newbrush/gles/Projection.h"

namespace nb {
	
class RenderObject;
using RenderObjectPtr = std::shared_ptr<RenderObject>;
class NB_API Viewport2D
{
public:
	void viewport(int x, int y, unsigned int width, unsigned height);

	//入列一个渲染物
	void queue(RenderObjectPtr renderObject);

	//渲染所有渲染物
	void draw();

	Camera		camera;
	Projection	projection;

private:
	std::vector<RenderObjectPtr> m_renderObjects;
};

}