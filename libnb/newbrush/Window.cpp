#include "newbrush/Window.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "newbrush/Log.h"
#include "newbrush/Node2D.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"

using namespace nb;

static bool	g_windowSystemInitialized = false;

Window::Window()
	: Window(1280.0f, 720.0f, "newbrush")
{}

Window::Window(float width, float heith)
	: Window(width, heith, "newbrush")
{}

Window::Window(const std::string & title)
	: Window(1280.0f, 720.0f, title)
{}

Window::Window(float width, float height, const std::string &title)
	: m_dispatchingCloseEvent(false)
	, m_processingCallback(false)
	, m_processingWindowStateChanged(false)
	, m_lastWindowState(WindowStateE::Normal)
	, m_title(title)
{
#if NB_OS == NB_OS_ANDROID
	nbThrowException(std::runtime_error, "should not create Window on android");
#else
	init();

	m_implWindow = glfwCreateWindow((int)width, (int)height, title.data(), 0, 0);

	glfwSetWindowUserPointer(m_implWindow, this);
	glfwSetWindowPosCallback(m_implWindow, [](GLFWwindow*w, int x, int y) { static_cast<Window *>(glfwGetWindowUserPointer(w))->posCallback(x, y); });
	glfwSetWindowSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->sizeCallback(width, height); });
	glfwSetFramebufferSizeCallback(m_implWindow, [](GLFWwindow*w, int width, int height) { static_cast<Window *>(glfwGetWindowUserPointer(w))->frameBufferSizeCallback(width, height); });
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
	glfwSetDropCallback(m_implWindow, [](GLFWwindow * w, int count, const char* paths[]) { static_cast<Window *>(glfwGetWindowUserPointer(w))->dropCallback(count, paths); });

	glfwMakeContextCurrent(m_implWindow);
	gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress));
	WindowCollection::get()->push(this);
	glfwSwapInterval(1);
	frameBufferSizeCallback((int)width, (int)height);
	Log::info("{}", SystemHelper::getSystemInfos());
#endif
}
 
Window::~Window()
{
#if NB_OS != NB_OS_ANDROID
	destroyWindow();
	WindowCollection::get()->erase(this);
#endif
}

void Window::setTitle(const std::string & title)
{
#if NB_OS != NB_OS_ANDROID
	glfwSetWindowTitle(m_implWindow, title.data());
#endif
}

const std::string &Window::title() const
{
	return m_title;
}

void Window::setPosition(float x, float y)
{
#if NB_OS != NB_OS_ANDROID
	glfwSetWindowPos(m_implWindow, (int)x, (int)y);
#endif
}

void Window::active()
{
#if NB_OS != NB_OS_ANDROID
	if (m_implWindow)
	{
		glfwFocusWindow(m_implWindow);
	}
#endif
}

void Window::close()
{
	_close(true);
}

void Window::show(bool bShow)
{
#if NB_OS != NB_OS_ANDROID
	bShow ? glfwHideWindow(m_implWindow) : glfwShowWindow(m_implWindow);
#endif
}

bool Window::isShow() const
{
	return true;
}

void Window::setWindowState(WindowStateE state)
{
#if NB_OS != NB_OS_ANDROID
	m_lastWindowState = WindowStateE::Normal;
	if (!m_processingCallback)
	{
		m_processingWindowStateChanged = true;
		switch (state)
		{
			//处理WindowStateE::Normal，多加一个glfwMaximizeWindow的原因，是当出现连续设置glfwMaximizeWindow、glfwIconifyWindow、glfwRestoreWindow时，
			//glfw恢复到了max状态，这和预期是不符合的，这是glfw的固有表现；在glfwRestoreWindow前加一个glfwMaximizeWindow则可以保证恢复到normal状态
		case WindowStateE::Normal:		glfwMaximizeWindow(m_implWindow); glfwRestoreWindow(m_implWindow);	break;
		case WindowStateE::Maximized:	glfwMaximizeWindow(m_implWindow);									break;
		case WindowStateE::Minimized:	glfwIconifyWindow(m_implWindow);									break;
		default:																							break;
		}
	}
	StateChanged.invoke({});
#endif
}

WindowStateE Window::windowState() const
{
	return WindowStateE();
}

