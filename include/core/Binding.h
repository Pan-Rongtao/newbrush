#pragma once
#include "Property.h"

namespace nb{ namespace core{
	
class Binding
{
public:
	enum class ModeE
	{
		OneTime,
		OneWay,
		OneWayToSource,
		TwoWay
	};

public:
	template<class T>
	void bind(Property_rw<T> target, std::function<T(void)> getter);

};


}}