#include "newbrush/core/DependencyProperty.h"

using namespace nb;

static std::map<std::size_t, DependencyPropertyPtr> g_dependencyProperties;

PropertyMetadata::PropertyMetadata(const var & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback)
	: m_defaultValue(defaulValue)
	, m_propertyChangedCallback(propertyChangedCallback)
	, m_coerceValueCallback(coerceValueCallback)
{
}

void PropertyMetadata::setDefaultValue(const var & value) &
{
	m_defaultValue = value;
}

const var &PropertyMetadata::defaultValue() const
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

DependencyPropertyPtr DependencyProperty::find(size_t globalIndex)
{
	auto iter = g_dependencyProperties.find(globalIndex);
	return iter == g_dependencyProperties.end() ? nullptr : iter->second;
}

DependencyProperty::DependencyProperty(const std::string & name, rttr::type ownerType, rttr::type propertyType, PropertyMetadataPtr metadata, ValidateValueCallback validateValueCallback, size_t hash)
	: m_name(name)
	, m_ownerType(ownerType)
	, m_propertyType(propertyType)
	, m_metadata(metadata)
	, m_validateValueCallback(validateValueCallback)
	, m_hash(hash)
{
}

DependencyPropertyPtr DependencyProperty::registerCommon(const std::string &name, rttr::type ownerType, rttr::type propertyType, PropertyMetadataPtr metadata, ValidateValueCallback validateValueCallback)
{
	std::hash<std::string> _shash;
	auto _hash = _shash(ownerType.get_name().data()) ^ _shash(name);
	DependencyPropertyPtr dp(new DependencyProperty(name, ownerType, propertyType, metadata, validateValueCallback, _hash));
	auto p = dependencyProperties().insert({ _hash, dp });
	if (!p.second)
	{
		nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), ownerType.get_name().data());
	}

	return p.first->second;
}

const std::string &DependencyProperty::name() const
{
	return m_name;
}

rttr::type DependencyProperty::ownerType() const
{
	return m_ownerType;
}

rttr::type DependencyProperty::propertyType() const
{
	return m_propertyType;
}

PropertyMetadataPtr DependencyProperty::defaultMetadata() const
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

std::map<std::size_t, DependencyPropertyPtr> &DependencyProperty::dependencyProperties()
{
	return g_dependencyProperties;
}
