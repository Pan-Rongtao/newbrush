﻿#pragma once
#include "../core/Def.h"
#include <unordered_map>
#include <functional>
#include "../core/EventArgs.h"

namespace nb{

template<class ArgsT>
class NB_API Event
{
	using CallBack = std::function<void(ArgsT &)>;
	using CallBackContainer = std::unordered_map<int, CallBack>;
public:
	Event() : m_callbacks(nullptr) {}
	~Event() { delete m_callbacks; }

	int addHandler(CallBack callback)
	{
		if (!m_callbacks) m_callbacks = new CallBackContainer();

		static int i = 0;
		m_callbacks->insert({ i++, callback });
		return i - 1;
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

	void invoke(ArgsT &args)
	{
		invoke(const_cast<const ArgsT &>(args));
	}
	void invoke(const ArgsT &args)
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
		remove(callback);
	}

private:
	CallBackContainer *m_callbacks;
};

}