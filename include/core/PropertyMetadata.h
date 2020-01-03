#pragma once
#include <functional>
#include "../core/Any.h"
#include "../core/EventArgs.h"

namespace nb {

class PropertyMetadata
{
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata(const Any &defaulValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr);

	void setDefaultValue(const Any &value) &;
	Any defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	
private:
	Any						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
};

}