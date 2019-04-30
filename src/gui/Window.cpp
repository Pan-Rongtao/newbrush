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

	WindowState.notify(std::bind(&Window::onWindowStateChanged, this, std::placeholders::_1, std::placeholders::_2));
	Topmost.notify(std::bind(&Window::onTopmostChanged, this, std::placeholders::_1, std::placeholders::_2));
	Left.notify(std::bind(&Window::onLeftChanged, this, std::placeholders::_1, std::placeholders::_2));
	Top.notify(std::bind(&Window::onTopChanged, this, std::placeholders::_1, std::placeholders::_2));
	Width.notify(std::bind(&Window::onWidthChanged, this, std::placeholders::_1, std::placeholders::_2));
	Height.notify(std::bind(&Window::onHeightChanged, this, std::placeholders::_1, std::placeholders::_2));
	Title.notify(std::bind(&Window::onTitleChanged, this, std::placeholders::_1, std::placeholders::_2));
	Icon.notify(std::bind(&Window::onIconChanged, this, std::placeholders::_1, std::placeholders::_2));
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

void nb::gui::Window::onWindowStateChanged(const gui::WindowState & _old, const gui::WindowState & _new)
{
}

void nb::gui::Window::onTopmostChanged(const bool & _old, const bool & _new)
{
}

void nb::gui::Window::onLeftChanged(const double & _old, const double & _new)
{
	m_glWindow->setX((int)_new);
}

void nb::gui::Window::onTopChanged(const double & _old, const double & _new)
{
	m_glWindow->setY((int)_new);
}

void nb::gui::Window::onWidthChanged(const double & _old, const double & _new)
{
	m_glWindow->setWidth((int)_new);
}

void nb::gui::Window::onHeightChanged(const double & _old, const double & _new)
{
	m_glWindow->setHeight((int)_new);
}

void nb::gui::Window::onTitleChanged(const std::string & _old, const std::string & _new)
{
	m_glWindow->setTitle(_new);
}

void nb::gui::Window::onIconChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{

}
