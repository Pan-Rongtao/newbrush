#pragma once
#include "newbrush/core/Event.h"
#include "newbrush/core/DependencyProperty.h"
#include "newbrush/core/EffectiveValueEntry.h"
#include "Poco/Dynamic/Var.h"

namespace nb {

class NB_API DependencyObject : public Object
{
public:
	//设置属性值
	//异常：std::logic_error
	void set(const DependencyProperty &dp, const Var &value);

	//获取属性值
	Var get(const DependencyProperty &dp) const;
	template<class T>
	T get(const DependencyProperty &dp) const
	{
		return get(dp).extract<T>();
	}

protected:
	void _set(const DependencyProperty & dp, const Var &defaultValue, const Var &setValue);
	virtual void onPropertyChanged(const DependencyPropertyChangedEventArgs &args);

private:
	
	std::map<size_t, EffectiveValueEntry>	m_valueEntrys;
};

}