#include "core/KeyboardEvent.h"

using namespace nb;

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
