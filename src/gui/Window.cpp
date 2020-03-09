﻿#include "newbrush/gui/Window.h"
#include "newbrush/gles/Projection.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gui/VisualTreeHelper.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/gui/WindowCollection.h"
#include "newbrush/core/Singleton.h"
#include "newbrush/core/Log.h"
#include "newbrush/media/Bitmap.h"
#include "GLFW/glfw3.h"

using namespace nb;

Viewport2D Window::drawContext;
static bool	g_windowSystemInitialized = false;

//glfw document：https://www.glfw.org/docs/latest/window_guide.html#window_windowed_full_screen
Window::Window()
	: m_implWindow(nullptr)
	, m_dispatchingCloseEvent(false)
	, m_processingCallback(false)
	, m_processingWindowStateChanged(false)
	, m_lastWindowState(WindowStateE::Normal)
{
	init();

	m_implWindow = glfwCreateWindow(800, 600, "newbrush", nullptr, nullptr);
	int x, y, w, h;
	glfwGetWindowPos(m_implWindow, &x, &y);
	glfwGetWindowSize(m_implWindow, &w, &h);
	//一定不能去掉下面四句（需要在回调生效前设置）以便不触发回调，否则会更新layout，而此时Width或Height是NAN（目前不需要了）
	setValue(LeftProperty(), (float)x);
	setValue(TopProperty(), (float)y);
	setValue(WidthProperty(), (float)w);
	setValue(HeightProperty(), (float)h);
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
	glfwSetWindowMaximizeCallback(m_implWindow, [](GLFWwindow * w, int maximized) { static_cast<Window *>(glfwGetWindowUserPointer(w))->maximizeCallback(maximized); });

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
	if(m_implWindow)
		glfwFocusWindow(m_implWindow);
}

void Window::show()
{
	if (m_implWindow)
		glfwShowWindow(m_implWindow);
}

void Window::hide()
{
	if (m_implWindow)
		glfwHideWindow(m_implWindow);
}

void Window::close()
{
	_close(true);
}

Point Window::getMousePosition() const
{
	double x = 0, y = 0;
	glfwGetCursorPos(m_implWindow, &x, &y);
	return Point((float)x, (float)y);
}

Size Window::measureOverride(const Size & availableSize)
{
	auto content = getValue<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		auto w = getValue<float>(WidthProperty());
		auto h = getValue<float>(HeightProperty());
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
	auto content = getValue<std::shared_ptr<UIElement>>(ContentProperty());
	if (content)
	{
		auto w = getValue<float>(WidthProperty());
		auto h = getValue<float>(HeightProperty());
		content->arrage(Rect(0.0, 0.0, w, h));
	}
	return finalSize;
}

void loopTree(UIElement *e, std::vector<UIElement *> &elements)
{
	elements.push_back(e);
	auto childrenCount = VisualTreeHelper::getChildrenCount(e);
	for (int i = 0; i != childrenCount; ++i)
	{
		auto child = VisualTreeHelper::getChild(e, i);
		if (VisualTreeHelper::getChildrenCount(child) > 0)
		{
			loopTree(child, elements);
		}
	}
};

void Window::_close(bool eraseFromCollection)
{
	if (m_dispatchingCloseEvent)
		return;

	m_dispatchingCloseEvent = true;
	CancelEventArgs args;
	onClosing(args);
	if (!args.cancel)
	{
		destroyWindow();
		onClosed(args);
		if(eraseFromCollection)
			Singleton<WindowCollection>::get()->erase(this);
	}
	m_dispatchingCloseEvent = false;
}

void Window::posCallback(int x, int y)
{
	LocationChanged.invoke({});
}

void Window::sizeCallback(int width, int height)
{
	drawContext.projection.ortho(0.0f, (float)width, (float)height, 0.0f, 1000.0f, -1000.0f);
	drawContext.viewport(0, 0, width, height);
	setValue(WidthProperty(), (float)width);
	setValue(HeightProperty(), (float)height);
	updateLayout();
}

