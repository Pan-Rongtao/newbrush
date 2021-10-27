#pragma once
#include <unordered_map>
#include <functional>
#include <vector>

namespace nb
{

template<class ArgsT>
class Event
{
	using CallBack = std::function<void(ArgsT &)>;
	using CallBackContainer = std::unordered_map<int, CallBack>;
public:
	Event() : m_callbacks(nullptr), m_nextID(0)			{}
	Event(const Event &other) : m_callbacks(nullptr)	{ *this = other; }
	~Event()											{ delete m_callbacks; }

	std::size_t size() const							{ return m_callbacks ? m_callbacks->size() : 0; }
	void clear()										{ if (m_callbacks) m_callbacks->clear(); }
	void invoke(ArgsT &args) const						{ invoke(const_cast<const ArgsT &>(args)); }
	int operator += (CallBack callback)					{ return addHandler(callback); }
	void operator -=(int handler)						{ removeHandler(handler); }

	void operator = (const Event &other)
	{
		CallBackContainer *pNew = other.m_callbacks ? new CallBackContainer(*(other.m_callbacks)) : nullptr;
		delete m_callbacks;
		m_callbacks = pNew;
		m_nextID = other.m_nextID;
	}

	int addHandler(CallBack callback)
	{
		if (!m_callbacks)
			m_callbacks = new CallBackContainer();

		int id = m_nextID++;
		m_callbacks->insert({ id, callback });
		return id;
	}

	void removeHandler(int handler)
	{
		if (m_callbacks)
		{
			auto iter = m_callbacks->find(handler);
			if (iter != m_callbacks->end())
				m_callbacks->erase(handler);
		}
	}


	void invoke(const ArgsT &args) const
	{
		if (m_callbacks)
		{
			for (const auto &callback : *m_callbacks)
				if (callback.second)
					callback.second(const_cast<ArgsT &>(args));
		}
	}

private:
	CallBackContainer *m_callbacks;
	uint32_t m_nextID;
};

class Object;
struct EventArgs 
{ 
	Object *sender;
};

enum class TouchAction : uint8_t
{
	Enter,
	Down,
	Move,
	Up,
	Leave,
};

struct ExitEventArgs : public EventArgs
{
	int exitCode; 
};

struct StartupEventArgs : public EventArgs
{ 
	std::vector<std::string> args;
};

struct CancelEventArgs : public EventArgs 
{ 
	bool cancel = false; 
};

struct TouchEventArgs : public EventArgs 
{
	TouchAction action;
	float x;
	float y;
};

struct DropEventArgs : public EventArgs
{
	std::vector<std::string> paths;
};

struct ScrollEventArgs : public EventArgs
{
	int delta;
};

struct FocusEventArgs : public EventArgs
{
	bool focused;
};

enum class KeyCode
{
	Space			= 32,
	Apostrophe		= 39,  /* ' */
	Comma			= 44,  /* , */
	Minus			= 45,  /* - */
	Period			= 46,  /* . */
	Slash			= 47,  /* / */
	_0				= 48, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	Semicolon		= 59,  /* ; */
	Equal			= 61,  /* = */
	A				= 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	LeftBracket		= 91,  /* [ */
	BackSlash		= 92,  /* \ */
	RightBracket	= 93,  /* ] */
	GraveAccent		= 96,  /* ` */
	World1			= 161, /* non-US #1 */
	World2			= 162, /* non-US #2 */

	/* Function keys */
	Escape			= 256, Enter, Tab, Backspace, Insert, Del, Right, Left, Down, Up, PageUp, PageDown, Home, End,
	CapsLock		= 280,
	ScrollLock		= 281,
	NumLock			= 282,
	PrintScreen		= 283,
	Pause			= 284,
	F1				= 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
	KP_0			= 320, KP_1, KP_2, KP_3, KP_4, KP_5, KP_6, KP_7, KP_8, KP_9,
	KP_Decimal		= 330, KP_Divide, KP_Multiply, KP_Subtract, KP_Add, KP_Enter, KP_Equal,
	LeftShift		= 340, LeftControl, LeftAlt, LeftSuper, RightShift, RightControl, RightAlt, RightSuper,
	Menu			= 348,
};

enum class KeyAction
{
	Down,
	Up,
	Repeat,
};

enum KeyMode
{
	Shift		= 0x0001,
	Control		= 0x0002,
	Alt			= 0x0004,
	Super		= 0x0008,
	CapsLock	= 0x0010,
	NumLock		= 0x0020,
};

struct KeyEventArgs : public EventArgs
{
	KeyCode key;
	KeyAction action;
	int scancode;
	int mods;
};

}
