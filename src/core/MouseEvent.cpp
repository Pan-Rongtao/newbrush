#include "core/MouseEvent.h"

using namespace nb;

MouseEventArgs::MouseEventArgs(int timestamp)
	: InputEventArgs(timestamp)
	, LeftButton(MouseButtonState::Released)
	, MiddleButton(MouseButtonState::Released)
	, RightButton(MouseButtonState::Released)
{
}

Point nb::MouseEventArgs::getPosition()
{
	return nb::Point();
}

MouseButtonEventArgs::MouseButtonEventArgs(int timestamp, MouseButton button)
	: MouseEventArgs(timestamp)
	, ChangedButton(button)
	, ButtonState()
	, ClickCount(1)
{
}

MouseWheelEventArgs::MouseWheelEventArgs(int timestamp, int delta)
	: MouseEventArgs(timestamp)
	, Delta(delta)
{
}
