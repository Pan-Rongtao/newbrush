#include "core/EventArgs.h"

using namespace nb;

RoutedEventArgs::RoutedEventArgs()
	: RoutedEventArgs(RoutedEvent())
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent)
	: RoutedEventArgs(routedEvent, Object())
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent, const Object &source)
	: Handled(false)
	, Event(routedEvent)
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

KeyboardFocusChangedEventArgs::KeyboardFocusChangedEventArgs(int timestamp, std::shared_ptr<InputElement> oldFocus, std::shared_ptr<InputElement> newFocus)
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

std::shared_ptr<InputElement> Keyboard::focus(std::shared_ptr<InputElement> element)
{
	return std::shared_ptr<InputElement>();
}

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

TouchEventArgs::TouchEventArgs(int timestamp)
	: InputEventArgs(timestamp)
{
}

Point TouchEventArgs::getTouchPoint() const
{
	return Point();
}
