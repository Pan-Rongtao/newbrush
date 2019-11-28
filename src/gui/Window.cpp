#include "gui/Window.h"
#include "GLFW/glfw3.h"
#include "gles/Egl.h"
#include "gles/Projection.h"
#include "gui/Application.h"
#include "gui/VisualTreeHelper.h"
#include "media/ImageSource.h"

using namespace nb;
using namespace nb::gl;
using namespace nb::gui;

std::shared_ptr<nb::gl::Context> Window::drawContext = nullptr;
Window::Window()
	: WindowState([&](WindowStateE v) {set(WindowStateProperty(), v); }, [&]()->WindowStateE& {return get<WindowStateE>(WindowStateProperty()); })
	, WindowStyle([&](WindowStyleE v) {set(WindowStyleProperty(), v); }, [&]()->WindowStyleE& {return get<WindowStyleE>(WindowStyleProperty()); })
	, Topmost([&](bool v) {set(TopmostProperty(), v); }, [&]()->bool& {return get<bool>(TopmostProperty()); })
	, Left([&](float v) {set(LeftProperty(), v); }, [&]()->float& {return get<float>(LeftProperty()); })
	, Top([&](float v) {set(TopProperty(), v); }, [&]()->float& {return get<float>(TopProperty()); })
	, Title([&](std::string v) {set(TitleProperty(), v); }, [&]()->std::string& {return get<std::string>(TitleProperty()); })
	, Icon([&](shared_ptr<ImageSource> v) {set(IconProperty(), v); }, [&]()->shared_ptr<ImageSource>& {return get<shared_ptr<ImageSource>>(IconProperty()); })
	, m_implWindow(nullptr)
{
	drawContext = std::make_shared<nb::gl::Context>();
	m_implWindow = glfwCreateWindow(800, 600, "newbrush", nullptr, nullptr);
	int x, y, w, h;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwGetWindowSize(m_implWindow, &w, &h);
	//一定不能去掉下面四句（需要在回调生效前设置）以便不触发回调，否则会更新layout，而此时Width或Height是NAN
	Left = (float)x;
	Top = (float)y;
	Width = (float)w;
	Height = (float)h;
	glfwSetWindowUserPointer(m_implWindow, this);
	glfwSetWindowPosCallback(m_implWindow, [](GLFWwindow*w, int x, int y) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->posCallback(x, y); });
	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetFramebufferSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetMouseButtonCallback(m_implWindow, [](GLFWwindow*w, int button, int action, int mods) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->mouseButtonCallback(button, action, mods); });
	glfwSetCursorPosCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->cusorPosCallback(x, y); });
	glfwSetCursorEnterCallback(m_implWindow, [](GLFWwindow*w, int entered) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->cusorPosEnterCallback(entered); });
	glfwSetScrollCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->scrollCallback(x, y); });
	glfwSetKeyCallback(m_implWindow, [](GLFWwindow*w, int key, int scancode, int action, int mods) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->keyCallback(key, scancode, action, mods); });
	glfwSetWindowFocusCallback(m_implWindow, [](GLFWwindow*w, int focused) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->focusCallback(focused); });
	glfwSetWindowRefreshCallback(m_implWindow, [](GLFWwindow*w) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->refreshCallback(); });
	glfwSetWindowCloseCallback(m_implWindow, [](GLFWwindow*w) { static_cast<gui::Window *>(glfwGetWindowUserPointer(w))->closeCallback(); });

	glfwMakeContextCurrent(m_implWindow);
	sizeCallback(Width(), Height());
	Application::current()->windows().push_back(this);
}

Window::~Window()
{
	auto iter = std::find(Application::current()->windows().begin(), Application::current()->windows().end(), this);
	if (iter != Application::current()->windows().end())
		Application::current()->windows().erase(iter);
	glfwDestroyWindow(m_implWindow);
}

void Window::active()
{
	glfwFocusWindow(m_implWindow);
}

void Window::show()
{
	glfwShowWindow(m_implWindow);
}

void Window::hide()
{
	glfwHideWindow(m_implWindow);
}

void Window::close()
{
	glfwSetWindowShouldClose(m_implWindow, 1);
}

