#pragma once
#include "../core/InputEvent.h"
#include "../core/Point.h"

namespace nb {

enum class MouseButtonE : uint8_t
{
	Left,		//左按钮
	Middle,		//中间按钮
	Right,		//右按钮
};

enum class MouseButtonStateE : uint8_t
{
	Released,	//已释放
	Pressed,	//已压下
};

class InputElement;
class NB_API MouseEventArgs : public InputEventArgs
{
public:
	MouseEventArgs(int timestamp);

	nb::Point getPosition(std::shared_ptr<InputElement> relativeTo);			//获取光标相对于指定元素的位置

	MouseButtonStateE	LeftButton;		//左按钮状态
	MouseButtonStateE	MiddleButton;	//中间按钮状态
	MouseButtonStateE	RightButton;	//右按钮状态
};

class NB_API MouseButtonEventArgs : public MouseEventArgs
{
public:
	MouseButtonEventArgs(int timestamp, MouseButtonE button);

	MouseButtonE		ChangedButton;	//触发的按钮
	MouseButtonStateE	ButtonState;	//按钮状态
	int					ClickCount;		//点击次数，可处理单击、双击、三击的判定
};

class NB_API MouseWheelEventArgs : public MouseEventArgs
{
public:
	MouseWheelEventArgs(int timestamp, int delta);

	int	Delta;							//滚动值
};

}