#include "core/KeyboardEvent.h"

using namespace nb;

KeyEventArgs::KeyEventArgs(int timestamp, KeyE key)
	: Key(key)
{
	Timestamp = timestamp;
}
