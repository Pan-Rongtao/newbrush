#include "newbrush/core/RoutedEvent.h"
#include "newbrush/core/EventArgs.h"
#include "catch2/catch.hpp"

using namespace nb;

class TT : public Object
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
					auto hxx = h.extract<RoutedEventHandler<ArgsT>>();
					hxx.invoke(args);
				}
				catch (...) {
					printf("args must be type of [%s]\n", args.Event.argsType().name());
				}
			}
		}
	}

	std::map<size_t, std::vector<Var>>	m_eventHandlers;


	static RoutedEvent ClickEvent();

};

RoutedEvent TT::ClickEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<TT, MouseButtonEventArgs>("Click", RoutingStrategyE::bubble);
	return e;
}

TEST_CASE("Test nb::RoutedEvent", "[RoutedEvent]")
{
	TT t;
	t.addHandler(TT::ClickEvent(), RoutedEventHandler<MouseButtonEventArgs>([](const MouseButtonEventArgs &args) {
		printf("on click 0\n");
	}));

	MouseButtonEventArgs args(1000, MouseButtonE::Left);
	args.OriginalSource = &t;
	args.Event = TT::ClickEvent();
	t.raiseEvent(args);
}