void Window::setWindowsStyle(WindowStyleE style)
{
#if NB_OS != NB_OS_ANDROID
	switch (style)
	{
	case WindowStyleE::None:	glfwSetWindowAttrib(m_implWindow, GLFW_DECORATED, false);	glfwSetWindowAttrib(m_implWindow, GLFW_RESIZABLE, true);	break;
	case WindowStyleE::Fixed:	glfwSetWindowAttrib(m_implWindow, GLFW_DECORATED, true);	glfwSetWindowAttrib(m_implWindow, GLFW_RESIZABLE, false);	break;
	case WindowStyleE::SizeBox:	glfwSetWindowAttrib(m_implWindow, GLFW_DECORATED, true);	glfwSetWindowAttrib(m_implWindow, GLFW_RESIZABLE, true);	break;
	default:																																			break;
	}
#endif
}

WindowStyleE Window::windowStyle() const
{
	return WindowStyleE();
}

void Window::setTopmost(bool topmost)
{
#if NB_OS != NB_OS_ANDROID
	glfwSetWindowAttrib(m_implWindow, GLFW_FLOATING, topmost);
#endif
}

bool Window::topmost() const
{
#if NB_OS != NB_OS_ANDROID
	return glfwGetWindowAttrib(m_implWindow, GLFW_FLOATING) != 0;
#else
	return false;
#endif
}

Point Window::getMousePosition() const
{
#if NB_OS != NB_OS_ANDROID
	double x = 0, y = 0;
	glfwGetCursorPos(m_implWindow, &x, &y);
	return Point((float)x, (float)y);
#else
	return Point();
#endif
}

GLFWwindow *Window::getGLFW() const
{
	return m_implWindow;
}

ref<Node2D> Window::getSelectItem() const
{
	return m_selectItem;
}

void Window::selectItem(float x, float y)
{
	auto nodes = TreeHelper::getAllChildren(root);
	for (int i = nodes.size() - 1; i >= 0; --i)
	{
		auto node = nodes[i];
		if (node->hitTest(Point(x, y)))
		{
			m_selectItem = node;
			return;
		}
	}
	m_selectItem = nullptr;
}

void Window::pollEvents()
{
#if NB_OS != NB_OS_ANDROID
	if (g_windowSystemInitialized)
	{
		glfwPollEvents();
	}
#endif
}

void Window::setWidth(float width)
{
#if NB_OS != NB_OS_ANDROID
	glfwSetWindowSize(m_implWindow, (int)width, (int)height());
#endif
}

void Window::setHeight(float height)
{
#if NB_OS != NB_OS_ANDROID
	glfwSetWindowSize(m_implWindow, (int)width(), (int)height);
#endif
}

float Window::width() const
{
#if NB_OS != NB_OS_ANDROID
	int w = 0, h = 0;
	glfwGetWindowSize(m_implWindow, &w, &h);
	return (float)w;
#else
	return 0.0f;
#endif
}

float Window::height() const
{
#if NB_OS != NB_OS_ANDROID
	int w = 0, h = 0;
	glfwGetWindowSize(m_implWindow, &w, &h);
	return (float)h;
#else
	return 0.0f;
#endif
}

void Window::_close(bool eraseFromCollection)
{
#if NB_OS != NB_OS_ANDROID
	if (m_dispatchingCloseEvent)	return;

	m_dispatchingCloseEvent = true;
	CancelEventArgs args;
	//onClosing(args);
	if (!args.cancel)
	{
		destroyWindow();
		//onClosed(args);
		if (eraseFromCollection)
		{
			WindowCollection::get()->erase(this);
		}
	}
	m_dispatchingCloseEvent = false;
#endif
}

void Window::posCallback(int x, int y)
{
	LocationChanged.invoke({});
}

void Window::sizeCallback(int width, int height)
{
}

void Window::frameBufferSizeCallback(int width, int height)
{
	GLUtils::viewport((float)0, (float)0, (float)width, (float)height);
	sharedCamera2D()->resize((float)width, (float)height);
}

void Window::mouseButtonCallback(int button, int action, int mods)
{
#if NB_OS != NB_OS_ANDROID
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		double x = 0, y = 0;
		glfwGetCursorPos(m_implWindow, &x, &y);

		TouchEventArgs e;
		e.action = action == GLFW_PRESS ? TouchActionE::down : TouchActionE::up;
		e.x = (float)x;
		e.y = (float)y;

		Touch.invoke(e);
		TreeHelper::touchThunk(root, e);
	}
#endif
}

