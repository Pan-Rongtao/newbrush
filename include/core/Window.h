#pragma once
#include "../core/Def.h"
#include "../core/Event.h"
#include <string>

namespace nb{ namespace core{

enum class WindowStateE
{
	Normal,
	Maximized,
	Minimized,
	FullScreen,
};

enum class WindowStyleE
{
	None,
	Fixed,
	SizeBox,
};

enum class KeyCodeE
{
	Unknown = -1,
	Esc		= 0x00,
	F1		= 0x01, F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
	Space	= 0x20,
	A		= 0x41, B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	Left,Up,Right,Down,
	Add,Sub,
};

class Window_Internal;
class NB_API Window
{
public:
	//构建一个Window对象，它的标题为空，区域为(x-middle, y-middle, 800, 480)
	Window();

	//构建一个Window对象，它的标题为空，区域为(x-middle, y-middle, width, height)
	Window(int width, int height);

	//构建一个Window对象，它的标题为空，区域为(x, y, width, height)
	Window(int x, int y, int width, int height);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, 800, 480)
	explicit Window(const std::string &title);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, width, height)
	Window(const std::string &title, int width, int height);

	//构建一个Window对象，它的标题为title，区域为(x-middle, y-middle, width, height)
	Window(const std::string &title, int x, int y, int width, int height);
	virtual ~Window();

	//设置窗口标题
	void setTitle(const std::string &title);

	//获取窗口标题
	std::string title() const;

	//设置窗口位置x（如果在win32环境下，为边框的左边距）
	void setX(int x);

	//获取窗口x（如果在win32环境下，为边框的左边距）
	int x() const;

	//设置窗口位置y（如果在win32环境下，为边框的上边距）
	void setY(int y);

	//获取窗口y（如果在win32环境下，为边框的上边距）
	int y() const;

	//设置窗口客户端宽度width
	//异常：width < 0
	void setWidth(int width);

	//获取窗口客户端宽度
	int width() const;

	//设置窗口客户端高度
	//异常：height < 0
	void setHeight(int height);

	//获取窗口客户端高度
	int height() const;	

	//获取客户区
	int clientWidth() const;
	int clientHeight() const;

	//检查窗口事件
	void pending();

	//窗口句柄
	long handle() const;

	//窗口置顶（仅windows下有效）
	void setTopMost(bool topMost);
	bool topMost() const;

	//窗口状态
	void setWindowState(WindowStateE state);
	WindowStateE getWindowState() const;

	//窗口样式
	void setWindowStyle(WindowStyleE style);
	WindowStyleE getWindowStyle() const;

	//显示隐藏，仅将窗口显示隐藏，并非激活到前台
	void show(bool show);
	bool isShow() const;

	//激活窗口，如果窗口未显示，则无效
	void active();

	//尺寸重置事件
	struct ResizeArgs { int width; int height; };
	nb::core::Event<ResizeArgs>			ResizeEvent;

	//鼠标进入事件
	struct MouseEnterEventArgs { };
	nb::core::Event<MouseEnterEventArgs>		MouseEnterEvent;

	//鼠标移动事件
	struct MouseMoveEventArgs { int x; int y; };
	nb::core::Event<MouseMoveEventArgs>			MouseMoveEvent;

	//鼠标离开事件
	struct MouseLeaveEventArgs { };
	nb::core::Event<MouseLeaveEventArgs>		MouseLeaveEvent;

	//鼠标左键事件
	struct MouseLeftButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseLeftButtonEventArgs>	MouseLeftButtonEvent;

	//鼠标右键事件
	struct MouseRightButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseRightButtonEventArgs>	MouseRightButtonEvent;

	//鼠标中键事件
	struct MouseMiddleButtonEventArgs { bool pressed; int x; int y; };
	nb::core::Event<MouseMiddleButtonEventArgs>	MouseMiddleButtonEvent;

	//鼠标滚轮事件
	struct MouseWheelEventArgs { int delta; };
	nb::core::Event<MouseWheelEventArgs>		MouseWheelEvent;

	//键盘事件
	struct KeyEventArgs { bool down; KeyCodeE key; int mask; };
	nb::core::Event<KeyEventArgs>				KeyEvent;

private:
	Window_Internal	*m_internal;
};

}}
