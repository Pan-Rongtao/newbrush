#include "gui/Window.h"
#include "core/Exception.h"
#include "WindowManager.h"
#include "gles/Egl.h"
#include "gles/Window.h"
#include "gui/Application.h"

using namespace nb::core;
using namespace nb::gui;

nb::gui::Window::Window()
{
	m_glWindow = std::make_shared<nb::gl::Window>();
	try {
		std::shared_ptr<nb::gl::WindowSurface> windowSurface = std::make_shared<nb::gl::WindowSurface>(m_glWindow->width(), m_glWindow->height(), m_glWindow->handle());
		std::shared_ptr<nb::gl::Context> context = std::make_shared<nb::gl::Context>(nb::gl::getCurrentConfigure());
		nb::gl::makeCurrent(windowSurface, windowSurface, context);
	}
	catch (Exception &e)
	{
		NB_THROW_EXCEPTION("you should create Application before you create a nb::gui::Window");
	}
}

nb::gui::Window::~Window()
{

}

void nb::gui::Window::active()
{
}

void nb::gui::Window::show()
{
}

void nb::gui::Window::hide()
{
}

void nb::gui::Window::close()
{
}
