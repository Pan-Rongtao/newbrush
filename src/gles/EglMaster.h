#pragma once
#include "core/Def.h"
#include <vector>

namespace nb {namespace gl{
class Window;
class Context;
class WindowSurface;
class NB_API EglMaster
{
public:
	//窗口集
	static std::vector<Window *> &windows();

	//上下文集
	static std::vector<Context *> &contexts();

	//windowsSurface集
	static std::vector<WindowSurface *> &windowSurfaces();
};

}}
