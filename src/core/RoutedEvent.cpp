#include "newbrush/core/RoutedEvent.h"

using namespace nb;

std::string RoutedEvent::name() const
{
	return m_name;
}

std::size_t RoutedEvent::hash() const
{
	return m_hash;
}

std::type_index RoutedEvent::ownerType() const
{
	return m_ownerType;
}

std::type_index RoutedEvent::argsType() const
{
	return m_argsType;
}

RoutingStrategyE RoutedEvent::routingStrategy() const
{
	return m_routingStrategy;
}

bool RoutedEvent::operator==(const RoutedEvent & other) const
{
	return !(operator!=(other));
}

bool RoutedEvent::operator!=(const RoutedEvent & other) const
{
	return m_hash != other.m_hash;
}

RoutedEvent RoutedEvent::invalid()
{
	return RoutedEvent("", typeid(void), typeid(void), RoutingStrategyE::bubble, 0);
}

RoutedEvent::RoutedEvent(const std::string & name, std::type_index ownerType, std::type_index eventArgsType, RoutingStrategyE routingStrategy, std::size_t hash)
	: m_name(name)
	, m_ownerType(ownerType)
	, m_argsType(eventArgsType)
	, m_routingStrategy(routingStrategy)
	, m_hash(hash)
{
}
