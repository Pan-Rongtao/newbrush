#include "newbrush/core/DependencyProperty.h"

using namespace nb;

std::map<std::string, std::shared_ptr<PropertyCategory>> PropertyCategory::s_propertyCategorys;

Range::Range(var lowerBound, var upperBound, var step)
	: m_lowerBound(lowerBound)
	, m_upperBound(upperBound)
	, m_step(step)
{
}

var Range::lowerBound() const
{
	return m_lowerBound;
}

var Range::upperBound() const
{
	return m_upperBound;
}

var Range::step() const
{
	return m_step;
}

const std::string & PropertyCategory::name() const
{
	return m_name;
}

int PropertyCategory::order() const
{
	return m_order;
}

std::shared_ptr<PropertyCategory> PropertyCategory::get(const std::string & name, int order)
{
	auto newPC = std::make_shared<PropertyCategory>();
	newPC->m_name = name;
	newPC->m_order = order;
	auto ret = s_propertyCategorys.insert({ name, newPC });
	return ret.first->second;
}

std::shared_ptr<PropertyCategory> PropertyCategory::Brush()
{
	return PropertyCategory::get("画笔", 0);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Appearance()
{
	return PropertyCategory::get("外观", 1);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Public()
{
	return PropertyCategory::get("公共", 2);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Automation()
{
	return PropertyCategory::get("自动化", 3);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Layout()
{
	return PropertyCategory::get("布局", 4);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Text()
{
	return PropertyCategory::get("文本", 5);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Transform()
{
	return PropertyCategory::get("转换", 6);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Misc()
{
	return PropertyCategory::get("杂项", 7);
}

std::shared_ptr<PropertyCategory> PropertyCategory::Custom()
{
	return PropertyCategory::get("自定义", 8);
}

static std::map<std::size_t, DependencyProperty> g_dependencyProperties;
std::map<std::shared_ptr<DependencyObject>, std::map<std::string, var>>	DependencyProperty::m_attProperties;

PropertyMetadata::PropertyMetadata(const var & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback, 
	PropertyCategoryPtr category, const std::string &description, int order, std::shared_ptr<Range> range)
	: m_defaultValue(defaulValue)
	, m_propertyChangedCallback(propertyChangedCallback)
	, m_coerceValueCallback(coerceValueCallback)
	, m_category(category)
	, m_description(description)
	, m_order(order)
	, m_range(range)
{
}

void PropertyMetadata::setDefaultValue(const var & value) &
{
	m_defaultValue = value;
}

var PropertyMetadata::defaultValue() const
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

PropertyCategoryPtr PropertyMetadata::category() const
{
	return m_category;
}

const std::string &PropertyMetadata::description() const
{
	return m_description;
}

int PropertyMetadata::order() const
{
	return m_order;
}

std::shared_ptr<Range>PropertyMetadata::range() const
{
	return m_range;
}

void DependencyProperty::registerAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name, const var & property_v)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		std::map<std::string, var> mapNameV;
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

var DependencyProperty::findAttached(std::shared_ptr<DependencyObject> element, const std::string & property_name)
{
	auto iter = m_attProperties.find(element);
	if (iter == m_attProperties.end())
	{
		return var();
	}
	else
	{
		auto iterInner = iter->second.find(property_name);
		if (iterInner == iter->second.end())
			return var();
		else
			return iterInner->second;
	}
}

struct UnsetValueInternal
{
	std::string	_name;
};
static UnsetValueInternal staticUnsetValue{ "DependencyProperty.UnsetValue" };
void DependencyProperty::getTypePropertys(rttr::type ownerType, std::vector<DependencyProperty> &ret)
{
	using namespace rttr;
	auto baseClassesRange = ownerType.get_base_classes();
	if (baseClassesRange.empty())
	{
		auto pros = getTypePropertys(ownerType);
		ret.insert(ret.end(), pros.begin(), pros.end());
	}
	else
	{
		for (type t : baseClassesRange)
		{
			getTypePropertys(t, ret);
		}
	}
}

std::vector<DependencyProperty> DependencyProperty::getTypePropertys(rttr::type t)
{
	std::vector<DependencyProperty> ret;
	for (auto pair : g_dependencyProperties)
	{
		auto const &p = pair.second;
		if (p.ownerType() == t)
		{
			ret.push_back(p);
		}
	}
	return ret;
}

var DependencyProperty::unsetValue()
{
	return staticUnsetValue;
}

const DependencyProperty &DependencyProperty::invalidProperty()
{
	static DependencyProperty dp("", rttr::type::get<void>(), rttr::type::get<void>(), nullptr, nullptr, 0);
	return dp;
}

const DependencyProperty &DependencyProperty::find(size_t globalIndex)
{
	auto iter = g_dependencyProperties.find(globalIndex);
	return iter == g_dependencyProperties.end() ? invalidProperty() : iter->second;
}

DependencyProperty::DependencyProperty(const std::string & name, rttr::type ownerType, rttr::type propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback, size_t hash)
	: m_name(name)
	, m_ownerType(ownerType)
	, m_propertyType(propertyType)
	, m_metadata(metadata)
	, m_validateValueCallback(validateValueCallback)
	, m_hash(hash)
{
}

const DependencyProperty &DependencyProperty::registerCommon(const std::string &name, rttr::type ownerType, rttr::type propertyType, std::shared_ptr<PropertyMetadata> metadata, ValidateValueCallback validateValueCallback)
{
	std::hash<std::string> _shash;
	auto _hash = ownerType.get_id() ^ _shash(name);
	DependencyProperty dp(name, ownerType, propertyType, metadata, validateValueCallback, _hash);
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
