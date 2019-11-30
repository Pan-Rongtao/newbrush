#pragma once
#include "EnumFlags.h"
#include "../core/InputEvent.h"

namespace nb {

struct KeyboardEventArgs : public InputEventArgs
{
	KeyboardEventArgs(int timestamp);
};

//键盘焦点变化事件
class InputElement;
struct KeyboardFocusChangedEventArgs : public KeyboardEventArgs
{
	KeyboardFocusChangedEventArgs(int timestamp, std::shared_ptr<InputElement> oldFocus, std::shared_ptr<InputElement> newFocus);
	std::shared_ptr<InputElement>	OldFocus;
	std::shared_ptr<InputElement>	NewFocus;
};

//按键事件
struct KeyEventArgs : public KeyboardEventArgs
{
	KeyEventArgs(int timestamp, KeyE key);

	KeyE					SystemKey;	//由系统按键引起的键（系统键有F10、左Alt、右Alt）：如果仅按下Alt，[systemKey, key]=[Alt, System]；如果按下Alt+A=[A, System]
	KeyE					Key;		//按键
	EnumFlags<KeyStateE>	KeyState;	//按键状态
};

}