#pragma once
#include <functional>
#include "../core/Def.h"

#define property_setter(variableType) [&](variableType value)
#define property_getter(variableType) [&]()->variableType

namespace nb{namespace core{

template<typename T>
class Property_rw
{
public:
	Property_rw() : m_notify(nullptr), m_v(T()) {}
	Property_rw(T v) : m_notify(nullptr), m_v(v) {}

	void setNotify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	void operator =(const Property_rw &other)
	{
		if (m_v != other.m_v)
		{
			T old = m_v;
			m_v = other.m_v;
			if (m_notify)
				m_notify(old, m_v);
		}
	}

	void operator =(const T &v)
	{
		if (m_v != v)
		{
			T old = m_v;
			m_v = v;
			if (m_notify)
				m_notify(old, m_v);
		}
	}

	operator const T&() const
	{
		return m_v;
	}

private:
	std::function<void(const T &, const T &)>	m_notify;
	T											m_v;
};

template<typename T>
class Property_r
{
public:
	Property_r() : m_getter(nullptr), m_v(T()) {}
	explicit Property_r(T v) :  m_getter(nullptr), m_v(v) {}
	Property_r(std::function<T(void)> getter) : m_getter(getter) {}

	void setGetter(std::function<T(void)> getter)
	{
		m_getter = getter;
	}

	operator T() const
	{
		return m_getter ? m_getter() : m_v;
	}

private:
	std::function<T(void)>		m_getter;
	T							m_v;
};


template<typename T>
class Property_w
{
public:
	Property_w() : m_v(T()) {}
	Property_w(const T &v) : m_v(v) {}

	void setNotify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	void operator =(const Property_w &other)
	{
		if (m_v != other.m_v)
		{
			T old = m_v;
			m_v = other.m_v();
			if (m_notify)
				m_notify(old, m_v);
		}
	}

	void operator =(const T &v)
	{
		if (m_v != v)
		{
			T old = m_v;
			m_v = v;
			if (m_notify)
				m_notify(old, m_v);
		}
	}

private:
	std::function<void(const T &, const T &)>	m_notify;
	T											m_v;
};

}}