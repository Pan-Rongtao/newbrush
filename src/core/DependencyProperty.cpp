#include "newbrush/core/DependencyProperty.h"

using namespace nb;

std::map<std::string, PropertyCategoryPtr> PropertyCategory::s_propertyCategorys;

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

const std::map<std::string, PropertyCategoryPtr>& PropertyCategory::getAll()
{
	return s_propertyCategorys;
}

PropertyCategoryPtr PropertyCategory::get(const std::string & name, int order)
{
	auto newPC = std::make_shared<PropertyCategory>();
	newPC->m_name = name;
	newPC->m_order = order;
	auto ret = s_propertyCategorys.insert({ name, newPC });
	return ret.first->second;
}

PropertyCategoryPtr PropertyCategory::Brush()
{
	return PropertyCategory::get("画笔", 0);
}

PropertyCategoryPtr PropertyCategory::Appearance()
{
	return PropertyCategory::get("外观", 1);
}

PropertyCategoryPtr PropertyCategory::Public()
{
	return PropertyCategory::get("公共", 2);
}

PropertyCategoryPtr PropertyCategory::Automation()
{
	return PropertyCategory::get("自动化", 3);
}

PropertyCategoryPtr PropertyCategory::Layout()
{
	return PropertyCategory::get("布局", 4);
}

PropertyCategoryPtr PropertyCategory::Text()
{
	return PropertyCategory::get("文本", 5);
}

PropertyCategoryPtr PropertyCategory::Transform()
{
	return PropertyCategory::get("转换", 6);
}

PropertyCategoryPtr PropertyCategory::Misc()
{
	return PropertyCategory::get("杂项", 7);
}

PropertyCategoryPtr PropertyCategory::Custom()
{
	return PropertyCategory::get("自定义", 8);
}

static std::map<std::size_t, DependencyPropertyPtr> g_dependencyProperties;

PropertyMetadata::PropertyMetadata(const var & defaulValue, PropertyChangedCallback propertyChangedCallback, CoerceValueCallback coerceValueCallback, 
	PropertyCategoryPtr category, const std::string &description, int order, RangePtr range)
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

RangePtr PropertyMetadata::range() const
{
	return m_range;
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
