#include "gui/Window.h"
#include "gles/Egl.h"
#include "gles/Window.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include "gui/Application.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

nb::gui::Window::Window()
	: WindowState(WindowState::Normal)
	, m_glWindow(std::make_shared<nb::gl::Window>(800.0, 600.0))
	, DrawContext(std::make_shared<nb::gl::Context>(nb::gl::getConfigure()))
{
	Width = m_glWindow->width();
	Height = m_glWindow->height();
	onWidthChanged(0.0, Width);
	onHeightChanged(0.0, Height);

	WindowState.notify(std::bind(&Window::onWindowStateChanged, this, std::placeholders::_1, std::placeholders::_2));
	Topmost.notify(std::bind(&Window::onTopmostChanged, this, std::placeholders::_1, std::placeholders::_2));
	Left.notify(std::bind(&Window::onLeftChanged, this, std::placeholders::_1, std::placeholders::_2));
	Top.notify(std::bind(&Window::onTopChanged, this, std::placeholders::_1, std::placeholders::_2));
	Width.notify(std::bind(&Window::onWidthChanged, this, std::placeholders::_1, std::placeholders::_2));
	Height.notify(std::bind(&Window::onHeightChanged, this, std::placeholders::_1, std::placeholders::_2));
	Title.notify(std::bind(&Window::onTitleChanged, this, std::placeholders::_1, std::placeholders::_2));
	Icon.notify(std::bind(&Window::onIconChanged, this, std::placeholders::_1, std::placeholders::_2));

	WindowCollections::Windows().push_back(this);
	DrawSurface = std::make_shared<nb::gl::WindowSurface>(m_glWindow->width(), m_glWindow->height(), m_glWindow->handle());
	nb::gl::makeCurrent(DrawSurface, DrawSurface, DrawContext);
}

nb::gui::Window::~Window()
{
	auto iter = std::find(WindowCollections::Windows().begin(), WindowCollections::Windows().end(), this);
	if (iter != WindowCollections::Windows().end())
		WindowCollections::Windows().erase(iter);
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
	nb::gl::viewport(0, 0, (unsigned int)Width, (unsigned int)Height);
	nb::gl::getProjection()->perspective(45.0f, (float)(Width / Height), 0.1f, 10000.0f);
	nb::gl::getCamera()->lookat2D(Width, Height);
}

void nb::gui::Window::onHeightChanged(const double & _old, const double & _new)
{
	m_glWindow->setHeight((int)_new);
	nb::gl::viewport(0, 0, (unsigned int)Width, (unsigned int)Height);
	nb::gl::getProjection()->perspective(45.0f, (float)(Width / Height), 0.1f, 10000.0f);
	nb::gl::getCamera()->lookat2D(Width, Height);
}

void nb::gui::Window::onTitleChanged(const std::string & _old, const std::string & _new)
{
	m_glWindow->setTitle(_new);
}

void nb::gui::Window::onIconChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{

}
