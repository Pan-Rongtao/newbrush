#include "Window_Internal.h"
#include "core/Exception.h"
#include "core/Window.h"
#include <cstring>

using namespace nb::core;

#ifdef NB_OS_FAMILY_WINDOWS
	bool Window_Internal::m_pressed = false;
	std::map<long, Window *> Window_Internal::m_windows;
	#define WINDOW_CLASS_NAME	"Newbrush Class"
#elif defined NB_OS_FAMILY_UNIX
	static wl_fixed_t x_pointer_move = 0;
	static wl_fixed_t y_pointer_move = 0;
#endif

Window_Internal::Window_Internal(Window *p)
	: m_pW(p)
{
#ifdef NB_OS_FAMILY_WINDOWS
	m_instance = ::GetModuleHandle(NULL);

	WNDCLASSA windowClass = { 0 };
	windowClass.style = 0;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.lpszMenuName = 0;
	windowClass.hInstance = m_instance;
	windowClass.lpszClassName = WINDOW_CLASS_NAME;
	windowClass.lpfnWndProc = Window_Internal::wndProc;
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//	windowClass.hIconSm			= 0;
	if (::RegisterClassA(&windowClass) == 0)
	{
		//already exist class name, not a error
	}
	RECT rcClient = { 0, 0, 800, 480 };
	::AdjustWindowRect(&rcClient, WS_TILEDWINDOW, false);
	int width = rcClient.right - rcClient.left;
	int height = rcClient.bottom - rcClient.top;
	int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	m_hwnd = ::CreateWindowA(windowClass.lpszClassName, "", WS_TILEDWINDOW, x, y, width, height, NULL, NULL, m_instance, NULL);
	::ShowWindow(m_hwnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hwnd);
	m_windows[(long)m_hwnd] = m_pW;
#elif defined NB_OS_FAMILY_UNIX
	m_X11Display = XOpenDisplay(nullptr);
	if (m_X11Display == nullptr)
		throw SystemException("XOpenDiplay return nullptr");
	int screen = DefaultScreen(m_X11Display);	//这是个宏
	//m_X11WindowID从服务端获取，不用释放
	m_X11WindowID = XCreateSimpleWindow(m_X11Display, RootWindow(m_X11Display, screen), 0, 0, 800, 480, 1, BlackPixel(m_X11Display, screen), WhitePixel(m_X11Display, screen));
	XSelectInput(m_X11Display, m_X11WindowID, StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask);
	XMapWindow(m_X11Display, m_X11WindowID);
#elif NB_OS == NB_OS_LINUX_ARM
	m_wlDisplay = wl_display_connect(NULL);
	if (m_wlDisplay == NULL)
		throw SystemException("create window fail.");

	m_wlRegistry = wl_display_get_registry(m_wlDisplay);
	m_UserData.wlListeners.wlRegistryListener.global = Window_Internal::onWaylandRegistryGlobal;
	wl_registry_add_listener(m_wlRegistry, &m_UserData.wlListeners.wlRegistryListener, &m_UserData);
	//一定要同步server端的处理，在回调中拿到各global对象，包括compositor、shell、seat等，并按需注册相应global对象的消息
	wl_display_dispatch(m_wlDisplay);
	wl_display_roundtrip(m_wlDisplay);

	m_wlSurface = wl_compositor_create_surface(m_UserData.wlGlobals.wlCompositor);
	if (m_wlSurface == NULL)
		throw SystemException("create surface fail.");

	m_wlShellSurface = wl_shell_get_shell_surface(m_UserData.wlGlobals.wlShell, m_wlSurface);
	if (m_wlShellSurface == NULL)
		throw SystemException("get shell surface fail.");

	m_wlWindow = wl_egl_window_create(m_wlSurface, 1920, 1080);
	if (m_wlWindow == NULL)
		throw SystemException("create window fail.");
#endif
}

