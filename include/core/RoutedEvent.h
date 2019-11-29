#pragma once
#include <string>
#include <typeindex>
#include <functional>
#include <map>
#include "../core/Def.h"

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
	RoutingStrategyE routingStrategy() const;

	bool operator ==(const RoutedEvent &other) const;
	bool operator !=(const RoutedEvent &other) const;

private:
	std::size_t			m_hash{0};
	std::string			m_name;
	RoutingStrategyE	m_routingStrategy;
	std::type_index		m_ownerType;
	std::type_index		m_handleTyp;
	friend class RoutedEventManager;
};

class NB_API RoutedEventArgs
{
public:
	RoutedEventArgs();
	RoutedEventArgs(RoutedEvent event);

	//已处理标志
	void setHandled(bool handled);
	bool handled() const;

	//路由事件
	void setRoutedEvent(const RoutedEvent &event);
	RoutedEvent routedEvent() const;

private:
	bool		m_handled;
	RoutedEvent	m_event;
	//Object	m_originalSource;
	//Object	m_source;
};

//template<class ArgsT>
class NB_API RoutedEventHandler
{
public:
	RoutedEventHandler(std::function<void(RoutedEventArgs)> callback)
		: m_callback(std::make_shared<std::function<void(RoutedEventArgs)>>(std::move(callback)))
	{
	}
	void invoke(const RoutedEventArgs &args)
	{
		(*m_callback)(args);
	}
	bool operator ==(const RoutedEventHandler &other) const
	{
		return m_callback == other.m_callback;
	}

private:
	std::shared_ptr<std::function<void(RoutedEventArgs)>>	m_callback;
};

class NB_API RoutedEventManager
{
public:
	template<class ownerType, class handlerType>
	void registerRoutedEvent(const std::string &name, RoutingStrategyE routingStrategy = RoutingStrategyE::bubble)
	{
		static_assert(std::is_base_of<DependencyObject, ownerType>::value, "handlerType must be DependencyObject or it's derived type.");

		std::hash<std::string> _shash;
		auto hash = typeid(ownerType).hash_code() ^ _shash(name);
		if(m_routedEvents.find(hash) != m_routedEvents.end())
			nbThrowException(std::logic_error, "[%s] has already been registered for [%s]", name.data(), typeid(ownerType).name());

		RoutedEvent e;
		e.m_name = name;
		e.m_routingStrategy = routingStrategy;
		e.m_ownerType = std::type_index(typeid(ownerType));
		e.m_handleTyp = std::type_index(typeid(handlerType));
		m_routedEvents[hash] = e;
		return e;
	}

private:
	static std::map<std::size_t, RoutedEvent>	m_routedEvents;
};

}