#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/EffectiveValueEntry.h"

namespace nb {

class NB_API DependencyObject : public Object
{
	RTTR_ENABLE(Object)
public:
	//设置属性值（允许设置任意依赖属性对象，即使DependencyObject未注册有该依赖属性）
	//异常：std::logic_error
	void setValue(DependencyPropertyPtr dp, const var &value);
	template<class T>
	void setValue(DependencyPropertyPtr dp, const T &value)
	{
		setValue(dp, var(value));
	}

	//获取属性值
	var getValue(DependencyPropertyPtr dp) const;
	template<class T>
	T getValue(DependencyPropertyPtr dp) const
	{
		_checkType(dp, rttr::type::get<T>());
		return getValue(dp).get_value<T>();
	}

protected:
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	void _set(DependencyPropertyPtr dp, const var &defaultValue, const var &setValue);
	void _checkType(DependencyPropertyPtr dp, rttr::type getType) const;
	void invokePropertyCallback(const DependencyPropertyChangedEventArgs & args);

	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}