Window_Internal::~Window_Internal()
{
#ifdef NB_OS_FAMILY_WINDOWS
	if (::DestroyWindow(m_hwnd) || ::UnregisterClassA(WINDOW_CLASS_NAME, m_instance) == 0)
	{
		printf("DestroyWindow or UnregisterClass window class fail. error code[%d]", GetLastError());
	}
#elif defined NB_OS_FAMILY_UNIX
	XCloseDisplay(m_X11Display);
#elif NB_OS == NB_OS_LINUX_ARM
	wl_shell_surface_destroy(m_wlShellSurface);
	wl_surface_destroy(m_wlSurface);
	//是否要删除shell和compositor？
#endif
}

void Window_Internal::setTitle(const std::string & title)
{
#ifdef NB_OS_FAMILY_WINDOWS
	::SetWindowTextA(m_hwnd, title.data());
#elif defined NB_OS_FAMILY_UNIX
	int x = XStoreName(m_X11Display, m_X11WindowID, title.data());
#elif NB_OS == NB_OS_LINUX_ARM
	wl_shell_surface_set_title(m_wlShellSurface, title.data());
#endif
}

std::string Window_Internal::title() const
{
	char arr[256] = { 0 };
#ifdef NB_OS_FAMILY_WINDOWS
	GetWindowTextA(m_hwnd, arr, sizeof(arr));
	return arr;
#elif defined NB_OS_FAMILY_UNIX
	Status x = XFetchName(m_X11Display, m_X11WindowID, &arr);
	return (x == 0 || arr == NULL) ? "" : arr;
#elif NB_OS == NB_OS_LINUX_ARM
	return "";
#endif
}

void Window_Internal::setX(int x)
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rc = { x, y(), x + width(), y() + height()};
	::AdjustWindowRect(&rc, WS_TILEDWINDOW, false);
	::MoveWindow(m_hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);
#elif defined NB_OS_FAMILY_UNIX
	XMoveResizeWindow(m_X11Display, m_X11WindowID, x, y(), width(), height());
#elif NB_OS == NB_OS_LINUX_ARM
	//	wl_shell_surface_resize(m_wlShellSurface, m_wlGlobals.wlSeat, );
#endif
}

int Window_Internal::x() const
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rcWindow;
	::GetWindowRect(m_hwnd, &rcWindow);
	return rcWindow.left;
#elif defined NB_OS_FAMILY_WINDOWS
	//	XWindowAttributes attrs;
	//	XGetWindowAttributes(m_X11Display, m_X11WindowID, &attrs);
	return 0;
#elif NB_OS == NB_OS_LINUX_ARM
	return 0;
#endif
}

void Window_Internal::setY(int y)
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rc = { x(), y, x() + width(), y + height() };
	::AdjustWindowRect(&rc, WS_TILEDWINDOW, false);
	::MoveWindow(m_hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);
#elif defined NB_OS_FAMILY_UNIX
	XMoveResizeWindow(m_X11Display, m_X11WindowID, x(), y, width(), height());
#elif NB_OS == NB_OS_LINUX_ARM
	//	wl_shell_surface_resize(m_wlShellSurface, m_wlGlobals.wlSeat, );
#endif
}

int Window_Internal::y() const
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rcWindow;
	::GetWindowRect(m_hwnd, &rcWindow);
	return rcWindow.top;
#elif defined NB_OS_FAMILY_UNIX
	//	XWindowAttributes attrs;
	//	XGetWindowAttributes(m_X11Display, m_X11WindowID, &attrs);
	return 0;
#elif NB_OS == NB_OS_LINUX_ARM
	return 0;
#endif
}

void Window_Internal::setWidth(int width)
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rc = { x(), y(), x() + width, y() + height() };
	::AdjustWindowRect(&rc, WS_TILEDWINDOW, false);
	::MoveWindow(m_hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);
#elif defined NB_OS_FAMILY_UNIX
	XMoveResizeWindow(m_X11Display, m_X11WindowID, x(), y(), width, height());
#elif NB_OS == NB_OS_LINUX_ARM
	//	wl_shell_surface_resize(m_wlShellSurface, m_wlGlobals.wlSeat, );
