#pragma once
#include <map>
#include "core/Def.h"
#include "core/Window.h"
#ifdef NB_OS_FAMILY_WINDOWS
	#include <Windows.h>
	#include <WindowsX.h>
#elif defined NB_OS_FAMILY_UNIX
	#include <X11/X.h>
	#include <X11/Xlib.h>
#elif NB_OS == NB_OS_LINUX_ARM
	#include <wayland-client.h>
	#include <wayland-egl.h>
#endif

namespace nb{ namespace core{

class Window_Internal
{
public:
	Window_Internal(Window *p);
	~Window_Internal();

	void setTitle(const std::string &title);
	std::string title() const;

	void setX(int x);
	int x() const;

	void setY(int y);
	int y() const;

	void setWidth(int width);
	int width() const;

	void setHeight(int height);
	int height() const;

	int clientWidth() const;
	int clientHeight() const;

	long handle() const;

	void setTopMost(bool topMost);
	bool topMost() const;

	void setWindowState(WindowStateE state);
	WindowStateE getWindowState() const;

	void setWindowStyle(WindowStyleE style);
	WindowStyleE getWindowStyle() const;
	
	void show(bool show);
	bool isShow() const;

	void active();

	void pending();

private:
	Window				*m_pW;

	//根据不同平台的私有变量和私有函数
#ifdef NB_OS_FAMILY_WINDOWS
	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HINSTANCE						m_instance;
	HWND							m_hwnd;
	static std::map<long, Window *>	m_windows;
#elif defined NB_OS_FAMILY_UNIX
	void x11WindowPending();
	WindowEvent::KeyCode nativeKeyToKeycode(int key);
	::Display						*m_X11Display;
	::Window						m_X11WindowID;
	nb::core::RectI					m_rect;
	static wl_fixed_t x_pointer_move = 0;
	static wl_fixed_t y_pointer_move = 0;
#elif NB_OS == NB_OS_LINUX_ARM
	//wl_registry global消息
	static void onWaylandRegistryGlobal(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version);

	//wl_seat capabilities消息
	static void onWaylandSeatCapabilitties(void *data, struct wl_seat *wl_seat, uint32_t capabilities);

	//wl_pointer enter、leave、motion，button，axis消息
	static void onWaylandPointerEnter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void onWaylandPointerLeave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface);
	static void onWaylandPointerMotion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y);
	static void onWaylandPointerButton(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state);
	static void onWaylandPointerAxis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

	//wl_touch down、up、motion、cancel消息
	static void onWaylandTouchDown(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, struct wl_surface *surface, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void onWaylandTouchUp(void *data, struct wl_touch *wl_touch, uint32_t serial, uint32_t time, int32_t id);
	static void onWaylandTouchMotion(void *data, struct wl_touch *wl_touch, uint32_t time, int32_t id, wl_fixed_t x, wl_fixed_t y);
	static void onWaylandTouchFrame(void *data, struct wl_touch *wl_touch);
	static void onWaylandTouchCancel(void *data, struct wl_touch *wl_touch);

	//wl_keyboard 消息
	static void onWaylandKeyEnter(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys);
	static void onWaylandKeyLeave(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, struct wl_surface *surface);
	static void onWaylandKey(void *data, struct wl_keyboard *wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);


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
		UserData() {}

		Globals						wlGlobals;					//全局对象结构，作为userdata传入
		SeatGroup					wlSeatGroup;				//设备组结构，作为userdata传入
		Listeners					wlListeners;				//监听结构
	//	WindowEvent *				windowEvent;
	};

	wl_display						*m_wlDisplay;				//wayland服务的连接
	wl_registry						*m_wlRegistry;				//全局对象注册表
	wl_surface						*m_wlSurface;				//wayland surface
	wl_shell_surface				*m_wlShellSurface;			//wayland shell surface
	wl_egl_window					*m_wlWindow;				//wayland window（egl nativewindow）
	UserData						m_UserData;
#endif
};



}}
