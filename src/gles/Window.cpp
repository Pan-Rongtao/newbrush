#include "gles/Window.h"
#include "EglMaster.h"

using nb::gl::egl::Window;
using nb::gl::egl::WindowMaster;
Window::Window()
{
	WindowMaster::Push(this);
}

Window::~Window()
{
	WindowMaster::Erease(this);
}
