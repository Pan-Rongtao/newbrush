#include "gui/Window.h"
#include "GLFW/glfw3.h"
#include "gles/Projection.h"
#include "gui/Application.h"
#include "gui/VisualTreeHelper.h"
#include "media/ImageSource.h"
#include "gui/WindowCollection.h"
#include "core/Singleton.h"
#include "core/Log.h"

using namespace nb;
using namespace gui;

Viewport2D Window::drawContext;
static bool	g_windowSystemInitialized = false;

Window::Window()
	: m_implWindow(nullptr)
{
	init();

	m_implWindow = glfwCreateWindow(800, 600, "newbrush", nullptr, nullptr);
	int x, y, w, h;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwGetWindowSize(m_implWindow, &w, &h);
	//一定不能去掉下面四句（需要在回调生效前设置）以便不触发回调，否则会更新layout，而此时Width或Height是NAN
	set(LeftProperty(), (float)x);
	set(TopProperty(), (float)y);
	set(WidthProperty(), (float)w);
	set(HeightProperty(), (float)h);
	glfwSetWindowUserPointer(m_implWindow, this);
	glfwSetWindowPosCallback(m_implWindow, [](GLFWwindow*w, int x, int y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->posCallback(x, y); });
	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetFramebufferSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetMouseButtonCallback(m_implWindow, [](GLFWwindow*w, int button, int action, int mods) { static_cast<Window *>(glfwGetWindowUserPointer(w))->mouseButtonCallback(button, action, mods); });
	glfwSetCursorPosCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->cusorPosCallback(x, y); });
	glfwSetCursorEnterCallback(m_implWindow, [](GLFWwindow*w, int entered) { static_cast<Window *>(glfwGetWindowUserPointer(w))->cusorPosEnterCallback(entered); });
	glfwSetScrollCallback(m_implWindow, [](GLFWwindow*w, double x, double y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->scrollCallback(x, y); });
	glfwSetKeyCallback(m_implWindow, [](GLFWwindow*w, int key, int scancode, int action, int mods) { static_cast<Window *>(glfwGetWindowUserPointer(w))->keyCallback(key, scancode, action, mods); });
	glfwSetWindowFocusCallback(m_implWindow, [](GLFWwindow*w, int focused) { static_cast<Window *>(glfwGetWindowUserPointer(w))->focusCallback(focused); });
	glfwSetWindowRefreshCallback(m_implWindow, [](GLFWwindow*w) { static_cast<Window *>(glfwGetWindowUserPointer(w))->refreshCallback(); });
	glfwSetWindowCloseCallback(m_implWindow, [](GLFWwindow*w) { static_cast<Window *>(glfwGetWindowUserPointer(w))->closeCallback(); });
	glfwSetWindowIconifyCallback(m_implWindow, [](GLFWwindow*w, int iconified) { static_cast<Window *>(glfwGetWindowUserPointer(w))->iconifyCallback(iconified); });
	glfwSetWindowMaximizeCallback(m_implWindow, [](GLFWwindow*w, int iconified) { static_cast<Window *>(glfwGetWindowUserPointer(w))->iconifyCallback(iconified); });

	glfwMakeContextCurrent(m_implWindow);
	sizeCallback((int)w, (int)h);
	Singleton<WindowCollection>::get()->push(this);

}

Window::~Window()
{
	destroyWindow();
	Singleton<WindowCollection>::get()->erase(this);
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
	_close(true);
}

Size Window::measureOverride(const Size & availableSize)
{
	auto content = get<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		auto w = get<float>(WidthProperty());
		auto h = get<float>(HeightProperty());
		content->measure({ w, h });
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
	auto content = get<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		auto w = get<float>(WidthProperty());
		auto h = get<float>(HeightProperty());
		content->arrage(Rect(0.0, 0.0, w, h));
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

		auto childRenderer = child->get<std::shared_ptr<RenderObject>>(UIElement::RendererProperty());
		if (hit(childRenderer))
		{
			hits.push_back(child);
		}

		if (VisualTreeHelper::getChildCount(child) > 0)
		{
			loopTest(x, y, w, child, hits);
		}
	}
};

void Window::_close(bool eraseFromCollection)
{
	if (m_onDispatching)	return;
	m_onDispatching = true;
	CancelEventArgs args;
	onClosing(args);
	if (!args.cancel)
	{
		destroyWindow();
		onClosed(args);
		if(eraseFromCollection)
			Singleton<WindowCollection>::get()->erase(this);
	}
	m_onDispatching = false;
}

std::vector<UIElement *> Window::hitElements(int x, int y) const
{
	std::vector<UIElement *> hits;
	//loopTest(x, y, m_glWindow, const_cast<Window *>(this), hits);
	return hits;
}

