#include "gui/Window.h"
#include "core/Exception.h"
#include "gles/Egl.h"
#include "gles/Window.h"
#include "gui/Application.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include "gles/Gl.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

nb::gui::Window::Window()
{
	Width = 800.0;
	Height = 600.0;
	m_glWindow = std::make_shared<nb::gl::Window>();
	m_glWindow->setWidth(Width);
	m_glWindow->setHeight(Height);
	DrawSurface = std::make_shared<nb::gl::WindowSurface>(m_glWindow->width(), m_glWindow->height(), m_glWindow->handle());
	DrawContext = std::make_shared<nb::gl::Context>(nb::gl::getCurrentConfigure());
	nb::gl::makeCurrent(DrawSurface, DrawSurface, DrawContext);

	static Vec3 cameraPosition(0.0, 0.0, 3.0);
	static Vec3 cameraFront(0.0f, 0.0f, -1.0f);
	static Vec3 cameraUp(0.0f, 1.0f, 0.0f);
	Projection::instance()->perspective(45.0f, Width / Height, 0.1f, 10000.0f);

	float z = (float)Height / (float)(2 * tanf((22.5f * 3.1415926f) / 180.0f));
	Vec3 position((float)Width / 2.0f, Height / 2.0f, -z);
	Vec3 target((float)Width / 2.0f, Height / 2.0f, 0.0f);
	Vec3 upVec(0.0f, -1.0f, 0.0f);
//	if (g_Original)
//		Camera::instance()->lookat(cameraPosition, cameraPosition + cameraFront, cameraUp);
//	else
		Camera::instance()->lookat(position, target, upVec);

	nb::gl::Viewport(0, 0, Width, Height);

	WindowState.notify(std::bind(&Window::onWindowStateChanged, this, std::placeholders::_1, std::placeholders::_2));
	Topmost.notify(std::bind(&Window::onTopmostChanged, this, std::placeholders::_1, std::placeholders::_2));
	Left.notify(std::bind(&Window::onLeftChanged, this, std::placeholders::_1, std::placeholders::_2));
	Top.notify(std::bind(&Window::onTopChanged, this, std::placeholders::_1, std::placeholders::_2));
	Width.notify(std::bind(&Window::onWidthChanged, this, std::placeholders::_1, std::placeholders::_2));
	Height.notify(std::bind(&Window::onHeightChanged, this, std::placeholders::_1, std::placeholders::_2));
	Title.notify(std::bind(&Window::onTitleChanged, this, std::placeholders::_1, std::placeholders::_2));
	Icon.notify(std::bind(&Window::onIconChanged, this, std::placeholders::_1, std::placeholders::_2));

	WindowCollections::Windows().push_back(this);
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
