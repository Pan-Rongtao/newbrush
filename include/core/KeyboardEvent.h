#pragma once
#include "EnumFlags.h"
#include "../core/InputEvent.h"

namespace nb {

class KeyboardEventArgs : public InputEventArgs
{
};

//按键事件
class KeyEventArgs : public KeyboardEventArgs
{
public:
	KeyEventArgs(int timestamp, KeyE key);

	KeyE					SystemKey;	//由系统按键引起的键（系统键有F10、左Alt、右Alt）：如果仅按下Alt，[systemKey, key]=[Alt, System]；如果按下Alt+A=[A, System]
	KeyE					Key;		//按键
	EnumFlags<KeyStateE>	KeyState;	//按键状态
};

}