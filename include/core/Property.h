/*******************************************************
**	Property_rw, Property_r, Property_w
**
**	属性类
**		属性给外部提供方便的访问权限控制的能力。使用一个
**	属性就像使用一个变量一样方便。不同的属性提供不同的访问
**	能力：Property_rw供读写，Property_r供只读，对应的读写能力为
**	setter和getter，std::function，可以返回一个成语变量，另一个属性，或
**	一个可执行函数体或lambda表达式。
**	
**
********************************************************/
#pragma once
#include <functional>
#include "../core/Def.h"

namespace nb{

template<class T>
class Property_rw
{
public:
	Property_rw(std::function<void(T v)> setter, std::function<T&()> getter)  : m_setter(std::move(setter)) , m_getter(std::move(getter)) { }
	void operator =(const T &v) &				{ try { m_setter(v); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null setter"); } }
	bool operator == (const T &v) const			{ return !operator!=(v);  }
	bool operator != (const T &v) const			{ return v != operator()(); }
	const T&operator()() const					{ return const_cast<Property_rw *>(this)->operator()(); }
	T &operator()()								{ try { return m_getter(); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null getter"); } }
	operator T() const							{ return operator()(); }
	const std::type_info &type() const			{ return typeid(T); }
	
private:
	std::function<void(T)>	m_setter;
	std::function<T&()>		m_getter;
};

template<typename T>
class Property_r
{
public:
	explicit Property_r(std::function<T()> getter) : m_getter(std::move(getter)) { }
	bool operator == (const T &v) const			{ return !operator!=(v); }
	bool operator != (const T &v) const			{ return v != operator()();  }
	T operator()() const						{ try { return m_getter(); } catch (std::bad_function_call &e) { (void)e; nbThrowException(std::runtime_error, "null getter"); } }
	void operator = (const Property_r<T> &v)	= delete;
	void operator = (const T &v)				= delete;
	operator T() const							{ return operator()(); }
	const std::type_info &type() const			{ return typeid(T); }

private:
	std::function<T()>		m_getter;
};

}