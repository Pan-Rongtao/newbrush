#include "newbrush/Window.h"
#if NB_OS == NB_OS_WINDOWS_NT
	#define GLFW_INCLUDE_NONE
	#include "GLFW/glfw3.h"
#endif
#include "newbrush/Log.h"
#include "newbrush/Node2D.h"
#include "newbrush/Helper.h"
#include "newbrush/Renderer2D.h"

using namespace nb;

static bool		g_windowSystemInitialized = false;
static Window *g_window = nullptr;

#if NB_OS == NB_OS_QNX

screen_context_t	m_qnxScreenContext;
screen_event_t		m_qnxScreenEvent;

const EGLint attribs[] = 
{
	EGL_BLUE_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_RED_SIZE, 8,
	EGL_DEPTH_SIZE,24,
	EGL_SAMPLE_BUFFERS, 1,
	EGL_SAMPLES, 4,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_NONE
};

int choose_format(EGLDisplay egl_disp, EGLConfig egl_conf)
{
	EGLint bufferBit, alphaBit;
	eglGetConfigAttrib(egl_disp, egl_conf, EGL_BUFFER_SIZE, &bufferBit);
	eglGetConfigAttrib(egl_disp, egl_conf, EGL_ALPHA_SIZE, &alphaBit);
	switch (bufferBit) 
	{ 
		case 32: return SCREEN_FORMAT_RGBA8888;
		case 24: return SCREEN_FORMAT_RGB888;
		case 16: return alphaBit == 4 ? SCREEN_FORMAT_RGBA4444 : alphaBit == 1 ? SCREEN_FORMAT_RGBA5551 : SCREEN_FORMAT_RGB565;
		default: return SCREEN_FORMAT_BYTE;
	}
}
#endif

Window::Window()
	: Window(1920.0f, 720.0f, "newbrush")
{}

Window::Window(float width, float heith)
	: Window(width, heith, "newbrush")
{}

Window::Window(const std::string & title)
	: Window(1920.0f, 720.0f, title)
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
#endif

	init();

#if NB_OS == NB_OS_WINDOWS_NT
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
	

#elif NB_OS == NB_OS_QNX
	/*egl init begin*/
	m_eglDisplay = eglGetDisplay(EGL_CAST(EGLNativeDisplayType,0)/*EGL_DEFAULT_DISPLAY*/);
	nbThrowExceptionIf(!m_eglDisplay, std::runtime_error, "eglGetDisplay fail.");
	nbThrowExceptionIf(!eglInitialize(m_eglDisplay, NULL, NULL), std::runtime_error, "eglInitialize fail.");

	EGLConfig egl_conf;
	EGLint numConfigs = 0;
	eglChooseConfig(m_eglDisplay, attribs, &m_eglConfig, 1, &numConfigs);
	nbThrowExceptionIf(!m_eglConfig, std::runtime_error, "eglChooseConfig fail.");

	EGLint contextAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
	m_eglContext = eglCreateContext(m_eglDisplay, m_eglConfig, 0, contextAttr/*NULL*/);
	nbThrowExceptionIf(!m_eglContext, std::runtime_error, "eglCreateContext fail");

	/*egl init end*/
	
	/*qnx screen & window*/
	screen_create_context(&m_qnxScreenContext, SCREEN_INPUT_PROVIDER_CONTEXT);
	screen_create_event(&m_qnxScreenEvent);
	screen_create_window(&m_qnxWindow, m_qnxScreenContext);
	screen_create_window_buffers(m_qnxWindow, 2);
	int format = choose_format(m_eglDisplay, m_eglConfig);
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_FORMAT, &format);

	m_eglSurface = eglCreateWindowSurface(m_eglDisplay, m_eglConfig, m_qnxWindow, 0);
	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);

	/*qnx screen & window*/
#endif
	setZOrder(3000);
	setSwapInterval(1);
	frameBufferSizeCallback((int)width, (int)height);
	WindowCollection::get()->push(this);
	Log::info("{}", SystemHelper::getSystemInfos());
	g_window = this;
}

Window::~Window()
{
	destroyWindow();
	WindowCollection::get()->erase(this);
}

void Window::setTitle(const std::string & title)
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetWindowTitle(m_implWindow, title.data());
	m_title = title;
#elif NB_OS == NB_OS_QNX
	
#endif
}

const std::string &Window::title() const
{
	return m_title;
}