Size Window::measureOverride(const Size & availableSize)
{
	if (Content())
	{
		Content()->measure({ Width(), Height() });
		//return Content()->DesiredSize;
		return availableSize;
	}
	else
	{
		return ContentControl::measureOverride(availableSize);
	}
}

Size Window::arrangeOverride(const Size & finalSize)
{
	if (Content())
	{
		Content()->arrage(Rect(0.0, 0.0, Width(), Height()));
	}
	return finalSize;
}

void loopTest(int x, int y, std::shared_ptr<Window> w, UIElement *e, std::vector<UIElement *> &hits)
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

std::vector<UIElement *> Window::hitElements(int x, int y) const
{
	std::vector<UIElement *> hits;
	//loopTest(x, y, m_glWindow, const_cast<Window *>(this), hits);
	return hits;
}

void Window::onWindowStateChanged(const WindowStateE & _old, const WindowStateE & _new)
{
	//m_glWindow->setWindowState(_new);
}

void Window::onWindowStyleChanged(const WindowStyleE & _old, const WindowStyleE & _new)
{
	//m_glWindow->setWindowStyle(_new);
}

void Window::onTopmostChanged(const bool & _old, const bool & _new)
{
	//m_glWindow->setTopMost(_new);
}

void Window::onLeftChanged(const float & _old, const float & _new)
{
	int x, y;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwSetWindowPos(m_implWindow, _new, y);
}

void Window::onTopChanged(const float & _old, const float & _new)
{
	int x, y;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwSetWindowPos(m_implWindow, x, _new);
}

void Window::onWidthChanged(const float & _old, const float & _new)
{
	int w, h;
	glfwGetWindowSize(m_implWindow, &w, &h);
	glfwSetWindowSize(m_implWindow, _new, h);
}

void Window::onHeightChanged(const float & _old, const float & _new)
{
	int w, h;
	glfwGetWindowSize(m_implWindow, &w, &h);
	glfwSetWindowSize(m_implWindow, w, _new);
}

void Window::posCallback(int x, int y)
{
}

void Window::sizeCallback(int width, int height)
{
	nb::gl::getProjection()->ortho(0.0f, (float)width, (float)height, 0.0f, 1000.0f, -1000.0f);
	nb::gl::viewport(0, 0, width, height);
	Width = width;
	Height = height;
	updateLayout();
}

void Window::frameBufferSizeCallback(int width, int height)
{
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		double x, y;
		glfwGetCursorPos(m_implWindow, &x, &y);
		auto hits = hitElements(x, y);
		for (auto e : hits)
		{
			e->MouseEnter.dispatch({});
			e->onMouseEnter();
			e->MouseMove.dispatch({});
			e->onMouseMove();
		}
	}
}

void Window::cusorPosCallback(double x, double y)
{
}

void Window::cusorPosEnterCallback(int entered)
{
}

void Window::scrollCallback(double x, double y)
{
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
}

void Window::focusCallback(int focused)
{
}

void Window::refreshCallback()
{
}

void Window::closeCallback()
{
}

void Window::init()
{
	glfwSetErrorCallback([](int error, const char*str) {printf("error:%s\n", str); });
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}

void Window::deinit()
{
	glfwTerminate();
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_implWindow) != 0;
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_implWindow);
}

void Window::waitEvent()
{
	glfwWaitEvents();
}

void Window::onTitleChanged(const std::string & _old, const std::string & _new)
{
	glfwSetWindowTitle(m_implWindow, _new.data());
}

void Window::onIconChanged(const std::shared_ptr<ImageSource>& _old, const std::shared_ptr<ImageSource>& _new)
{

}

DependencyProperty Window::WindowStateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStateE>("WindowState", WindowStateE::Normal);
	return dp;
}

DependencyProperty Window::WindowStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStyleE>("WindowStyle", WindowStyleE::SizeBox);
	return dp;
}

DependencyProperty Window::TopmostProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, bool>("Topmost", false);
	return dp;
}

DependencyProperty Window::LeftProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Left", 0.0);
	return dp;
}

DependencyProperty Window::TopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Top", 0.0);
	return dp;
}

DependencyProperty Window::TitleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, std::string>("Title", std::string());
	return dp;
}

DependencyProperty Window::IconProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, shared_ptr<ImageSource>>("Icon", std::make_shared<ImageSource>());
	return dp;
}
