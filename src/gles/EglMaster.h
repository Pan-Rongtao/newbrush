#pragma once
#include "core/Def.h"
#include "gles/Configure.h"

namespace nb {namespace gl{
class Window;
class Context;
class WindowSurface;
class NB_API WindowMaster
{
public:
	//
	static void push(nb::gl::Window *window);

	//
	static void erease(nb::gl::Window *window);

	//获取窗口个数
	static int count();

	//查找一个窗口
	static nb::gl::Window *at(int index);
};

class NB_API ContextMaster
{
public:
	//创建一个Contex
	static void push(Context *contex);

	//销毁一个Contex
	static void erease(Context *contex);

	//获取Contex个数
	static int count();

	//查找一个Contex
	static Context *at(int index);
};

class NB_API SurfacesMaster
{
public:
	//创建一个WindowSurface
	static void push(WindowSurface *surface);

	//销毁一个WindowSurface
	static void erease(WindowSurface *surface);

	//获取WindowSurface个数
	static int count();

	//查找一个WindowSurface
	static WindowSurface *at(int index);
};

}}
