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
