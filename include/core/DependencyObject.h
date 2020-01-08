#pragma once
#include "../core/Event.h"
#include "../core/DependencyProperty.h"
#include "../core/EffectiveValueEntry.h"
#include "Poco/Dynamic/Var.h"

namespace nb {

class NB_API DependencyObject
{
public:
	//设置属性值
	//如果未存储有该属性的值，则当value与defaultValue不相等时，插入新存储
	//反之已经存储该属性的值，当value与defaultValue相等，移除该存储，否则更新该值
	void set(const DependencyProperty &dp, const Var &value);

	//获取属性值
	//如果未存储有该属性的值，则返回defaultValue
	//反之，返回该存储值
	Var get(const DependencyProperty &dp) const;
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		return get(dp).extract<T>();
	}

protected:
	void _set(const DependencyProperty & dp, const Var &defaultValue, const Var &setValue, bool isValueChanged);
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}