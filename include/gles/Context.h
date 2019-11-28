/*******************************************************
**	Context
**
**	上下文类
**		Context是描述OpenGL渲染上下文的数据结构，
**	可以把它理解为OpenGL渲染指令集合
**
**		潘荣涛
**
********************************************************/
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
	Context();
	~Context();

	//gl句柄
	void *handle() const;

	//入列一个渲染物
	void queue(std::shared_ptr<RenderObject> renderObject);

	//出列一个渲染物
	void dequeue(std::shared_ptr<RenderObject> renderObject);

	//渲染物个数
	uint32_t renderObjectCount() const;

	//渲染物
	std::shared_ptr<RenderObject> renderObject(uint32_t index);

	//执行渲染动作
	void draw();

private:
	void												*m_handle;
	std::vector<std::shared_ptr<RenderObject>>	m_renderObjects;
};

}}
