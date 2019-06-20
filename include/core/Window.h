#pragma once
#include "../core/Def.h"
#include "../core/Event.h"
#include <string>

namespace nb{ namespace core{

class Window_Internal;
class NB_API Window
{
public:
	enum KeyAction
	{
		KeyAction_Down,
		KeyAction_Up,
		KeyAction_LongPress,
	};

	enum KeyCode
	{
		VKey_Unknown = -1,

		VKey_Esc = 0x00,

		VKey_F1 = 0x01,
		VKey_F2 = 0x02,
		VKey_F3 = 0x03,
		VKey_F4 = 0x04,
		VKey_F5 = 0x05,
		VKey_F6 = 0x06,
		VKey_F7 = 0x07,
		VKey_F8 = 0x08,
		VKey_F9 = 0x09,
		VKey_F10 = 0x0A,
		VKey_F11 = 0x0B,
		VKey_F12 = 0x0C,

		VKey_Space = 0x20,

		VKey_A = 0x41,
		VKey_B,
		VKey_C,
		VKey_D,
		VKey_E,
		VKey_F,
		VKey_G,
		VKey_H,
		VKey_I,
		VKey_J,
		VKey_K,
		VKey_L,
		VKey_M,
		VKey_N,
		VKey_O,
		VKey_P,
		VKey_Q,
		VKey_R,
		VKey_S,
		VKey_T,
		VKey_U,
		VKey_V,
		VKey_W,
		VKey_X,
		VKey_Y,
		VKey_Z,

		VKey_Left,
		VKey_Up,
		VKey_Right,
		VKey_Down,

		VKey_Add,
		VKey_Sub,
	};

	enum PointerAction
	{
		PointerAction_Down,
		PointerAction_Move,
		PointerAction_Up,
		PointerAction_Click,
		PointerAction_LongPress,
	};

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

public:
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

	//检查窗口事件
	void pending();

	//窗口句柄
	long handle() const;

	//置顶（仅windows下有效）
	void setTopMost(bool topMost);
	bool topMost() const;

	//尺寸重置事件
	struct ResizeArgs { int width; int height; };
	nb::core::Event<ResizeArgs>			ResizeEvent;

	//鼠标事件
	struct PointerEventArgs { PointerAction action; int x; int y; };
	nb::core::Event<PointerEventArgs>	PointerEvent;

	//键盘事件
	struct KeyEventArgs { KeyAction action; KeyCode key; int mask; };
	nb::core::Event<KeyEventArgs>		KeyEvent;

private:
	Window_Internal	*m_internal;
};

}}
