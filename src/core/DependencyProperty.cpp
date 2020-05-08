#include "newbrush/core/DependencyProperty.h"

using namespace nb;

static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
std::map<std::shared_ptr<DependencyObject>, std::map<std::string, Var>>	DependencyProperty::m_attProperties;

PropertyMetadata::PropertyMetadata(const Var & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback)
	: m_defaultValue(defaulValue)
	, m_propertyChangedCallback(propertyChangedCallback)
	, m_coerceValueCallback(coerceValueCallback)
{
}

void PropertyMetadata::setDefaultValue(const Var & value) &
{
	m_defaultValue = value;
}

Var PropertyMetadata::defaultValue() const
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

void DependencyProperty::registerAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name, const Var & property_v)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		std::map<std::string, Var> mapNameV;
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

Var DependencyProperty::findAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		return Var();
	}
	else
	{
		auto iterInner = iter->second.find(property_name);
		if (iterInner == iter->second.end())
			return Var();
		else
			return iterInner->second;
	}
}

struct UnsetValueInternal
{
	std::string	_name;
};
static UnsetValueInternal staticUnsetValue{ "DependencyProperty.UnsetValue" };
Var DependencyProperty::unsetValue()
{
	return staticUnsetValue;
}

const DependencyProperty &DependencyProperty::invalidProperty()
{
	static DependencyProperty dp("", typeid(void), typeid(void), nullptr, nullptr, 0);
	return dp;
}

const DependencyProperty &DependencyProperty::find(size_t globalIndex)
{
	auto iter = g_dependencyProperties.find(globalIndex);
	return iter == g_dependencyProperties.end() ? invalidProperty() : iter->second;
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

bool DependencyProperty::isInvalid() const
{
	return *this == invalidProperty();
}

std::map<std::size_t, DependencyProperty> &DependencyProperty::dependencyProperties()
{
	return g_dependencyProperties;
}
