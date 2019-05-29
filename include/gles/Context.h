#pragma once
#include "../core/Def.h"
#include <vector>

namespace nb{ namespace gl{

class Configure;
class RenderObject;
class NB_API Context
{
public:
	//构建一个Context，使用配置configure
	Context(std::shared_ptr<Configure> configure);
	~Context();

	//gl句柄
	void *handle() const;

	//入列一个渲染物
	void queue(std::shared_ptr<nb::gl::RenderObject> renderObject);

	//出列一个渲染物
	void dequeue(std::shared_ptr<nb::gl::RenderObject> renderObject);

	//
	int renderObjectCount() const;

	//渲染物
	std::shared_ptr<nb::gl::RenderObject> renderObject(uint32_t index);

	//执行渲染动作
	void draw();

private:
	void												*m_handle;
	std::vector<std::shared_ptr<nb::gl::RenderObject>>	m_renderObjects;
};

}}