#endif
}

int Window_Internal::width() const
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rcClient;
	::GetClientRect(m_hwnd, &rcClient);
	return rcClient.right - rcClient.left;
#elif defined NB_OS_FAMILY_UNIX
	//	XWindowAttributes attrs;
	//	XGetWindowAttributes(m_X11Display, m_X11WindowID, &attrs);
	return 0;
#elif NB_OS == NB_OS_LINUX_ARM
	return 0;
#endif
}

void Window_Internal::setHeight(int height)
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rc = { x(), y(), x() + width(), y() + height };
	::AdjustWindowRect(&rc, WS_TILEDWINDOW, false);
	::MoveWindow(m_hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);
#elif defined NB_OS_FAMILY_UNIX
	XMoveResizeWindow(m_X11Display, m_X11WindowID, x(), y(), width(), height);
#elif NB_OS == NB_OS_LINUX_ARM
	//	wl_shell_surface_resize(m_wlShellSurface, m_wlGlobals.wlSeat, );
#endif
}

int Window_Internal::height() const
{
#ifdef NB_OS_FAMILY_WINDOWS
	RECT rcClient;
	::GetClientRect(m_hwnd, &rcClient);
	return rcClient.bottom - rcClient.top;
#elif defined NB_OS_FAMILY_UNIX
	//	XWindowAttributes attrs;
	//	XGetWindowAttributes(m_X11Display, m_X11WindowID, &attrs);
	return 0;
#elif NB_OS == NB_OS_LINUX_ARM
	return 0;
#endif
}

long Window_Internal::handle() const
{
#ifdef NB_OS_FAMILY_WINDOWS
	return (long)m_hwnd;
#elif defined NB_OS_FAMILY_UNIX
	return m_X11WindowID;
#elif NB_OS == NB_OS_LINUX_ARM
	return (long)m_wlWindow;
#endif
}

void Window_Internal::pending()
{
#ifdef NB_OS_FAMILY_WINDOWS
	MSG msg = { 0 };
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
#elif defined NB_OS_FAMILY_UNIX
	x11WindowPending();
#elif NB_OS == NB_OS_LINUX_ARM
	wl_display_dispatch_pending(m_wlDisplay);
#endif
}

//////////////////////////
//以下为其他私有函数，callback等

#ifdef NB_OS_FAMILY_WINDOWS

