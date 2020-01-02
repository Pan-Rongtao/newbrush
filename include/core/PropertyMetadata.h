#pragma once
#include <functional>
#include "../core/Any.h"
#include "../core/EventArgs.h"

namespace nb {

class DependencyObject;

class PropertyMetadata
{
	using PropertyChangedCallback = std::function<void(DependencyObject *, DependencyPropertyChangedEventArgs)>;
	using CoerceValueCallback = std::function<Any(DependencyObject *, Any)>;
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata();
	PropertyMetadata(const Any &defaulValue);
	PropertyMetadata(const PropertyChangedCallback propertyChangedCallback);
	PropertyMetadata(const Any &defaulValue, PropertyChangedCallback propertyChangedCallback);
	PropertyMetadata(const Any &defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback);

	void setDefaultValue(const Any &value);
	Any defaultValue() const;
	bool isSealed() const;
	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();
	bool defaultValueWasSet() const;


private:
	Any						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
	bool m_defaultValueWasSet;
};

}