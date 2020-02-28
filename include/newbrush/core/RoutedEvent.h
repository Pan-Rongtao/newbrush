#pragma once
#include <string>
#include <typeindex>
#include <functional>
#include <map>
#include "newbrush/core/Object.h"

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
	std::string name() const;
	std::size_t hash() const;
	std::type_index ownerType() const;
	std::type_index argsType() const;
	RoutingStrategyE routingStrategy() const;

	bool operator ==(const RoutedEvent &other) const;
	bool operator !=(const RoutedEvent &other) const;

	static RoutedEvent invalid();

private:
	RoutedEvent(const std::string & name, std::type_index ownerType, std::type_index eventArgsType, RoutingStrategyE routingStrategy, std::size_t hash);

	std::size_t			m_hash{0};
	std::string			m_name;
	RoutingStrategyE	m_routingStrategy;
	std::type_index		m_ownerType;
	std::type_index		m_argsType;
	friend class RoutedEventManager;
};

class RoutedEventArgs;
class NB_API RoutedEventHandler
{
public:
	using CB = std::function<void(std::shared_ptr<RoutedEventArgs>)>;
	RoutedEventHandler(CB callback) : m_callback(std::make_shared<CB>(std::move(callback))) { }

	void invoke(std::shared_ptr<RoutedEventArgs> args) const { (*m_callback)(args); }
	bool operator ==(const RoutedEventHandler &other) const	{ return !(operator!=(other)); }
	bool operator !=(const RoutedEventHandler &other) const	{ return m_callback != other.m_callback; }

private:
	std::shared_ptr<CB>	m_callback;
};


class NB_API RoutedEventManager
{
public:
	template<class OwnerType, class EventArgsType>
	static const RoutedEvent &registerRoutedEvent(const std::string &name, RoutingStrategyE routingStrategy = RoutingStrategyE::bubble)
	{
		static std::map<std::size_t, RoutedEvent>	m_routedEvents;
		//	static_assert(std::is_base_of<Object, ownerType>::value, "handlerType must be DependencyObject or it's derived type.");

		if (name.empty())
		{
			nbThrowException(std::invalid_argument, "'name' is empty.");
		}

		std::hash<std::string> _shash;
		auto _hash = typeid(OwnerType).hash_code() ^ _shash(name);
		RoutedEvent e(name, typeid(OwnerType), typeid(EventArgsType), routingStrategy, _hash);
		auto p = m_routedEvents.insert({ _hash, e });
		if (!p.second)
		{
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(OwnerType).name());
		}

		return p.first->second;
	}

};

}