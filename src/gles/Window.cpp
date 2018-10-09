#include "gles/Window.h"
#include "EglMaster.h"

using namespace nb::gl;

Window::Window()
{
	WindowMaster::push(this);
}

Window::~Window()
{
	WindowMaster::erease(this);
}
