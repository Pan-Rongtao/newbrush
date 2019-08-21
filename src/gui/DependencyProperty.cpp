#include "gui/DependencyProperty.h"

using namespace nb;
using namespace nb::gui;

std::map<std::shared_ptr<UIElement>, std::map<std::string, Any>>	DependencyProperty::m_attProperties;

void DependencyProperty::registerAttached(std::shared_ptr<UIElement> element, const std::string & property_name, const Any & property_v)
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

Any DependencyProperty::findAttached(std::shared_ptr<UIElement> element, const std::string & property_name)
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

std::string DependencyProperty::name() const
{
	return m_name;
}

size_t nb::gui::DependencyProperty::hash() const
{
	return m_hash;
}

bool DependencyProperty::isSealed() const
{
	return m_isSealed;
}

Any DependencyProperty::defaultValue() const
{
	return m_defaultV;
}

bool DependencyProperty::operator == (const DependencyProperty &other) const
{
	return m_hash == other.m_hash;
}