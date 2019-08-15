#include "gui/Window.h"
#include "gles/Egl.h"
#include "core/Window.h"
#include "gles/Window.h"
#include "gles/Projection.h"
#include "gles/Camera.h"
#include "gui/Application.h"
#include "WindowCollections.h"
#include "../src/gles/EglMaster.h"
#include "gui/VisualTreeHelper.h"

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

	m_glWindow->ResizeEvent += std::bind(&Window::onNativeWindowResize, this, std::placeholders::_1);
	m_glWindow->MouseEnterEvent += std::bind(&Window::onNativeWindowMouseEnter, this, std::placeholders::_1);
	m_glWindow->MouseLeaveEvent += std::bind(&Window::onNativeWindowMouseLeave, this, std::placeholders::_1);
	m_glWindow->MouseMoveEvent += std::bind(&Window::onNativeWindowMouseMove, this, std::placeholders::_1);
	m_glWindow->MouseLeftButtonEvent += std::bind(&Window::onNativeWindowMouseLeftButton, this, std::placeholders::_1);
	m_glWindow->MouseRightButtonEvent += std::bind(&Window::onNativeWindowMouseRightButton, this, std::placeholders::_1);
	m_glWindow->MouseMiddleButtonEvent += std::bind(&Window::onNativeWindowMouseMiddleButton, this, std::placeholders::_1);
	m_glWindow->MouseWheelEvent += std::bind(&Window::onNativeWindowMouseWheel, this, std::placeholders::_1);
	m_glWindow->KeyEvent += std::bind(&Window::onNativeWindowKeyAction, this, std::placeholders::_1);

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
	onNativeWindowResize({ (int)Width, (int)Height });
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

nb::core::Size nb::gui::Window::measureOverride(const nb::core::Size & availableSize)
{
	if (Content())
	{
		Content()->measure({ (float)m_glWindow->clientWidth(), (float)m_glWindow->clientHeight() });
		//return Content()->DesiredSize;
		return availableSize;
	}
	else
	{
		return ContentControl::measureOverride(availableSize);
	}
}

nb::core::Size nb::gui::Window::arrangeOverride(const nb::core::Size & finalSize)
{
	if (Content())
	{
		Content()->arrage(Rect(0.0, 0.0, (float)m_glWindow->clientWidth(), (float)m_glWindow->clientHeight()));
	}
	return finalSize;
}

void loopTest(int x, int y, std::shared_ptr<nb::gl::Window> w, UIElement *e, std::vector<UIElement *> &hits)
{
	auto hit = [x, y, w](std::shared_ptr<RenderObject> obj)
	{
		if (!obj || obj->model() == nullptr)	return false;
		return obj->model()->orthoHitTest((float)x, (float)y);
	};

	auto count = VisualTreeHelper::getChildCount(e);
	for (int i = 0; i != count; ++i)
	{
		auto child = VisualTreeHelper::getChild(e, i);
		if (!child)	continue;
		if (hit(child->Renderer()))
			hits.push_back(child);
		if (VisualTreeHelper::getChildCount(child) > 0)
		{
			loopTest(x, y, w, child, hits);
		}
	}
};

std::vector<UIElement *> nb::gui::Window::hitElements(int x, int y) const
{
	std::vector<UIElement *> hits;
	loopTest(x, y, m_glWindow, const_cast<nb::gui::Window *>(this), hits);
	return hits;
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

void nb::gui::Window::onNativeWindowResize(const core::Window::ResizeArgs & args)
{
	auto w = (float)m_glWindow->clientWidth();
	auto h = m_glWindow->clientHeight();
	auto ratio = w / h;
	nb::gl::getProjection()->ortho(0.0f, (float)w, (float)h, 0.0f, 1000.0f, -1000.0f);
	nb::gl::viewport(0, 0, m_glWindow->clientWidth(), m_glWindow->clientHeight());
	Width = (float)args.width;
	Height = (float)args.height;
	updateLayout();
}

void nb::gui::Window::onNativeWindowMouseEnter(const core::Window::MouseEnterEventArgs & args)
{
}

void nb::gui::Window::onNativeWindowMouseLeave(const core::Window::MouseLeaveEventArgs & args)
{
}

void nb::gui::Window::onNativeWindowMouseMove(const core::Window::MouseMoveEventArgs & args)
{
	auto hits = hitElements(args.x, args.y);
	for (auto e : hits)
	{
		e->MouseEnter.dispatch({});
		e->onMouseEnter();
		e->MouseMove.dispatch({});
		e->onMouseMove();
	}
}

void nb::gui::Window::onNativeWindowMouseLeftButton(const core::Window::MouseLeftButtonEventArgs & args)
{
	auto hits = hitElements(args.x, args.y);
	if (args.pressed)
	{
		for (auto e : hits)
		{
			e->MouseLeftButtonDown.dispatch({});
			e->MouseDown.dispatch({});
			e->onMouseLeftButtonDown();
			e->onMouseDown();
		}
	}
	else
	{
		for (auto e : hits)
		{
			e->MouseLeftButtonUp.dispatch({});
			e->MouseUp.dispatch({});
			e->onMouseLeftButtonUp();
			e->onMouseUp();
		}
	}
}

void nb::gui::Window::onNativeWindowMouseRightButton(const core::Window::MouseRightButtonEventArgs & args)
{
}

void nb::gui::Window::onNativeWindowMouseMiddleButton(const core::Window::MouseMiddleButtonEventArgs & args)
{
}

void nb::gui::Window::onNativeWindowMouseWheel(const core::Window::MouseWheelEventArgs & args)
{
}

void nb::gui::Window::onNativeWindowKeyAction(const core::Window::KeyEventArgs & args)
{
}

void nb::gui::Window::onTitleChanged(const std::string & _old, const std::string & _new)
{
	m_glWindow->setTitle(_new);
}

void nb::gui::Window::onIconChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{

}
