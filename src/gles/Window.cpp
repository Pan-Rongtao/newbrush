#include "gles/Window.h"
#include "EglMaster.h"

using namespace nb::gl;

Window::Window()
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
