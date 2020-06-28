#include "newbrush/core/EventArgs.h"

using namespace nb;

RoutedEventArgs::RoutedEventArgs()
	: RoutedEventArgs(RoutedEvent::invalid())
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent)
	: RoutedEventArgs(routedEvent, nullptr)
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent, Object *source)
	: Handled(false)
	, Event(routedEvent)
	, OriginalSource(nullptr)
	, Source(source)
{
}

InputEventArgs::InputEventArgs(int timestamp)
	: Timestamp(timestamp)
{
}

KeyboardEventArgs::KeyboardEventArgs(int timestamp)
	: InputEventArgs(timestamp)
{
}

KeyEventArgs::KeyEventArgs(int timestamp, KeyE key)
	: KeyboardEventArgs(timestamp)
	, Key(key)
{
	Timestamp = timestamp;
}

KeyboardFocusChangedEventArgs::KeyboardFocusChangedEventArgs(int timestamp, InputElementPtr oldFocus, InputElementPtr newFocus)
	: KeyboardEventArgs(timestamp)
	, OldFocus(oldFocus)
	, NewFocus(newFocus)
{
}

KeyStateE Keyboard::getKeyState(KeyE key)
{
	return KeyStateE();
}

bool Keyboard::isKeyDown(KeyE key)
{
	return false;
}

bool Keyboard::isKeyUp(KeyE key)
{
	return false;
}

bool Keyboard::isKeyToggled(KeyE key)
{
	return false;
}

InputElementPtr Keyboard::focus(InputElementPtr element)
{
	return InputElementPtr();
}

MouseEventArgs::MouseEventArgs(int timestamp)
	: InputEventArgs(timestamp)
	, LeftButton(MouseButtonStateE::Released)
	, MiddleButton(MouseButtonStateE::Released)
	, RightButton(MouseButtonStateE::Released)
{
}

Point MouseEventArgs::getPosition(InputElementPtr relativeTo) const
{
	return Point();
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

TouchEventArgs::TouchEventArgs(int timestamp)
	: InputEventArgs(timestamp)
{
}

Point TouchEventArgs::getTouchPoint() const
{
	return Point();
}
