/*******************************************************
**	Any（任意值）
**
**	Any是一种可以装载任意类型值的类型，并可以在过程中擦除和
**	和赋予其它的类型值。要求是该类型实现了=操作符和复制构造函数
**
**		潘荣涛
**
********************************************************/
#pragma once
#include <exception>
#include <typeinfo>
#include <type_traits>
#include <typeindex>
#include <string>

//refrence from https://www.jianshu.com/p/67c11c15906d
namespace nb 
{
	template <bool B, class T = void>
	struct disable_if_c { typedef T type; };

	template <class T>
	struct disable_if_c<true, T> {};

	template <class Cond, class T = void>
	struct disable_if : public disable_if_c<Cond::value, T> {};

	template<bool, class _Ty1, class _Ty2>
	struct _If { typedef _Ty2 type;/*type is _Ty2 for assumed false*/ };

	template<class _Ty1, class _Ty2>
	struct _If<true, _Ty1, _Ty2> { typedef _Ty1 type;/* type is _Ty1 for assumed true*/ };

	template<class _Ty>
	struct add_reference { typedef typename std::remove_reference<_Ty>::type& type; };

	template<>
	struct add_reference<void> { typedef void type; };

	template<>
	struct add_reference<const void> { typedef const void type; };

	template<>
	struct add_reference<volatile void> { typedef volatile void type; };

	template<>
	struct add_reference<const volatile void> {	typedef const volatile void type; };

	class bad_any_cast : public std::bad_cast
	{
	public:
		bad_any_cast(char const* const _Message) : std::bad_cast() {}
		const char* what() const noexcept override { return "bad any cast"; }
	};
}

namespace nb{
class Any
{
public:
	Any() : content(0) { }

	template<typename T>
	Any(const T& value)
		: content(new holder<typename std::remove_cv<typename std::decay<const T>::type>::type>(value))
	{
	}

	Any(const Any& other)
		: content(other.content ? other.content->clone() : 0)
	{
	}

	//c++11 Move constructor
	Any(Any&& other) noexcept
		: content(other.content)
	{
		other.content = 0;
	}

	// Perfect forwarding of T
	template<typename T>
	Any(T&& value
		, typename nb::disable_if< typename std::is_same<Any&, T> >::type* = 0 // disable if value has type `any&`
		, typename nb::disable_if< typename std::is_const<T> >::type* = 0) // disable if value has type `const T&&`
		: content(new holder< typename std::decay<T>::type >(static_cast<T&&>(value)))
	{
	}

	~Any()
	{
		delete content;
	}

public:
	Any& swap(Any& rhs)
	{
		std::swap(content, rhs.content);
		return *this;
	}

	Any& operator=(const Any& rhs)
	{
		Any(rhs).swap(*this);
		return *this;
	}

	Any& operator=(Any&& rhs) noexcept
	{
		rhs.swap(*this);
		Any().swap(rhs);
		return *this;
	}

	template<class T>
	Any& operator=(T&& rhs)
	{
		Any(static_cast<T&&>(rhs)).swap(*this);
		return *this;
	}

public: // queries
	bool empty()
	{
		return !content;
	}

	void clear()
	{
		Any().swap(*this);
	}

	const std::type_info& type() const
	{
		return content ? content->type() : typeid(void);
	}


	template<class T> 
	bool is() const
	{
		return type() == typeid(T);
	}

	bool isInteger() const
	{
		return is<bool>() || is<int>() || is<unsigned int>() || is<short>() || is<unsigned short>() ||
			is<long>() || is<unsigned long>() || is<long long>() || is<unsigned long long>() ||
			is<char>() || is<signed char>() || is<unsigned char>() || is<wchar_t>() || is<char16_t>() || is<char32_t>();
	}

	bool isFloating() const
	{
		return is<float>() || is<double>() || is<long double>();
	}

	bool isNumeric() const
	{
		return isFloating() || isInteger();
	}

private:
	class placeholder
	{
	public:
		virtual ~placeholder() {}
		virtual const std::type_info& type() const = 0;
		virtual placeholder* clone() const = 0;
	};

	template<typename T>
	class holder : public placeholder
	{
	public:
		holder(const T& value) :held(value) {}
		holder(T&& value) : held(static_cast<T&&>(value)) {}

		virtual const std::type_info& type() const { return typeid(T); }
		virtual placeholder* clone() const { return new holder(held); }

	public:
		T held;
	};

private:
	placeholder *content;
	template<typename T> friend T* any_cast(Any*);
	template<typename T> friend T* unsafe_any_cast(Any*);
};

inline void swap(Any& lhs, Any& rhs)
{
	lhs.swap(rhs);
}

template<typename T>
T* any_cast(Any* operand)
{
	return operand && operand->type() == typeid(T) ? &static_cast<Any::holder< typename std::remove_cv<T>::type>*>(operand->content)->held : 0;
}

template<typename T>
inline const T* any_cast(const Any* operand)
{
	return any_cast<T>(const_cast<Any*>(operand));
}

template<typename T>
T any_cast(Any& operand)
{
	typedef typename std::remove_reference<T>::type nonref;
	nonref* result = any_cast<nonref>(&operand);
	if (!result)
	{
		//std::string szReason = std::string("bad any_cast : can't convert ") + operand.type().name() + " to " + typeid(T).name();
		throw std::bad_cast();// nb::bad_any_cast(szReason);
	}

	// Attempt to avoid construction of a temporary object in cases when
	// `ValueType` is not a reference. Example:
	// `static_cast<std::string>(*result);`
	// which is equal to `std::string(*result);`
	typedef typename nb::_If<std::is_reference<T>::value, T, typename nb::add_reference<T>::type>::type ref_type;
	return static_cast<ref_type>(*result);
}

template<typename T>
inline T any_cast(const Any& operand)
{
	typedef typename std::remove_reference<T>::type nonref;
	return any_cast<const nonref&>(const_cast<Any&>(operand));
}

template<typename T>
inline T any_cast(Any&& operand)
{
	static_assert(std::is_rvalue_reference<T&&>::value /*true if T is rvalue or just a value*/ || std::is_const< typename std::remove_reference<T>::type >::value,
		"any_cast shall not be used for getting nonconst references to temporary objects"
		);

	return any_cast<T>(operand);
}

using var = Any;
}