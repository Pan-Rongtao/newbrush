#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include "Window_Wayland.h"
#include "core/Exception.h"
#include "system/Window.h"

using nb::System::String;
using nb::System::RectI;
using nb::System::WindowEvent;
using nb::System::Window;
using nb::System::Window_Wayland;

static wl_fixed_t x_pointer_move = 0;
static wl_fixed_t y_pointer_move = 0;
Window_Wayland::Window_Wayland(Window *pW)
: NativeWindow(pW)
{
	m_wlDisplay = wl_display_connect(NULL);
	if(m_wlDisplay == NULL)
	{
		NB_THROW_EXCEPTION("create window fail.");
		return;
	}

	m_wlRegistry = wl_display_get_registry(m_wlDisplay);
	m_UserData.wlListeners.wlRegistryListener.global = Window_Wayland::OnWaylandRegistryGlobal;
	wl_registry_add_listener(m_wlRegistry, &m_UserData.wlListeners.wlRegistryListener, &m_UserData);
	//一定要同步server端的处理，在回调中拿到各global对象，包括compositor、shell、seat等，并按需注册相应global对象的消息
	wl_display_dispatch(m_wlDisplay);
	wl_display_roundtrip(m_wlDisplay);

	m_wlSurface = wl_compositor_create_surface(m_UserData.wlGlobals.wlCompositor);
	if(m_wlSurface == NULL)
	{
		NB_THROW_EXCEPTION("create surface fail.");
		return;
	}

	m_wlShellSurface = wl_shell_get_shell_surface(m_UserData.wlGlobals.wlShell, m_wlSurface);
	if(m_wlShellSurface == NULL)
	{
		NB_THROW_EXCEPTION("get shell surface fail.");
		return;
	}

	m_wlWindow = wl_egl_window_create(m_wlSurface, 1920, 1080);
	if(m_wlWindow == NULL)
	{
		NB_THROW_EXCEPTION("create window fail.");
		return;
	}

	m_Rect.Reset(0, 0, 800, 480);
}

Window_Wayland::~Window_Wayland()
{
	wl_shell_surface_destroy(m_wlShellSurface);
	wl_surface_destroy(m_wlSurface);
	//是否要删除shell和compositor？
}

void Window_Wayland::SetCaption(const nb::System::String &caption)
{
	wl_shell_surface_set_title(m_wlShellSurface, caption.ToUtf8().GetData());
	m_Caption = caption;
}

nb::System::String Window_Wayland::GetCaption() const
{
	return m_Caption;
}

void Window_Wayland::SetRect(const nb::System::RectI &rect)
{
//	wl_shell_surface_resize(m_wlShellSurface, m_wlGlobals.wlSeat, );
}

nb::System::RectI Window_Wayland::GetRect() const
{
	return m_Rect;
}

long Window_Wayland::GetWindowHandle()
{
	return (long)m_wlWindow;
}

void Window_Wayland::Pending()
{
	wl_display_dispatch_pending(m_wlDisplay);
}

void Window_Wayland::OnWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version)
{
	UserData *userData = (UserData *)data;
	if(strcmp(interface, "wl_compositor") == 0)
	{
		userData->wlGlobals.wlCompositor = (wl_compositor *)wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1);
	}
	else if(strcmp(interface, "wl_shell") == 0)
	{
		userData->wlGlobals.wlShell = (wl_shell *)wl_registry_bind(wl_registry, name, &wl_shell_interface, 1);
	}
	else if(strcmp(interface, "wl_seat") == 0)
	{
		userData->wlGlobals.wlSeat = (wl_seat *)wl_registry_bind(wl_registry, name, &wl_seat_interface, 1);
		userData->wlListeners.wlSeatListener.capabilities = Window_Wayland::OnWaylandSeatCapabilitties;
		wl_seat_add_listener(userData->wlGlobals.wlSeat, &userData->wlListeners.wlSeatListener, userData);
	}
}

