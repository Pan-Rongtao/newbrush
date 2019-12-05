#pragma once
#include "../TestBase.h"
#include "core/RoutedEvent.h"
#include "core/Any.h"

using namespace nb;

class TT
{
public:

	template<class ArgsT>
	void addHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> &handler)
	{
		if (event.argsType() != typeid(ArgsT))
		{
			printf("add handler fail, %s != %s", event.argsType().name(), typeid(ArgsT).name());
			return;
		}
		m_eventHandlers[event.hash()].push_back(handler);
	}
	template<class ArgsT>
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler<ArgsT> handler)
	{
		auto iter = m_eventHandlers.find(event.hash());
		if (iter != m_eventHandlers.end())
		{
			auto &handlers = iter->second;
			auto iterHandler = std::find(handlers.begin(), handlers.end(), handler);
			if (iterHandler != handlers.end())
				handlers.erase(iterHandler);
		}
	}
	template<class ArgsT>
	void raiseEvent(const ArgsT &args)
	{
		auto iter = m_eventHandlers.find(args.Event.hash());
		if (iter != m_eventHandlers.end())
		{
			for (auto &h : iter->second)
			{
				try {
					auto hxx = any_cast<RoutedEventHandler<ArgsT>>(h);
					hxx.invoke(args);
				}
				catch (...) {
					printf("args must be type of [%s]\n", args.Event.argsType().name());
				}
			}
		}
	}

	std::map<size_t, std::vector<Any>>	m_eventHandlers;


	static RoutedEvent ClickEvent();
	
};

class TestRoutedEvent : public TestBase
{
public:
	void test();

};
