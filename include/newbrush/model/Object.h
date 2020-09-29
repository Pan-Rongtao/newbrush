#pragma once
#include "newbrush/model/Def.h"

namespace nb {

class NB_API Object
{
	RTTR_ENABLE()
public:
	virtual ~Object() = default;

	//设置属性值（允许设置任意依赖属性对象，即使DependencyObject未注册有该依赖属性）
	//异常：std::logic_error
	void setValue(const property &prop, const var &value);

	template<class T>
	void setValue(const property &prop, const T &value)
	{
		setValue(prop, var(value));
	}

	//通过属性名设置属性
	void setValue(const std::string &propName, const var &value);
	
	template<class T>
	void setValue(const std::string &propName, const T &value)
	{
		setValue(propName, var(value));
	}
	
	//获取属性值
	var getValue(const property &prop) const;
	template<class T>
	const T &getValue(const property &prop) const
	{
		if (prop.get_type() != type::get<T>())
		{
			nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", prop.get_type().get_name().data(), typeid(T).name(), prop.get_name().data());
		}
		return getValue(prop).get_value<T>();
	}

protected:
	Object() = default;

};

using ObjectPtr = std::shared_ptr<Object>;

NB_API void setValue(const instance &ins, const property &prop, const var &value);
NB_API void setValue(const instance &ins, const std::string &propName, const var &value);

}