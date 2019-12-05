#pragma once
#include <string>
#include <typeindex>
#include <functional>
#include <map>
#include "../core/Object.h"

namespace nb{

enum class RoutingStrategyE
{
	tunnel,		//隧道方式，事件由元素树的根到源元素传递
	bubble,		//冒泡方式，与tunnel相反
	direct,		//直达，
};

class NB_API RoutedEvent
{
public:
	RoutedEvent();

	std::string name() const;
	std::size_t hash() const;
	std::type_index ownerType() const;
	std::type_index argsType() const;
	RoutingStrategyE routingStrategy() const;

	bool operator ==(const RoutedEvent &other) const;
	bool operator !=(const RoutedEvent &other) const;

private:
	std::size_t			m_hash{0};
	std::string			m_name;
	RoutingStrategyE	m_routingStrategy;
	std::type_index		m_ownerType;
	std::type_index		m_argsType;
	friend class RoutedEventManager;
};

class NB_API RoutedEventArgs
{
public:
	RoutedEventArgs();
	RoutedEventArgs(const RoutedEvent &routedEvent);
	RoutedEventArgs(const RoutedEvent &routedEvent, const Object &source);
	virtual ~RoutedEventArgs() = default;

	bool		Handled;
	RoutedEvent	Event;
	Object		OriginalSource;
	Object		Source;
};

template<class ArgsT>
class NB_API RoutedEventHandler
{
public:
	using CB = std::function<void(const ArgsT &)>;
	RoutedEventHandler(CB callback) : m_callback(std::make_shared<CB>(std::move(callback))) { }

	void invoke(const ArgsT &args)									{ (*m_callback)(args); }
	bool operator ==(const RoutedEventHandler<ArgsT> &other) const	{ return !(operator!=(other)); }
	bool operator !=(const RoutedEventHandler<ArgsT> &other) const	{ return m_callback != other.m_callback; }

private:
	std::shared_ptr<CB>	m_callback;
};


class NB_API RoutedEventManager
{
public:
	template<class OwnerType, class EventArgsType>
	static const RoutedEvent registerRoutedEvent(const std::string &name, RoutingStrategyE routingStrategy = RoutingStrategyE::bubble)
	{
		static std::map<std::size_t, RoutedEvent>	m_routedEvents;
		//	static_assert(std::is_base_of<Object, ownerType>::value, "handlerType must be DependencyObject or it's derived type.");

		std::hash<std::string> _shash;
		auto hash = typeid(OwnerType).hash_code() ^ _shash(name);
		if (m_routedEvents.find(hash) != m_routedEvents.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(OwnerType).name());

		RoutedEvent e;
		e.m_hash = hash;
		e.m_name = name;
		e.m_routingStrategy = routingStrategy;
		e.m_ownerType = std::type_index(typeid(OwnerType));
		e.m_argsType = std::type_index(typeid(EventArgsType));
		m_routedEvents[hash] = e;
		return e;
	}

};

}