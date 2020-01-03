#include "core/DependencyProperty.h"

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

std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Any>>	DependencyProperty::m_attProperties;

void DependencyProperty::registerAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name, const Any & property_v)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		std::map<std::string, Any> mapNameV;
		mapNameV[property_name] = property_v;
		m_attProperties[element] = mapNameV;
	}
	else
	{
		auto &mapNameV = iter->second;
		//auto iterNameV = mapNameV.find(property_name);
		mapNameV[property_name] = property_v;
	}
}

Any DependencyProperty::findAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		return Any();
	}
	else
	{
		auto iterInner = iter->second.find(property_name);
		if (iterInner == iter->second.end())
			return Any();
		else
			return iterInner->second;
	}
}

struct UnsetValueInternal
{
	std::string	_name;
};
static UnsetValueInternal staticUnsetValue{ "DependencyProperty.UnsetValue" };
Any DependencyProperty::unsetValue()
{
	return staticUnsetValue;
}

DependencyProperty::DependencyProperty(const std::string & name, std::type_index ownerType, std::type_index propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback, size_t hash)
	: m_name(name)
	, m_ownerType(ownerType)
	, m_propertyType(propertyType)
	, m_metadata(metadata)
	, m_validateValueCallback(validateValueCallback)
	, m_hash(hash)
{
}

const std::string &DependencyProperty::name() const
{
	return m_name;
}

std::type_index DependencyProperty::ownerType() const
{
	return m_ownerType;
}

std::type_index DependencyProperty::propertyType() const
{
	return m_propertyType;
}

std::shared_ptr<PropertyMetadata> DependencyProperty::defaultMetadata() const
{
	return m_metadata;
}

bool DependencyProperty::readOnly() const
{
	return false;
}

size_t DependencyProperty::globalIndex() const
{
	return m_hash;
}

ValidateValueCallback DependencyProperty::validateValueCallback() const
{
	return m_validateValueCallback;
}

bool DependencyProperty::operator == (const DependencyProperty &other) const
{
	return !operator!=(other);
}

bool DependencyProperty::operator != (const DependencyProperty &other) const
{
	return m_hash != other.m_hash;
}