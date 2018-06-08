/*******************************************************
**	Painter
**
**	着色者
**	
**	着色者是用于绘制渲染物的数据结构，
**		
**		潘荣涛
**	
********************************************************/
#pragma once
#include "system/Global.h"

namespace nb{ namespace gl{ namespace egl{
	class Context;
}}}

namespace nb{ namespace gl{ namespace Gles{

class RenderObject;
class NB_EXPORT Painter
{
public:
	//构建一个着色者
	Painter(const nb::gl::egl::Context *context);

	virtual ~Painter();
	
	//渲染一个渲染物
	void Paint(RenderObject *renderObject);

};


}}}
