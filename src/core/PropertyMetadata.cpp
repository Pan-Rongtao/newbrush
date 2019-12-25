#include "core/PropertyMetadata.h"

using namespace nb;

PropertyMetadata::PropertyMetadata()
{
}

PropertyMetadata::PropertyMetadata(const Any & defaulValue)
{
}

PropertyMetadata::PropertyMetadata(PropertyChangedCallback propertyChangedCallback)
{
}

PropertyMetadata::PropertyMetadata(const Any & defaulValue, PropertyChangedCallback propertyChangedCallback)
{
}

PropertyMetadata::PropertyMetadata(const Any & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback)
	: m_defaultValue(defaulValue)
	, m_propertyChangedCallback(propertyChangedCallback)
	, m_coerceValueCallback(coerceValueCallback)
	, m_defaultValueWasSet(false)
{
}

void PropertyMetadata::setDefaultValue(const Any & value)
{
	m_defaultValue = value;
	m_defaultValueWasSet = true;
}

Any PropertyMetadata::defaultValue() const
{
	return m_defaultValue;
}

bool PropertyMetadata::isSealed() const
{
	return false;
}

PropertyMetadata::PropertyChangedCallback PropertyMetadata::propertyChangedCallback()
{
	return m_propertyChangedCallback;
}

PropertyMetadata::CoerceValueCallback PropertyMetadata::coerceValueCallback()
{
	return m_coerceValueCallback;
}

bool PropertyMetadata::defaultValueWasSet() const
{
	return false;
}