void Window::setPosition(float x, float y)
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetWindowPos(m_implWindow, (int)x, (int)y);
#elif NB_OS == NB_OS_QNX
	int pos[2] = {(int)x, (int)y};
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SOURCE_POSITION, pos);
#endif
}

void Window::active()
{
#if NB_OS == NB_OS_WINDOWS_NT
	if (m_implWindow)
	{
		glfwFocusWindow(m_implWindow);
	}
#elif NB_OS == NB_OS_QNX

#endif
}

void Window::close()
{
	_close(true);
}

void Window::show(bool bShow)
{
#if NB_OS == NB_OS_WINDOWS_NT
	bShow ? glfwHideWindow(m_implWindow) : glfwShowWindow(m_implWindow);
#elif NB_OS == NB_OS_QNX
	int visible = (int)bShow;
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_VISIBLE, &visible);
#endif
}

bool Window::isShow() const
{
	return true;
}

void Window::setWindowState(WindowStateE state)
{
#if NB_OS == NB_OS_WINDOWS_NT
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
#if NB_OS == NB_OS_WINDOWS_NT
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
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetWindowAttrib(m_implWindow, GLFW_FLOATING, topmost);
#endif
}

bool Window::topmost() const
{
#if NB_OS == NB_OS_WINDOWS_NT
	return glfwGetWindowAttrib(m_implWindow, GLFW_FLOATING) != 0;
#else
	return false;
#endif
}

Point Window::getMousePosition() const
{
#if NB_OS == NB_OS_WINDOWS_NT
	double x = 0, y = 0;
	glfwGetCursorPos(m_implWindow, &x, &y);
	return Point((float)x, (float)y);
#else
	return Point();
#endif
}

void Window::setZOrder(int order)
{
#if NB_OS == NB_OS_QNX
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_ZORDER, &order);
#endif
}

void Window::setSwapInterval(int interval)
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSwapInterval(interval);
#elif NB_OS == NB_OS_QNX
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SWAP_INTERVAL, &interval);
#endif
}

#if NB_OS == NB_OS_WINDOWS_NT
GLFWwindow *Window::getGLFW() const
{
	return m_implWindow;
}
#endif

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
#if NB_OS == NB_OS_WINDOWS_NT
	if (g_windowSystemInitialized)
	{
		glfwPollEvents();
	}
#elif NB_OS == NB_OS_QNX
	while (!screen_get_event(m_qnxScreenContext, m_qnxScreenEvent, 0)) 
	{
		int eventType;
		screen_get_event_property_iv(m_qnxScreenEvent, SCREEN_PROPERTY_TYPE, &eventType);
		if (eventType == SCREEN_EVENT_NONE) 
		{
			break;
		}
		switch (eventType) 
		{
			case SCREEN_EVENT_PROPERTY:
			{
				int val;
				screen_get_event_property_iv(m_qnxScreenEvent, SCREEN_PROPERTY_NAME, &val);
				switch (val) 
				{
					case SCREEN_PROPERTY_SIZE:
					{
						int size[2] = {0, 0};
						//screen_get_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
						printf("window size changed\n");	
					}
					break;
					default: break;
				}
			}
			break;
			case SCREEN_EVENT_MTOUCH_TOUCH:
			{
				int pos[2] = { 0, 0 };
				screen_get_event_property_iv(m_qnxScreenEvent, SCREEN_PROPERTY_POSITION, pos);
				//printf("touch down: x=%d, y=%d\n", pos[0], pos[1]);
				
				TouchEventArgs e;
				e.action = TouchActionE::down;
				e.x = (float)pos[0];
				e.y = (float)pos[1];

				g_window->Touch.invoke(e);
				TreeHelper::touchThunk(g_window->root, e);
			}
			break;
			case SCREEN_EVENT_MTOUCH_MOVE:
			{
				int pos[2] = { 0, 0 };
				screen_get_event_property_iv(m_qnxScreenEvent, SCREEN_PROPERTY_POSITION, pos);
				//printf("touch move: x=%d, y=%d\n", pos[0], pos[1]);
				g_window->cusorPosCallback(pos[0], pos[1]);
			}
			break;
			case SCREEN_EVENT_MTOUCH_RELEASE:
			{
				int pos[2] = { 0, 0 };
				screen_get_event_property_iv(m_qnxScreenEvent, SCREEN_PROPERTY_POSITION, pos);
				//printf("touch release: x=%d, y=%d\n", pos[0], pos[1]);

				TouchEventArgs e;
				e.action = TouchActionE::up;
				e.x = (float)pos[0];
				e.y = (float)pos[1];

				g_window->Touch.invoke(e);
				TreeHelper::touchThunk(g_window->root, e);
			}
			break;
		}
	}
