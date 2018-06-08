#pragma once
#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_LINUX_ARM
#include <wayland-client.h>
#include <wayland-egl.h>
#include "NativeWindow.h"

namespace nb{ namespace System{

class Window;
class Window_Wayland : public NativeWindow
{
public:
	Window_Wayland(Window *pW);
	~Window_Wayland();

	virtual void SetCaption(const nb::System::String &caption);
	virtual nb::System::String GetCaption() const;

	virtual void SetRect(const nb::System::RectI &rect);
	virtual nb::System::RectI GetRect() const;

	virtual long GetWindowHandle();

	virtual void Pending();

private:
	//wl_registry global消息
	static void OnWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version);

	//wl_seat capabilities消息
	static void OnWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities);

	//wl_pointer enter、leave、motion，button，axis消息
	static void OnWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void OnWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface);
	static void OnWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void OnWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
	static void OnWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

	//wl_touch down、up、motion、cancel消息
	static void OnWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void OnWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id);
	static void OnWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void OnWaylandTouchFrame(void *data, struct wl_touch *wl_touch);
	static void OnWaylandTouchCancel(void *data, struct wl_touch *wl_touch);

	//wl_keyboard 消息
	static void OnWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys);
	static void OnWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface);
	static void OnWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);


	//wayland全局对象只能通过wl_registry_listener消息中获取
	struct Globals
	{
		Globals() : wlCompositor(NULL), wlShell(NULL), wlSeat(NULL) {}

		wl_compositor				*wlCompositor;				//窗口合成器（服务器）全局对象
		wl_shell					*wlShell;					//shell全局对象
		wl_seat						*wlSeat;					//设备管理器全局对象
	};
	struct SeatGroup
	{
		SeatGroup() : wlPointer(NULL), wlTouch(NULL), wlKeyboard(NULL) {}

		wl_pointer					*wlPointer;					//手指触控
		wl_touch					*wlTouch;					//多点触摸
		wl_keyboard					*wlKeyboard;				//键盘设备
	};
	struct Listeners
	{
		wl_registry_listener		wlRegistryListener;			//全局对象监听
		wl_seat_listener			wlSeatListener;				//设备管理监听
		wl_pointer_listener			wlPointerListener;			//手指触控监听
		wl_touch_listener			wlTouchListener;			//多点触摸监听
		wl_keyboard_listener		wlKeyboardListener;			//键盘监听
		wl_surface_listener			wlShellListener;			//shell监听
		wl_shell_surface_listener	wlShellSurfaceListener;		//shell surface监听
	};
	struct UserData
	{
		UserData() : windowEvent(NULL) {}

		Globals						wlGlobals;					//全局对象结构，作为userdata传入
		SeatGroup					wlSeatGroup;				//设备组结构，作为userdata传入
		Listeners					wlListeners;				//监听结构
		WindowEvent *				windowEvent;
	};

	wl_display						*m_wlDisplay;				//wayland服务的连接
	wl_registry						*m_wlRegistry;				//全局对象注册表
	wl_surface						*m_wlSurface;				//wayland surface
	wl_shell_surface				*m_wlShellSurface;			//wayland shell surface
	wl_egl_window					*m_wlWindow;				//wayland window（egl nativewindow）
	UserData						m_UserData;

	nb::System::String				m_Caption;
	nb::System::RectI				m_Rect;
};

}}

#endif
