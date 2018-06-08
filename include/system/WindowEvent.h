#pragma once

namespace nb{ namespace System{

class WindowEvent
{
public:
	enum PrimaryAction
	{
		PrimaryAction_Create,
		PrimaryAction_Destroy,
	};
	enum KeyAction
	{
		KeyAction_Down,
		KeyAction_Up,
		KeyAction_LongPress,
	};

	enum KeyCode
	{
		VKey_Unknown	= -1,

		VKey_Esc	= 0x00,

		VKey_F1		= 0x01,
		VKey_F2		= 0x02,
		VKey_F3		= 0x03,
		VKey_F4		= 0x04,
		VKey_F5		= 0x05,
		VKey_F6		= 0x06,
		VKey_F7		= 0x07,
		VKey_F8		= 0x08,
		VKey_F9		= 0x09,
		VKey_F10	= 0x0A,
		VKey_F11	= 0x0B,
		VKey_F12	= 0x0C,

		VKey_Space	= 0x20,

		VKey_A		= 0x41,
		VKey_B,
		VKey_C,
		VKey_D,
		VKey_E,
		VKey_F,
		VKey_G,
		VKey_H,
		VKey_I,
		VKey_J,
		VKey_K,
		VKey_L,
		VKey_M,
		VKey_N,
		VKey_O,
		VKey_P,
		VKey_Q,
		VKey_R,
		VKey_S,
		VKey_T,
		VKey_U,
		VKey_V,
		VKey_W,
		VKey_X,
		VKey_Y,
		VKey_Z,

		VKey_Left	= 0x50,
		VKey_Up		= 0x51,
		VKey_Right	= 0x52,
		VKey_Down	= 0x53,
	};

	enum PointerAction
	{
		PointerAction_Down,
		PointerAction_Move,
		PointerAction_Up,
		PointerAction_Click,
		PointerAction_LongPress,
	};

	virtual void OnPrimaryAction(PrimaryAction action)					{}
	virtual void OnResize(int width, int height)						{}
	virtual void OnPointerAction(PointerAction action, int x, int y)	{}
	virtual void OnKeyAction(KeyAction action, KeyCode key, int mask)	{}
};

}}