#endif
}

void Window::setWidth(float width)
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetWindowSize(m_implWindow, (int)width, (int)height());
#elif NB_OS == NB_OS_QNX
	int size[2] = {0, 0};
	screen_get_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	size[0] = width;
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	frameBufferSizeCallback(size[0], size[1]);
#endif
}

void Window::setHeight(float height)
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetWindowSize(m_implWindow, (int)width(), (int)height);
#elif NB_OS == NB_OS_QNX
	int size[2] = {0, 0};
	screen_get_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	size[1] = height;
	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	frameBufferSizeCallback(size[0], size[1]);

//	int wh[2] = {1920, 1080};
//	screen_set_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SOURCE_SIZE, wh);
#endif
}

float Window::width() const
{
#if NB_OS == NB_OS_WINDOWS_NT
	int w = 0, h = 0;
	glfwGetWindowSize(m_implWindow, &w, &h);
	return (float)w;
#elif NB_OS == NB_OS_QNX
	int size[2] = {0, 0};
	screen_get_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	return (float)size[0];
#else
	return 0.0f;
#endif
}

float Window::height() const
{
#if NB_OS == NB_OS_WINDOWS_NT
	int w = 0, h = 0;
	glfwGetWindowSize(m_implWindow, &w, &h);
	return (float)h;
#elif NB_OS == NB_OS_QNX
	int size[2] = {0, 0};
	screen_get_window_property_iv(m_qnxWindow, SCREEN_PROPERTY_SIZE, size);
	return (float)size[1];
#else
	return 0.0f;
#endif
}

void Window::_close(bool eraseFromCollection)
{
#if NB_OS == NB_OS_WINDOWS_NT
	if (m_dispatchingCloseEvent)	return;

	m_dispatchingCloseEvent = true;
	CancelEventArgs e;
	Closing.invoke(e);
	if (!e.cancel)
	{
		destroyWindow();
		Closed.invoke(e);
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
#if NB_OS == NB_OS_WINDOWS_NT
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
	TouchEventArgs e;
	e.action = TouchActionE::move;
	e.x = (float)x;
	e.y = (float)y;

	Touch.invoke(e);
	TreeHelper::touchThunk(root, e);
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
#if NB_OS == NB_OS_WINDOWS_NT
	KeyEventArgs e;
	e.sender = this;
	e.key = KeyCode(key);
	e.scancode = scancode;
	e.action = action == GLFW_PRESS ? KeyAction::down : action == GLFW_RELEASE ? KeyAction::up : KeyAction::repeat;
	e.mods = mods;
	Key.invoke(e);
	TreeHelper::keyThunk(root, e);
#endif
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
#if NB_OS == NB_OS_WINDOWS_NT
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
#if NB_OS == NB_OS_WINDOWS_NT
	glfwMakeContextCurrent(m_implWindow);
#elif NB_OS == NB_OS_QNX
	eglMakeCurrent(m_eglDisplay, m_eglSurface, m_eglSurface, m_eglContext);
#endif

	PreRender.invoke({});

	if (root)
		root->updateLayout(Size(width(), height()));

	if (m_selectItem)
	{
		auto rc = m_selectItem->getRenderRect();
		Renderer2D::drawBorder(rc, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	}

	PostRender.invoke({});

#if NB_OS == NB_OS_WINDOWS_NT
	glfwSwapBuffers(m_implWindow);
#elif NB_OS == NB_OS_QNX
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
#endif

	static bool once = false;
	if (!once)
	{
		ContentRendered.invoke({});
		once = true;
	}
}

void Window::init()
{
	if (g_windowSystemInitialized)	return;
#if NB_OS == NB_OS_WINDOWS_NT
	glfwSetErrorCallback([](int error, const char*str) { printf("error:%s\n", str); });
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 32);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
#elif NB_OS == NB_OS_QNX

#endif
	g_windowSystemInitialized = true;
}

void Window::deinit()
{
#if NB_OS == NB_OS_WINDOWS_NT
	glfwTerminate();
#endif
	g_windowSystemInitialized = false;
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
