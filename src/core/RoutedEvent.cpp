#include "core/RoutedEvent.h"

using namespace nb;

RoutedEvent::RoutedEvent()
	: m_hash(0)
	, m_routingStrategy(RoutingStrategyE::bubble)
	, m_ownerType(typeid(nullptr))
	, m_argsType(typeid(nullptr))
{
}

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

RoutedEventArgs::RoutedEventArgs()
	: RoutedEventArgs(RoutedEvent())
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent)
	: RoutedEventArgs(routedEvent, Object())
{
}

RoutedEventArgs::RoutedEventArgs(const RoutedEvent &routedEvent, const Object &source)
	: Handled(false)
	, Event(routedEvent)
	, Source(source)
{ 
}