void Window::frameBufferSizeCallback(int width, int height)
{
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
	auto changedButton = button == GLFW_MOUSE_BUTTON_1 ? MouseButtonE::Left : button == GLFW_MOUSE_BUTTON_2 ? MouseButtonE::Right : MouseButtonE::Middle;
	MouseButtonEventArgs e(0, changedButton);
	e.ButtonState = action == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	e.LeftButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	e.RightButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	e.MiddleButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;

	double x = 0, y = 0;
	glfwGetCursorPos(m_implWindow, &x, &y);
	std::vector<UIElement *> elements;
	loopTree(this, elements);
	for (auto uie : elements)
	{
		uie->onMouseButtonThunk(e, Point((float)x, (float)y));
	}
}

void Window::cusorPosCallback(double x, double y)
{
	MouseEventArgs e(0);
	e.LeftButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	e.RightButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	e.MiddleButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;

	std::vector<UIElement *> elements;
	loopTree(this, elements);
	for (auto uie : elements)
	{
		uie->onMouseMoveThunk(e, Point((float)x, (float)y));
	}
}

void Window::cusorPosEnterCallback(int entered)
{
	MouseEventArgs args(0);
	args.LeftButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	args.RightButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	args.MiddleButton = glfwGetMouseButton(m_implWindow, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS ? MouseButtonStateE::Pressed : MouseButtonStateE::Released;
	if (entered)
	{
		onMouseEnter(args);
	}
	else
	{
		onMouseLeave(args);
	}
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
	m_processingCallback = true;
	if (!m_processingWindowStateChanged)	//如果从WindowStateChanged来的，则不再setValue
	{
		setValue(WindowStateProperty(), iconified ? WindowStateE::Minimized : m_lastWindowState);
	}
	m_processingCallback = false;
}

void Window::maximizeCallback(int maximized)
{
	m_processingCallback = true;
	if (!m_processingWindowStateChanged)
	{
		setValue(WindowStateProperty(), maximized ? WindowStateE::Maximized : WindowStateE::Normal);
	}
	m_processingCallback = false;
}

void Window::init()
{
	if (g_windowSystemInitialized)	return;

	glfwSetErrorCallback([](int error, const char*str) {printf("error:%s\n", str); });
	glfwInit();
	//以下两句在有些电脑上导致glfwDestroyWindow挂死，放在库外不会挂死，目前暂未找到原因
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
	if (m_implWindow)
	{
		glfwDestroyWindow(m_implWindow);
		m_implWindow = nullptr;
		if (Singleton<WindowCollection>::get()->windows().empty())
			deinit();
	}
}

void Window::swapBuffers() const
{
	glfwMakeContextCurrent(m_implWindow);
//	glClearColor(250 / 255.0f, 235 / 255.0f, 215 / 255.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapBuffers(m_implWindow);
}

void Window::pollEvents()
{
	if (g_windowSystemInitialized)
		glfwWaitEvents();	//与glfwWaitEvents不同，glfwWaitEvents会阻塞（glfwWaitEvents CPU消耗很低，glfwPollEvents则很高30%以上）
}

DependencyProperty Window::WindowStateProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStateE>("WindowState", WindowStateE::Normal, [](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		auto w = dynamic_cast<Window *>(obj)->m_implWindow;
		if (!w)	return;

		auto oldState = args->oldValue.extract<WindowStateE>();
		auto newState = args->newValue.extract<WindowStateE>();
		if (oldState == newState)
		{
			return;
		}
		dynamic_cast<Window *>(obj)->m_lastWindowState = oldState;
		if (!dynamic_cast<Window *>(obj)->m_processingCallback)
		{
			dynamic_cast<Window *>(obj)->m_processingWindowStateChanged = true;
			switch (newState)
			{	
			//这里多加一个glfwMaximizeWindow的原因，是当出现连续设置glfwMaximizeWindow、glfwIconifyWindow、glfwRestoreWindow时，
			//glfw恢复到了max状态，这和预期是不符合的，可能是一个bug；在glfwRestoreWindow前加一个glfwMaximizeWindow则可以保证恢复到normal状态
			case WindowStateE::Normal:		glfwMaximizeWindow(w); glfwRestoreWindow(w);	break;
			case WindowStateE::Maximized:	glfwMaximizeWindow(w);	break;
			case WindowStateE::Minimized:	glfwIconifyWindow(w);	break;
			default:												break;
			}
			dynamic_cast<Window *>(obj)->m_processingWindowStateChanged = false;
		}
		dynamic_cast<Window *>(obj)->onStateChanged({});
	});
	return dp;
}

