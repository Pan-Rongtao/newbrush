#include "AttachedProperty.h"

using namespace nb::core;
using namespace nb::gui;

std::map<std::shared_ptr<UIElement>, std::map<std::string, Any>>	AttachedProperties::m_attProperties;
void AttachedProperties::registerAttached(std::shared_ptr<UIElement> element, const std::string & property_name, const Any & property_v)
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

Any AttachedProperties::findAttached(std::shared_ptr<UIElement> element, const std::string & property_name)
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