LRESULT CALLBACK Window_Internal::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_DESTROY || msg == WM_CLOSE || msg == WM_QUIT || msg == WM_SIZE ||
		msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_LBUTTONDBLCLK || msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP || msg == WM_MOUSEMOVE ||
		msg == WM_KEYDOWN || msg == WM_KEYUP || msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP)
	{
		auto iter = m_windows.find((long)hwnd);
		Window *pWindow = iter == m_windows.end() ? nullptr : iter->second;

		//只有pWindow->listener()方式才能访问非static成员，因为m_listener不是Window_Internal的成员。
		switch (msg)
		{
		case WM_DESTROY:
			break;
		case WM_CLOSE:
		case WM_QUIT:
		{
			::PostQuitMessage(0);
		}
		break;
		case WM_SIZE:
		{
			if (pWindow)
			{
				Window::ResizeArgs args;
				args.width = LOWORD(lParam);
				args.height = HIWORD(lParam);
				pWindow->ResizeEvent.dispatch(args);
			}
		}
		break;
		case WM_LBUTTONDOWN:
		{
			m_pressed = true;
			::SetCapture(hwnd);
			if (pWindow)
			{
				Window::PointerEventArgs args;
				args.action = Window::PointerAction_Down;
				args.x = GET_X_LPARAM(lParam);
				args.y = GET_Y_LPARAM(lParam);
				pWindow->PointerEvent.dispatch(args);
			}
		}
		break;
		case WM_MOUSEMOVE:
		{
			if (pWindow && m_pressed)
			{
				Window::PointerEventArgs args;
				args.action = Window::PointerAction_Move;
				args.x = GET_X_LPARAM(lParam);
				args.y = GET_Y_LPARAM(lParam);
				pWindow->PointerEvent.dispatch(args);
			}
		}
		break;
		case WM_LBUTTONUP:
		{
			m_pressed = false;
			::ReleaseCapture();
			if (pWindow)
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);

				Window::PointerEventArgs args;
				args.action = Window::PointerAction_Up;
				args.x = x;
				args.y = y;
				pWindow->PointerEvent.dispatch(args);

				RECT rcClient;
				::GetClientRect(hwnd, &rcClient);
				if (x >= 0 && x <= (rcClient.right - rcClient.left) && y >= 0 && y <= (rcClient.bottom - rcClient.top))
				{
					args.action = Window::PointerAction_Click;
					pWindow->PointerEvent.dispatch(args);
				}
			}
		}
		break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			if (pWindow)
			{
				Window::KeyEventArgs args;
				args.action = msg == WM_KEYDOWN ? Window::KeyAction_Down : Window::KeyAction_Up;
				args.mask = 0;
				if (wParam == VK_ESCAPE)														args.key = Window::VKey_Esc;
				else if (wParam >= VK_F1 && wParam <= VK_F12)									args.key = (Window::KeyCode)(wParam - VK_F1 + Window::VKey_F1);
				else if (wParam == VK_SPACE)													args.key = Window::VKey_Space;
				else if ((wParam >= '0' && wParam <= '9') || (wParam >= 'A' && wParam <= 'Z'))	args.key = (Window::KeyCode)wParam;
				else if (wParam >= VK_LEFT && wParam <= VK_DOWN)								args.key = (Window::KeyCode)(wParam - VK_LEFT + Window::VKey_Left);
				else if (wParam == VK_ADD)														args.key = Window::VKey_Add;
				else if (wParam == VK_SUBTRACT)													args.key = Window::VKey_Sub;
				else																			args.key = Window::VKey_Unknown;
				pWindow->KeyEvent.dispatch(args);
			}
		}
		break;
		case WM_SYSKEYDOWN:		
		case WM_SYSKEYUP:
		{
			if (pWindow)
			{
				if (wParam == VK_F10)//F10只有systemkey，且F10会影响其他key建
				{
					Window::KeyEventArgs args;
					args.action = msg == WM_KEYDOWN ? Window::KeyAction_Down : Window::KeyAction_Up;
					args.key = Window::VKey_F10;
					args.mask = 0;
					pWindow->KeyEvent.dispatch(args);

					//F10在win32中会让窗口消息进入空闲状态，此时不会再接收到F1-F12按键，除非再按一次F10来取消这种状态
					//而直接return 0不return ::DefWindowProc(hwnd, msg, wParam, lParam);可防止这种事情发生。
					return 0;
				}
			}
		}
		break;
		default:	break;
		}
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}
#elif defined NB_OS_FAMILY_UNIX
void Window_Internal::x11WindowPending()
{
	if (!XPending(m_X11Display))
		return;

	XEvent event;
	XNextEvent(m_X11Display, &event);
	switch (event.type)
	{
	case CreateNotify:
		if (m_pW->listener())
			m_pW->listener()->OnPrimaryAction(PrimaryAction_Create);
		break;
	case DestroyNotify:
		if (m_pW->listener())
			m_pW->listener()->OnPrimaryAction(PrimaryAction_Destroy);
		break;
	case ConfigureNotify:
		if (m_pW->listener())
		{
			if (width() != event.xconfigure.width || height() != event.xconfigure.height)
			{
			//	m_rect.Reset(event.xconfigure.x, event.xconfigure.y, event.xconfigure.width, event.xconfigure.height);
				m_pW->listener()->OnResize(event.xconfigure.width, event.xconfigure.height);
			}
		}
		break;
	case ButtonPress:
		if (m_pW->listener())
			m_pW->listener()->OnPointerAction(PointerAction_Down, event.xbutton.x, event.xbutton.y);
		break;
	case MotionNotify:
		if (m_pW->listener())
			m_pW->listener()->OnPointerAction(PointerAction_Move, event.xmotion.x, event.xmotion.y);
		break;
	case ButtonRelease:
		if (m_pW->listener())
		{
			m_pW->listener()->OnPointerAction(PointerAction_Up, event.xbutton.x, event.xbutton.y);
			if (event.xbutton.x >= 0 && event.xbutton.x <= width() && event.xbutton.y >= 0 && event.xbutton.y <= height())
				m_pW->listener()->OnPointerAction(PointerAction_Click, event.xbutton.x, event.xbutton.y);
		}
		break;
	case KeyPress:
		if (m_pW->listener())
			m_pW->listener()->OnKeyAction(Window::KeyAction_Down, nativeKeyToKeycode(event.xkey.keycode), 0);
		break;
	case KeyRelease:
		if (m_pW->listener())
			m_pW->listener()->OnKeyAction(Window::KeyAction_Up, nativeKeyToKeycode(event.xkey.keycode), 0);
		break;
	default:
		break;
	}
}

