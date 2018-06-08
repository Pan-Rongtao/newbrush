#pragma once
#include "core/NewBrushDef.h"
#include "gles/Display.h"
#include "gles/Configure.h"
#include "gles/RenderObject.h"

namespace nb{ namespace gl{ namespace egl{
class Surface;
class WindowSurface;
class Context;
}}}

namespace nb{ namespace gl{ namespace Gles{

class NB_EXPORT Application
{
public:
	//构建一个Application对象
	//异常：多次构建
	Application();
	virtual ~Application();

	//运行
	void Run();

protected:
	//初始化
	virtual void InitializeOverride();

	//渲染前
	virtual void PreRenderOverride();

	//渲染后
	virtual void PostRenderOverride();

	//空闲
	virtual void IdledOverride();


private:
	void Initialize();
	void Render();
};

}}}
