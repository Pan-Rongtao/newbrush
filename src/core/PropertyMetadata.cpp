#include "core/PropertyMetadata.h"

using namespace nb;

PropertyMetadata::PropertyMetadata(const Any & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback)
	: m_defaultValue(defaulValue)
	, m_propertyChangedCallback(propertyChangedCallback)
	, m_coerceValueCallback(coerceValueCallback)
{
}

void PropertyMetadata::setDefaultValue(const Any & value) &
{
	m_defaultValue = value;
}

Any PropertyMetadata::defaultValue() const
{
	return m_defaultValue;
}

bool PropertyMetadata::isSealed() const
{
	return false;
}

PropertyChangedCallback PropertyMetadata::propertyChangedCallback()
{
	return m_propertyChangedCallback;
}

CoerceValueCallback PropertyMetadata::coerceValueCallback()
{
	return m_coerceValueCallback;
}