KeyCode Window_Internal::nativeKeyToKeycode(int key)
{
	KeyCode ret = Window::VKey_Unknown;
	switch (key)
	{
	case 9:
		ret = Window::VKey_Esc;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		//	ret = KeyCode(key - (10 - Window::VKey_1));	//1-0
		break;
	case 67:
	case 68:
	case 69:
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
		ret = KeyCode(key - 67 + Window::VKey_F1);
		break;
	case 95:
	case 96:
		ret = KeyCode(key - 95 + Window::VKey_F11);
		break;
	default:
		break;
	}
	return ret;
}

#elif NB_OS == NB_OS_LINUX_ARM

void Window_Internal::onWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version)
{
	UserData *userData = (UserData *)data;
	if (strcmp(interface, "wl_compositor") == 0)
	{
		userData->wlGlobals.wlCompositor = (wl_compositor *)wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1);
	}
	else if (strcmp(interface, "wl_shell") == 0)
	{
		userData->wlGlobals.wlShell = (wl_shell *)wl_registry_bind(wl_registry, name, &wl_shell_interface, 1);
	}
	else if (strcmp(interface, "wl_seat") == 0)
	{
		userData->wlGlobals.wlSeat = (wl_seat *)wl_registry_bind(wl_registry, name, &wl_seat_interface, 1);
		userData->wlListeners.wlSeatListener.capabilities = Window_Internal::onWaylandSeatCapabilitties;
		wl_seat_add_listener(userData->wlGlobals.wlSeat, &userData->wlListeners.wlSeatListener, userData);
	}
}

