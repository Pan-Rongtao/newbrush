#include "gles/Window.h"
#include "EglMaster.h"

using namespace nb::gl;

Window::Window()
	: nb::Window()
{
	EglMaster::windows().push_back(this);
}

Window::Window(int width, int height)
	: nb::Window(width, height)
{
	EglMaster::windows().push_back(this);
}

Window::Window(int x, int y, int width, int height)
	: nb::Window(x, y, 800, 480)
{
	EglMaster::windows().push_back(this);
}

Window::Window(const std::string &title)
	: nb::Window(title)
{
	EglMaster::windows().push_back(this);
}

Window::Window(const std::string &title, int width, int height)
	: nb::Window(title, width, height)
{
	EglMaster::windows().push_back(this);
}

Window::Window(const std::string &title, int x, int y, int width, int height)
{
	EglMaster::windows().push_back(this);
}

Window::~Window()
{
	auto &windows = EglMaster::windows();
	auto iter = std::find(windows.begin(), windows.end(), this);
	if (iter != windows.end())
		windows.erase(iter);
}
