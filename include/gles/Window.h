#pragma once
#include "../core/Def.h"
#include "../core/Window.h"

namespace nb{ namespace gl{

class NB_API Window : public nb::core::Window
{
public:	
	//构建一个Window对象，它的标题为空，区域为(x-middle, y-middle, 800, 480)
	Window();

	//构建一个Window对象，它的标题为空，区域为(x-middle, y-middle, width, height)
	Window(int width, int height);

	//构建一个Window对象，它的标题为空，区域为(x, y, width, height)
	Window(int x, int y, int width, int height);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, 800, 480)
	explicit Window(const std::string &title);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, width, height)
	Window(const std::string &title, int width, int height);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, width, height)
	Window(const std::string &title, int x, int y, int width, int height);

	~Window();
};

}}
