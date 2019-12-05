#include "core/MouseEvent.h"

using namespace nb;

MouseEventArgs::MouseEventArgs(int timestamp)
	: InputEventArgs(timestamp)
	, LeftButton(MouseButtonStateE::Released)
	, MiddleButton(MouseButtonStateE::Released)
	, RightButton(MouseButtonStateE::Released)
{
}

Point MouseEventArgs::getPosition(std::shared_ptr<InputElement> relativeTo)
{
	return nb::Point();
}

MouseButtonEventArgs::MouseButtonEventArgs(int timestamp, MouseButtonE button)
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
