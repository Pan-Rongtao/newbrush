#pragma once
#include <unordered_map>
#include <functional>

namespace nb{

template<class ArgsT>
class Event
{
public:
	int addHandler(std::function<void(const ArgsT &args)> callback)
	{
		static int i = 0;
		m_callbacks.insert({ i++, callback });
		return i - 1;
	}

	void removeHandler(int handler)
	{
		auto iter = m_callbacks.find(handler);
		if(iter != m_callbacks.end())
			m_callbacks.erase(handler);
	}

	void clear()
	{
		m_callbacks.clear();
	}

	void dispatch(const ArgsT &args)
	{
		for (const auto &callback : m_callbacks)
			if (callback.second)
				callback.second(args);
	}

	void operator += (std::function<void(const ArgsT &args)> callback)
	{
		addHandler(callback);
	}

	void operator -=(int handler)
	{
		remove(callback);
	}

private:
	std::unordered_map<int, std::function<void(const ArgsT &)>>	m_callbacks;
};

}