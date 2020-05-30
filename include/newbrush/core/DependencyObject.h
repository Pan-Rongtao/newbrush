#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/EffectiveValueEntry.h"

namespace nb {

class NB_API DependencyObject : public Object
{
	RTTR_ENABLE(Object)
public:
	//设置属性值（允许设置任意依赖属性对象，即使DependencyObject未注册有该依赖属性）
	//异常：std::logic_error
	void setValue(const DependencyProperty &dp, const variant &value);
	template<class T>
	void setValue(const DependencyProperty &dp, const T &value)
	{
		var v = value;
		setValue(dp, v);
	}

	//获取属性值
	variant getValue(const DependencyProperty &dp) const;
	template<class T>
	T getValue(const DependencyProperty &dp) const
	{
		if(dp.propertyType() != rttr::type::get<T>())
		{
			nbThrowException(std::logic_error, "should use get<%s> instead of get<%s> for [%s]", dp.propertyType().get_name().data(), typeid(T).name(), dp.name().data()); 
		}
		return getValue(dp).get_value<T>();
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	void _set(const DependencyProperty & dp, const var &defaultValue, const var &setValue);
	void invokePropertyCallback(const DependencyPropertyChangedEventArgs & args);

	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}