void Window::cusorPosCallback(double x, double y)
{
#if NB_OS != NB_OS_ANDROID
	TouchEventArgs e;
	e.action = TouchActionE::move;
	e.x = (float)x;
	e.y = (float)y;

	Touch.invoke(e);
	TreeHelper::touchThunk(root, e);
#endif
}

void Window::cusorPosEnterCallback(int entered)
{
/*	MouseEventArgs args(0);
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
	*/
}

void Window::scrollCallback(double x, double y)
{
	ScrollEventArgs e;
	e.delta = (int)y;
	Scroll.invoke(e);
	TreeHelper::scrollThunk(root, e);
}

void Window::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		quick_exit(0);

	KeyEventArgs e;
	e.sender = this;
	e.key = KeyCode(key);
	e.scancode = scancode;
	e.action = action == GLFW_PRESS ? KeyAction::down : action == GLFW_RELEASE ? KeyAction::up : KeyAction::repeat;
	e.mods = mods;
	Key.invoke(e);
	TreeHelper::keyThunk(root, e);
}

void Window::focusCallback(int focused)
{
	//	Focusable = focused;
}

void Window::refreshCallback()
{
//	render();
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
		setWindowState(iconified ? WindowStateE::Minimized : m_lastWindowState);
	}
	m_processingCallback = false;
}

void Window::maximizeCallback(int maximized)
{
	m_processingCallback = true;
	if (!m_processingWindowStateChanged)
	{
		setWindowState(maximized ? WindowStateE::Maximized : WindowStateE::Normal);
	}
	m_processingCallback = false;
}

void Window::dropCallback(int count, const char * paths[])
{
	DropEventArgs e;
	e.sender = this;
	e.paths.reserve(count);
	for (auto i = 0; i < count; ++i)
		e.paths.emplace_back(paths[i]);
	Drop.invoke(e);
}

void Window::destroyWindow()
{
#if NB_OS != NB_OS_ANDROID
	if (m_implWindow)
	{
		glfwDestroyWindow(m_implWindow);
		m_implWindow = nullptr;
		if (WindowCollection::get()->windows().empty())
		{
			deinit();
		}
	}
#endif
}

void Window::render()
{
#if NB_OS != NB_OS_ANDROID
	glfwMakeContextCurrent(m_implWindow);

	if (root)
		root->updateLayout(Size(width(), height()));

	PreRender.invoke({});

	if (m_selectItem)
	{
		auto rc = m_selectItem->getRenderRect();
		Renderer2D::drawBorder(rc, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	}

	PostRender.invoke({});

	glfwSwapBuffers(m_implWindow);
#endif
}

void Window::init()
{
#if NB_OS != NB_OS_ANDROID
	if (g_windowSystemInitialized)	return;

	glfwSetErrorCallback([](int error, const char*str) { printf("error:%s\n", str); });
	glfwInit();
	//以下两句在有些电脑上导致glfwDestroyWindow挂死，放在库外不会挂死，目前暂未找到原因
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	//glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 32);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	g_windowSystemInitialized = true;
#endif
}

void Window::deinit()
{
#if NB_OS != NB_OS_ANDROID
	glfwTerminate();
	g_windowSystemInitialized = false;
#endif
}

/////////////////////
WindowCollection *WindowCollection::get()
{
	static WindowCollection *p = new WindowCollection();
	return p;
}

size_t WindowCollection::count() const
{
	return m_windows.size();
}

Window * WindowCollection::operator[](size_t index)
{
	nbThrowExceptionIf(index >= m_windows.size(), std::out_of_range, "index[%d] is out of range[0, %d)", (int)index, (int)m_windows.size());
	return m_windows[index];
}

void WindowCollection::push(Window * w)
{
	if (m_windows.empty())
		m_mainWindow = w;
	m_windows.push_back(w);
}

void WindowCollection::erase(Window * w)
{
	auto iter = std::find(m_windows.begin(), m_windows.end(), w);
	if (iter != m_windows.end())
	{
		auto isMainWindow = *iter == m_mainWindow;
		m_windows.erase(iter);
		WindowClosed.invoke({ isMainWindow });
	}
}

std::vector<Window*>& WindowCollection::windows()
{
	return m_windows;
}

void WindowCollection::setMainWindow(Window * w)
{
	m_mainWindow = w;
}

Window * WindowCollection::mainWindow()
{
	return m_mainWindow;
}
