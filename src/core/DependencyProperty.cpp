#include "core/DependencyProperty.h"
#include "core/PropertyMetadata.h"

using namespace nb;

std::map<std::size_t, DependencyProperty> DependencyProperty::g_dependencyProperties;
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

DependencyProperty::DependencyProperty(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
	: m_name(name)
	, m_propertyType(propertyType)
	, m_ownerType(ownerType)
	, m_metadata(metadata)
	, m_validateValueCallback(validateValueCallback)
	, m_hash(0)
{
}

DependencyProperty DependencyProperty::registerCommon(const std::string & name, std::type_index propertyType, std::type_index ownerType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
{
	if(propertyType != metadata->defaultValue().type())

	std::hash<std::string> _shash;
	auto hash = typeid(ownerType).hash_code() ^ _shash(name);
	if (g_dependencyProperties.find(hash) != g_dependencyProperties.end())
	{
		nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), ownerType.name());
	}
	if (!metadata)
	{
		metadata = autoGeneratePropertyMetadata(propertyType, validateValueCallback, name, ownerType);
	}
	else
	{
		if(!metadata->defaultValueWasSet())
		{
			metadata = autoGeneratePropertyMetadata(propertyType, validateValueCallback, name, ownerType);
		}
	}
	DependencyProperty dp(name, propertyType, ownerType, metadata, validateValueCallback);
	dp.m_hash = hash;
	g_dependencyProperties.insert({hash, dp});
	return dp;
}

std::shared_ptr<PropertyMetadata> DependencyProperty::autoGeneratePropertyMetadata(std::type_index propertyType, ValidateValueCallback validateValueCallback, const std::string & name, std::type_index ownerType)
{
	auto ret = std::make_shared<PropertyMetadata>();
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
	return std::shared_ptr<PropertyMetadata>();
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