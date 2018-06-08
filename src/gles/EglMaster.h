#pragma once
#include "core/NewBrushDef.h"
#include "gles/Configure.h"

namespace nb {namespace gl{ namespace egl{
class Window;
class Context;
class WindowSurface;
class NB_EXPORT WindowMaster
{
public:
	//
	static void Push(nb::gl::egl::Window *window);

	//
	static void Erease(nb::gl::egl::Window *window);

	//获取窗口个数
	static int GetCount();

	//查找一个窗口
	static nb::gl::egl::Window *At(int index);
};

class NB_EXPORT ContextMaster
{
public:
	//创建一个Contex
	static void Push(Context *contex);

	//销毁一个Contex
	static void Erease(Context *contex);

	//获取Contex个数
	static int GetCount();

	//查找一个Contex
	static Context *At(int index);
};

class NB_EXPORT SurfacesMaster
{
public:
	//创建一个WindowSurface
	static void Push(WindowSurface *surface);

	//销毁一个WindowSurface
	static void Erease(WindowSurface *surface);

	//获取WindowSurface个数
	static int GetCount();

	//查找一个WindowSurface
	static WindowSurface *At(int index);
};

}}}
