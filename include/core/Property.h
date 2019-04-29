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
	Property_rw() : m_v(T()) {}
	Property_rw(T v) : m_v(v) {}

	//设置通知函数
	void notify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	//绑定，可以是任意返回T&的函数，表达式；绑定后，属性返回值将受绑定函数影响，如果传入nullptr表示取消绑定
	void bind(std::function<const T&(void)> binder)
	{
		m_binder = std::move(binder);
	}

	void operator =(const Property_rw<T> &other)
	{
		operator=(other.m_binder ? other.m_binder() : other.m_v);
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

	bool operator == (const T &v) const { return v == operator()(); }
	bool operator != (const T &v) const { return !operator==(v); }

	operator const T&() const
	{
		return m_binder ? m_binder() : m_v;
	}

	const T & operator()() const
	{
		return m_binder ? m_binder() : m_v;
	}

private:
	std::function<void(const T &, const T &)>	m_notify;
	std::function<const T&(void)>				m_binder;
	T											m_v;
};

template<typename T>
class Property_r
{
public:
	Property_r() : m_v(T()) {}
	explicit Property_r(T v) : m_v(v) {}
	void operator = (const T &v) = delete;
	void operator = (const Property_r<T> &v) = delete;

	//绑定，可以是任意返回T&的函数，表达式；绑定后，属性返回值将受绑定函数影响，如果传入nullptr表示取消绑定
	void bind(std::function<const T&(void)> binder)
	{
		m_binder = binder;
	}

	operator const T&() const
	{
		return m_binder ? m_binder() : m_v;
	}

private:
	std::function<const T &(void)>	m_binder;
	T							m_v;
};


template<typename T>
class Property_w
{
public:
	Property_w() : m_v(T()) {}
	Property_w(const T &v) : m_v(v) {}

	void notify(std::function<void(const T &, const T &)> notify)
	{
		m_notify = std::move(notify);
	}

	void operator =(const Property_w<T> &other)
	{
		operator=(other.m_v);
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