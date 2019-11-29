#include "core/RoutedEvent.h"

using namespace nb;

RoutedEvent::RoutedEvent()
	: m_hash(0)
	, m_ownerType(typeid(nullptr))
	, m_handleTyp(typeid(nullptr))
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

RoutedEventArgs::RoutedEventArgs(RoutedEvent event)
	: m_event(event)
{
}

void RoutedEventArgs::setHandled(bool handled)
{
	m_handled = handled;
}

bool RoutedEventArgs::handled() const
{
	return m_handled;
}

void RoutedEventArgs::setRoutedEvent(const RoutedEvent & event)
{
	m_event = event;
}

RoutedEvent RoutedEventArgs::routedEvent() const
{
	return m_event;
}