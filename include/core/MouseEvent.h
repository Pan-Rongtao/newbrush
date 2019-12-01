#pragma once
#include "../core/InputEvent.h"
#include "../core/Point.h"

namespace nb {

enum class MouseButton : uint8_t
{
	Left,
	Middle,
	Right,
};

enum class MouseButtonState : uint8_t
{
	Released,
	Pressed,
};

class MouseEventArgs : public InputEventArgs
{
public:
	MouseEventArgs(int timestamp);

	nb::Point getPosition();

	MouseButtonState	LeftButton;
	MouseButtonState	MiddleButton;
	MouseButtonState	RightButton;
};

class MouseButtonEventArgs : public MouseEventArgs
{
public:
	MouseButtonEventArgs(int timestamp, MouseButton button);

	MouseButton			ChangedButton;
	MouseButtonState	ButtonState;
	int					ClickCount;
};

class MouseWheelEventArgs : public MouseEventArgs
{
public:
	MouseWheelEventArgs(int timestamp, int delta);

	int	Delta;
};

}