DependencyProperty Window::WindowStyleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, WindowStyleE>("WindowStyle", WindowStyleE::SizeBox, [&](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		auto oldStyle = args->oldValue.extract<WindowStyleE>();
		auto newStyle = args->newValue.extract<WindowStyleE>();
		if (oldStyle == newStyle)
			return;

		auto w = dynamic_cast<Window *>(obj)->m_implWindow;
		switch (newStyle)
		{
		case WindowStyleE::None:	glfwSetWindowAttrib(w, GLFW_DECORATED, false);	glfwSetWindowAttrib(w, GLFW_RESIZABLE, true);	break;
		case WindowStyleE::Fixed:	glfwSetWindowAttrib(w, GLFW_DECORATED, true);	glfwSetWindowAttrib(w, GLFW_RESIZABLE, false);	break;
		case WindowStyleE::SizeBox:	glfwSetWindowAttrib(w, GLFW_DECORATED, true);	glfwSetWindowAttrib(w, GLFW_RESIZABLE, true);	break;
		default:																													break;
		}
	});
	return dp;
}

DependencyProperty Window::TopmostProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, bool>("Topmost", false, [&](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		if(dynamic_cast<Window *>(obj)->m_implWindow)
			glfwSetWindowAttrib(dynamic_cast<Window *>(obj)->m_implWindow, GLFW_FLOATING, args->newValue.extract<bool>());
	});
	return dp;
}

DependencyProperty Window::LeftProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Left", 0.0, [&](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		if (dynamic_cast<Window *>(obj)->m_implWindow)
			glfwSetWindowPos(dynamic_cast<Window *>(obj)->m_implWindow, (int)obj->getValue<float>(LeftProperty()), (int)obj->getValue<float>(TopProperty()));
	});
	return dp;
}

DependencyProperty Window::TopProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, float>("Top", 0.0, [&](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		if (dynamic_cast<Window *>(obj)->m_implWindow)
			glfwSetWindowPos(dynamic_cast<Window *>(obj)->m_implWindow, (int)obj->getValue<float>(LeftProperty()), (int)obj->getValue<float>(TopProperty()));
	});
	return dp;
}

DependencyProperty Window::TitleProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, std::string>("Title", std::string(), [](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		if (dynamic_cast<Window *>(obj)->m_implWindow)
			glfwSetWindowTitle(dynamic_cast<Window *>(obj)->m_implWindow, args->newValue.extract<std::string>().data());
	});
	return dp;
}

DependencyProperty Window::IconProperty()
{
	static auto dp = DependencyProperty::registerDependency<Window, std::shared_ptr<ImageSource>>("Icon", nullptr, [](DependencyObject *obj, DependencyPropertyChangedEventArgs *args) {
		auto source = args->newValue.extract<std::shared_ptr<ImageSource>>();
		Bitmap bm = source ? source->bitmap() : Bitmap();
		GLFWimage img;
		img.width = bm.width();
		img.height = bm.height();
		img.pixels = (unsigned char *)bm.data();
		if (dynamic_cast<Window *>(obj)->m_implWindow)
		{
			glfwSetWindowIcon(dynamic_cast<Window *>(obj)->m_implWindow, 1, &img);
		}

	});
	return dp;
}

void Window::onPropertyChanged(const DependencyPropertyChangedEventArgs & args)
{
	ContentControl::onPropertyChanged(args);
	if (args.property == ContentProperty())
	{
		updateLayout();
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
