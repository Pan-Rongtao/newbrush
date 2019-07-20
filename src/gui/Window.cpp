#include "gui/Window.h"
#include "gles/Egl.h"
#include "core/Window.h"
#include "gles/Window.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include "gui/Application.h"
#include "WindowCollections.h"

using namespace nb::core;
using namespace nb::gl;
using namespace nb::gui;

nb::core::Property_rw<std::shared_ptr<nb::gl::Context>>	nb::gui::Window::DrawContext;
nb::gui::Window::Window()
	: WindowState(WindowStateE::Normal)
	, WindowStyle(WindowStyleE::SizeBox)
	, m_glWindow(std::make_shared<nb::gl::Window>(800, 600))
{
	DrawContext = std::make_shared<nb::gl::Context>(nb::gl::getConfigure());
	Left = (float)m_glWindow->x();
	Top = (float)m_glWindow->y();
	Width = (float)m_glWindow->width();
	Height = (float)m_glWindow->height();

	auto onWindowResized = [&](const nb::core::Window::ResizeArgs & args)
	{
		auto ratio = (float)args.width / args.height;
		nb::gl::getProjection()->perspective(45.0f, std::isnan(ratio) ? 0.0f : ratio, 0.1f, 10000.0f);
		nb::gl::getCamera()->lookat2D((float)args.width, (float)args.height);
		nb::gl::viewport(0, 0, args.width, args.height);
		Width = args.width;
		Height = args.height;
		updateLayout();
	};
	m_glWindow->ResizeEvent.addHandler(std::bind(onWindowResized, std::placeholders::_1));
	onWindowResized({ (int)Width, (int)Height });

	WindowState.notify(std::bind(&Window::onWindowStateChanged, this, std::placeholders::_1, std::placeholders::_2));
	WindowStyle.notify(std::bind(&Window::onWindowStyleChanged, this, std::placeholders::_1, std::placeholders::_2));
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
	m_glWindow->active();
}

void nb::gui::Window::show()
{
	m_glWindow->show(true);
}

void nb::gui::Window::hide()
{
	m_glWindow->show(false);
}

void nb::gui::Window::close()
{
	m_glWindow = nullptr;
}

void nb::gui::Window::onWindowStateChanged(const core::WindowStateE & _old, const core::WindowStateE & _new)
{
	m_glWindow->setWindowState(_new);
}

void nb::gui::Window::onWindowStyleChanged(const core::WindowStyleE & _old, const core::WindowStyleE & _new)
{
	m_glWindow->setWindowStyle(_new);
}

void nb::gui::Window::onTopmostChanged(const bool & _old, const bool & _new)
{
	m_glWindow->setTopMost(_new);
}

void nb::gui::Window::onLeftChanged(const float & _old, const float & _new)
{
	m_glWindow->setX((int)_new);
}

void nb::gui::Window::onTopChanged(const float & _old, const float & _new)
{
	m_glWindow->setY((int)_new);
}

void nb::gui::Window::onWidthChanged(const float & _old, const float & _new)
{
	m_glWindow->setWidth((int)_new);
}

void nb::gui::Window::onHeightChanged(const float & _old, const float & _new)
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