void Window_Wayland::OnWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
	UserData *userData = (UserData *)data;
	if((capabilities & WL_SEAT_CAPABILITY_POINTER) && userData->wlSeatGroup.wlPointer == NULL)
	{
		userData->wlSeatGroup.wlPointer = wl_seat_get_pointer(wl_seat);
		userData->wlListeners.wlPointerListener.enter = Window_Wayland::OnWaylandPointerEnter;
		userData->wlListeners.wlPointerListener.leave = Window_Wayland::OnWaylandPointerLeave;
		userData->wlListeners.wlPointerListener.motion = Window_Wayland::OnWaylandPointerMotion;
		userData->wlListeners.wlPointerListener.button = Window_Wayland::OnWaylandPointerButton;
		userData->wlListeners.wlPointerListener.axis = Window_Wayland::OnWaylandPointerAxis;
		wl_pointer_add_listener(userData->wlSeatGroup.wlPointer, &userData->wlListeners.wlPointerListener, userData);
	}
	else if(!(capabilities & WL_SEAT_CAPABILITY_POINTER) && userData->wlSeatGroup.wlPointer)
	{
		wl_pointer_destroy(userData->wlSeatGroup.wlPointer);
		userData->wlSeatGroup.wlPointer = NULL;
	}
	if((capabilities & WL_SEAT_CAPABILITY_TOUCH) && userData->wlSeatGroup.wlTouch == NULL)
	{
		userData->wlSeatGroup.wlTouch = wl_seat_get_touch(wl_seat);
		userData->wlListeners.wlTouchListener.down = Window_Wayland::OnWaylandTouchDown;
		userData->wlListeners.wlTouchListener.up = Window_Wayland::OnWaylandTouchUp;
		userData->wlListeners.wlTouchListener.motion = Window_Wayland::OnWaylandTouchMotion;
		userData->wlListeners.wlTouchListener.frame = Window_Wayland::OnWaylandTouchFrame;
		userData->wlListeners.wlTouchListener.cancel = Window_Wayland::OnWaylandTouchCancel;
		wl_touch_add_listener(userData->wlSeatGroup.wlTouch, &userData->wlListeners.wlTouchListener, userData);
	}
	else if(!(capabilities & WL_SEAT_CAPABILITY_TOUCH) && userData->wlSeatGroup.wlTouch)
	{
		wl_touch_destroy(userData->wlSeatGroup.wlTouch);
		userData->wlSeatGroup.wlTouch = NULL;
	}
	if((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && userData->wlSeatGroup.wlKeyboard == NULL)
	{
		userData->wlSeatGroup.wlKeyboard = wl_seat_get_keyboard(wl_seat);
		userData->wlListeners.wlKeyboardListener.enter = Window_Wayland::OnWaylandKeyEnter;
		userData->wlListeners.wlKeyboardListener.leave = Window_Wayland::OnWaylandKeyLeave;
		userData->wlListeners.wlKeyboardListener.key = Window_Wayland::OnWaylandKey;
		wl_keyboard_add_listener(userData->wlSeatGroup.wlKeyboard, &userData->wlListeners.wlKeyboardListener, userData);
	}
	else if(!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && userData->wlSeatGroup.wlKeyboard)
	{
		wl_keyboard_destroy(userData->wlSeatGroup.wlKeyboard);
		userData->wlSeatGroup.wlKeyboard = NULL;
	}
}

void Window_Wayland::OnWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	WindowEvent *pEvent = (WindowEvent *)data;
	if(!pEvent)
		return;

	pEvent->OnPointerAction(nb::System::WindowEvent::PointerAction_Down, surface_x, surface_y);
}

void Window_Wayland::OnWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
	WindowEvent *pEvent = (WindowEvent *)data;
	if(!pEvent)
		return;

	pEvent->OnPointerAction(WindowEvent::PointerAction_Up, x_pointer_move, y_pointer_move);
}

void Window_Wayland::OnWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	x_pointer_move = surface_x;
	y_pointer_move = surface_y;
	WindowEvent *pEvent = (WindowEvent *)data;
	if(!pEvent)
		return;

	pEvent->OnPointerAction(WindowEvent::PointerAction_Move, surface_x, surface_y);
}

void Window_Wayland::OnWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	printf("Window_Wayland::OnWaylandButton---time[%d], button[%d], state[%d]\r\n", time, button, state);
}

void Window_Wayland::OnWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
	printf("Window_Wayland::OnWaylandAxis---time[%d], axis[%d], value[%d]\r\n", time, axis, value);
}

void Window_Wayland::OnWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	printf("Window_Wayland::OnWaylandTouchDown---id[%d], x[%d], y[%d]\r\n", id, x, y);
}

void Window_Wayland::OnWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id)
{
	printf("Window_Wayland::OnWaylandTouchUp---id[%d]\r\n");
}

void Window_Wayland::OnWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y)
{
	printf("Window_Wayland::OnWaylandTouchMotion---id[%d], x[%d], y[%d]\r\n", id, x, y);
}

void Window_Wayland::OnWaylandTouchFrame(void *data, struct wl_touch *wl_touch)
{
	printf("Window_Wayland::OnWaylandTouchFrame\r\n");
}

void Window_Wayland::OnWaylandTouchCancel(void *data, struct wl_touch *wl_touch)
{
	printf("Window_Wayland::OnWaylandTouchCancel\r\n");
}

void Window_Wayland::OnWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys)
{
	printf("Window_Wayland::OnWaylandKeyEnter\r\n");
}

void Window_Wayland::OnWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface)
{
	printf("Window_Wayland::OnWaylandKeyLeave\r\n");
}

void Window_Wayland::OnWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
	printf("Window_Wayland::OnWaylandKey---key[%d], state[%d]\r\n", key, state);
}

#endif