void Window::posCallback(int x, int y)
{
	LocationChanged.invoke({});
}

void Window::sizeCallback(int width, int height)
{
	drawContext.projection.ortho(0.0f, (float)width, (float)height, 0.0f, 1000.0f, -1000.0f);
	drawContext.viewport(0, 0, width, height);
	set(WidthProperty(), (float)width);
	set(HeightProperty(), (float)height);
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
		auto hits = hitElements((int)x, (int)y);
		for (auto e : hits)
		{
		//	e->MouseEnter.invoke({});
		//	e->onMouseEnter();
		//	e->MouseMove.invoke({});
		//	e->onMouseMove();
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
//	Focusable = focused;
}

void Window::refreshCallback()
{
	glfwMakeContextCurrent(m_implWindow);
	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{

		static int frames = 0;
		static uint64_t k = nb::getTickCount();
		drawContext.draw();

		++frames;
		uint64_t kk = nb::getTickCount();
		if (kk - k >= 2000)
		{
			float fps = frames * 1000.0f / (kk - k);
			frames = 0;
			k = kk;
			Log::info("fps:%.2f", fps);
		}
	}
	glfwSwapBuffers(m_implWindow);
}

void Window::closeCallback()
{
	close();
}

void Window::iconifyCallback(int iconified)
{
	StateChanged.invoke({});
}

void Window::maximizeCallback(GLFWwindow * window, int maximized)
{
	StateChanged.invoke({});
}

void Window::init()
{
	if (g_windowSystemInitialized)	return;

	glfwSetErrorCallback([](int error, const char*str) {printf("error:%s\n", str); });
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	g_windowSystemInitialized = true;
}

void Window::deinit()
{
	glfwTerminate();
	g_windowSystemInitialized = false;
}

void Window::destroyWindow()
{
	if (!m_implWindow)
		return;
	glfwDestroyWindow(m_implWindow);
	m_implWindow = nullptr;
	if (Singleton<WindowCollection>::get()->windows().empty())
		deinit();
}

void Window::swapBuffers() const
{
	glfwMakeContextCurrent(m_implWindow);
//	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(m_implWindow);
}

void Window::waitEvent()
{
	if (g_windowSystemInitialized)
		glfwWaitEvents();
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
	static auto dp = DependencyProperty::registerDependency<Window, std::shared_ptr<ImageSource>>("Icon", std::make_shared<ImageSource>());
	return dp;
}

void Window::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	if (args.property == WindowStateProperty())
	{
		auto state = args.newValue.extract<WindowStateE>();
		switch (state)
		{
		case WindowStateE::Normal:		glfwRestoreWindow(m_implWindow);	break;
		case WindowStateE::Maximized:	glfwMaximizeWindow(m_implWindow);	break;
		case WindowStateE::Minimized:	glfwIconifyWindow(m_implWindow);	break;
		default:															break;
		}
	}
	else if (args.property == WindowStyleProperty())
	{
	}
	else if (args.property == TopmostProperty())
	{
		glfwSetWindowAttrib(m_implWindow, GLFW_FLOATING, args.newValue.extract<bool>());
	}
	else if (args.property == LeftProperty() || args.property == TopProperty())
	{
		glfwSetWindowPos(m_implWindow, (int)get<float>(LeftProperty()), (int)get<float>(TopProperty()));
	}
	else if (args.property == TitleProperty())
	{
		glfwSetWindowTitle(m_implWindow, args.newValue.extract<std::string>().data());
	}
	else if (args.property == IconProperty())
	{
		auto source = args.newValue.extract<std::shared_ptr<ImageSource>>();
		auto bm = source->get<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
		GLFWimage img;
		img.width = bm->width();
		img.height = bm->height();
		img.pixels = (unsigned char *)bm->data();
		glfwSetWindowIcon(m_implWindow, 1, &img);
	}
}

void Window::onActivated(const EventArgs & args)
{
	Activated.invoke({ args });
}

void Window::onDeactivated(const EventArgs & args)
{
	Deactivated.invoke({ args });
}

void Window::onClosed(const EventArgs & args)
{
	Closed.invoke({ args });
}

void Window::onClosing(const CancelEventArgs & args)
{
	Closing.invoke({ args });
}

void Window::onLocationChanged(const EventArgs & args)
{
	LocationChanged.invoke({ args });
}

void Window::onStateChanged(const EventArgs & args)
{
	StateChanged.invoke({ args });
}

void Window::onSourceInitiallized(const EventArgs & args)
{
	SourceInitiallized.invoke({ args });
}

void Window::onContentRendered(const EventArgs & args)
{
	ContentRendered.invoke({ args });
}
