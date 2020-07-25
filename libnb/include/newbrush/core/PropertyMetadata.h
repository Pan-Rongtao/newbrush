#pragma once
#include "newbrush/core/DependencyPropertyChangedEventArgs.h"

namespace nb{
	
class DependencyObject;
using PropertyChangedCallback = std::function<void(DependencyObject *, const DependencyPropertyChangedEventArgs &)>;
using CoerceValueCallback = std::function<var(DependencyObject *, var)>;
using ValidateValueCallback = std::function<bool(const var &value)>;

class NB_API PropertyMetadata
{
public:
	//构建一个PropertyMetadata
	//defaulValue：默认值
	//propertyChangedCallback：属性已改变回调
	//coerceValueCallback：属性值矫正回调
	PropertyMetadata(const var &defaultValue, PropertyChangedCallback propertyChangedCallback = nullptr, CoerceValueCallback coerceValueCallback = nullptr);

	void setDefaultValue(const var &value) &;
	const var &defaultValue() const;

	bool isSealed() const;

	PropertyChangedCallback propertyChangedCallback();
	CoerceValueCallback coerceValueCallback();

private:
	var						m_defaultValue;
	PropertyChangedCallback	m_propertyChangedCallback;
	CoerceValueCallback		m_coerceValueCallback;
};

using PropertyMetadataPtr = std::shared_ptr<PropertyMetadata>;
}