void Window_Internal::onWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
	UserData *userData = (UserData *)data;
	if ((capabilities & WL_SEAT_CAPABILITY_POINTER) && userData->wlSeatGroup.wlPointer == NULL)
	{
		userData->wlSeatGroup.wlPointer = wl_seat_get_pointer(wl_seat);
		userData->wlListeners.wlPointerListener.enter = Window_Internal::onWaylandPointerEnter;
		userData->wlListeners.wlPointerListener.leave = Window_Internal::onWaylandPointerLeave;
		userData->wlListeners.wlPointerListener.motion = Window_Internal::onWaylandPointerMotion;
		userData->wlListeners.wlPointerListener.button = Window_Internal::onWaylandPointerButton;
		userData->wlListeners.wlPointerListener.axis = Window_Internal::onWaylandPointerAxis;
		wl_pointer_add_listener(userData->wlSeatGroup.wlPointer, &userData->wlListeners.wlPointerListener, userData);
	}
	else if (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && userData->wlSeatGroup.wlPointer)
	{
		wl_pointer_destroy(userData->wlSeatGroup.wlPointer);
		userData->wlSeatGroup.wlPointer = NULL;
	}
	if ((capabilities & WL_SEAT_CAPABILITY_TOUCH) && userData->wlSeatGroup.wlTouch == NULL)
	{
		userData->wlSeatGroup.wlTouch = wl_seat_get_touch(wl_seat);
		userData->wlListeners.wlTouchListener.down = Window_Internal::onWaylandTouchDown;
		userData->wlListeners.wlTouchListener.up = Window_Internal::onWaylandTouchUp;
		userData->wlListeners.wlTouchListener.motion = Window_Internal::onWaylandTouchMotion;
		userData->wlListeners.wlTouchListener.frame = Window_Internal::onWaylandTouchFrame;
		userData->wlListeners.wlTouchListener.cancel = Window_Internal::onWaylandTouchCancel;
		wl_touch_add_listener(userData->wlSeatGroup.wlTouch, &userData->wlListeners.wlTouchListener, userData);
	}
	else if (!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && userData->wlSeatGroup.wlTouch)
	{
		wl_touch_destroy(userData->wlSeatGroup.wlTouch);
		userData->wlSeatGroup.wlTouch = NULL;
	}
	if ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && userData->wlSeatGroup.wlKeyboard == NULL)
	{
		userData->wlSeatGroup.wlKeyboard = wl_seat_get_keyboard(wl_seat);
		userData->wlListeners.wlKeyboardListener.enter = Window_Internal::onWaylandKeyEnter;
		userData->wlListeners.wlKeyboardListener.leave = Window_Internal::onWaylandKeyLeave;
		userData->wlListeners.wlKeyboardListener.key = Window_Internal::onWaylandKey;
		wl_keyboard_add_listener(userData->wlSeatGroup.wlKeyboard, &userData->wlListeners.wlKeyboardListener, userData);
	}
	else if (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && userData->wlSeatGroup.wlKeyboard)
	{
		wl_keyboard_destroy(userData->wlSeatGroup.wlKeyboard);
		userData->wlSeatGroup.wlKeyboard = NULL;
	}
}

void Window_Internal::onWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
//	WindowEvent *pEvent = (WindowEvent *)data;
//	if (!pEvent)
//		return;

//	pEvent->OnPointerAction(nb::System::PointerAction_Down, surface_x, surface_y);
}

void Window_Internal::onWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
//	WindowEvent *pEvent = (WindowEvent *)data;
//	if (!pEvent)
//		return;

//	pEvent->OnPointerAction(PointerAction_Up, x_pointer_move, y_pointer_move);
}

void Window_Internal::onWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	x_pointer_move = surface_x;
	y_pointer_move = surface_y;
//	WindowEvent *pEvent = (WindowEvent *)data;
//	if (!pEvent)
//		return;

//	pEvent->OnPointerAction(PointerAction_Move, surface_x, surface_y);
}

void Window_Internal::onWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	printf("Window_Internal::onWaylandButton---time[%d], button[%d], state[%d]\r\n", time, button, state);
}

void Window_Internal::onWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
	printf("Window_Internal::onWaylandAxis---time[%d], axis[%d], value[%d]\r\n", time, axis, value);
}

void Window_Internal::onWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	printf("Window_Internal::onWaylandTouchDown---id[%d], x[%d], y[%d]\r\n", id, x, y);
}

void Window_Internal::onWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id)
{
	printf("Window_Internal::onWaylandTouchUp---id[%d]\r\n");
}

void Window_Internal::onWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	printf("Window_Internal::onWaylandTouchMotion---id[%d], x[%d], y[%d]\r\n", id, x, y);
}

void Window_Internal::onWaylandTouchFrame(void *data, struct wl_touch *wl_touch)
{
	printf("Window_Internal::onWaylandTouchFrame\r\n");
}

void Window_Internal::onWaylandTouchCancel(void *data, struct wl_touch *wl_touch)
{
	printf("Window_Internal::onWaylandTouchCancel\r\n");
}

void Window_Internal::onWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys)
{
	printf("Window_Internal::onWaylandKeyEnter\r\n");
}

void Window_Internal::onWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface)
{
	printf("Window_Internal::onWaylandKeyLeave\r\n");
}

void Window_Internal::onWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
	printf("Window_Internal::onWaylandKey---key[%d], state[%d]\r\n", key, state);
}


#endif
