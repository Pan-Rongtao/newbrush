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
	Event() : m_callbacks(nullptr), m_nextID(0) {}
	~Event() { delete m_callbacks; }
	Event(const Event &other)
		: m_callbacks(nullptr)
	{
		*this = other;
	}
	void operator = (const Event &other)
	{
		CallBackContainer *pNew = other.m_callbacks ? new CallBackContainer(*(other.m_callbacks)) : nullptr;
		delete m_callbacks;
		m_callbacks = pNew;
		m_nextID = other.m_nextID;
	}

	int addHandler(CallBack callback)
	{
		if (!m_callbacks) m_callbacks = new CallBackContainer();

		int id = m_nextID++;
		m_callbacks->insert({ id, callback });
		return id;
	}

	void removeHandler(int handler)
	{
		if (!m_callbacks)	return;
		auto iter = m_callbacks->find(handler);
		if(iter != m_callbacks->end())
			m_callbacks->erase(handler);
	}

	void clear()
	{
		if (!m_callbacks)	return;
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

struct CancelEventArgs : public EventArgs 
{ 
	bool cancel = false; 
};

struct KeyEventArgs : public EventArgs 
{ 
	int key; 
	int scancode;
	int action;
	int mods;
};

struct TouchEventArgs : public EventArgs 
{
	TouchActionE action;
	float x;
	float y;
};

struct FocusEventArgs : public EventArgs
{
	bool focused;
};

}
