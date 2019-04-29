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
	auto windowSurface = std::make_shared<nb::gl::WindowSurface>(m_glWindow->width(), m_glWindow->height(), m_glWindow->handle());
	auto context = std::make_shared<nb::gl::Context>(nb::gl::getCurrentConfigure());
	nb::gl::makeCurrent(windowSurface, windowSurface, context);

	WindowState.notify([&](const gui::WindowState &_old, const gui::WindowState &_new) {

	});
	Topmost.notify([&](const bool &_old, const bool &_new) {

	});
	Left.notify([&](const double &_old, const double &_new) {
		m_glWindow->setX((int)_new);
	});
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
