#pragma once
#include "newbrush/Core.h"
#include <unordered_map>
#include <functional>

namespace nb
{

template<class ArgsT>
class NB_API Event
{
	using CallBack = std::function<void(ArgsT &)>;
	using CallBackContainer = std::unordered_map<int, CallBack>;
public:
	Event() : m_callbacks(nullptr), m_nextID(0)			{}
	Event(const Event &other) : m_callbacks(nullptr)	{ *this = other; }
	~Event()											{ delete m_callbacks; }

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
		if (!m_callbacks)	
			return;

		auto iter = m_callbacks->find(handler);
		if(iter != m_callbacks->end())
			m_callbacks->erase(handler);
	}

	void clear()
	{
		if (!m_callbacks)	
			return;

		m_callbacks->clear();
	}

	std::size_t size() const
	{
		return m_callbacks ? m_callbacks->size() : 0;
	}

	void invoke(ArgsT &args) const
	{
		invoke(const_cast<const ArgsT &>(args));
	}

	void invoke(const ArgsT &args) const
	{
		if (!m_callbacks)	return;
		for (const auto &callback : *m_callbacks)
			if (callback.second)
				callback.second(const_cast<ArgsT &>(args));
	}

	void operator += (CallBack callback)
	{
		addHandler(callback);
	}

	void operator -=(int handler)
	{
		removeHandler(handler);
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

enum class TouchActionE : uint8_t
{
	enter,
	down,
	move,
	up,
	leave,
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
	TouchActionE action;
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
	space			= 32,
	apostrophe		= 39,  /* ' */
	comma			= 44,  /* , */
	minus			= 45,  /* - */
	period			= 46,  /* . */
	slash			= 47,  /* / */
	_0				= 48, _1, _2, _3, _4, _5, _6, _7, _8, _9,
	semicolon		= 59,  /* ; */
	equal			= 61,  /* = */
	A				= 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	leftBracket		= 91,  /* [ */
	backSlash		= 92,  /* \ */
	rightBracket	= 93,  /* ] */
	graveAccent		= 96,  /* ` */
	world1			= 161, /* non-US #1 */
	world2			= 162, /* non-US #2 */

	/* Function keys */
	escape			= 256, enter, tab, backspace, insert, del, right, left, down, up, pageUp, pageDown, home, end,
	capsLock		= 280,
	scrollLock		= 281,
	numLock			= 282,
	printScreen		= 283,
	pause			= 284,
	F1				= 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25,
	kp_0			= 320, kp_1, kp_2, kp_3, kp_4, kp_5, kp_6, kp_7, kp_8, kp_9, 
	kp_decimal		= 330, kp_divide, kp_multiply, kp_subtract, kp_add, kp_enter, kp_equal,
	leftShift		= 340, leftControl, leftAlt, leftSuper, rightShift, rightControl, rightAlt, rightSuper,
	menu			= 348,
};

enum class KeyAction
{
	down,
	up,
	repeat,
};

enum KeyMode
{
	shift		= 0x0001,
	control		= 0x0002,
	alt			= 0x0004,
	super		= 0x0008,
	capsLock	= 0x0010,
	numLock		= 0x0020,
};

struct KeyEventArgs : public EventArgs
{
	KeyCode key;
	KeyAction action;
	int scancode;
	int mods;
};

}
