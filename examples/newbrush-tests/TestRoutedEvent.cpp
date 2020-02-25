#include "newbrush/core/RoutedEvent.h"
#include "newbrush/core/EventArgs.h"
#include "catch2/catch.hpp"

using namespace nb;

class TT : public Object
{
public:
	void addHandler(const RoutedEvent &event, const RoutedEventHandler &handler)
	{
		m_eventHandlers[event.hash()].push_back(handler);
	}
	void removeHandler(const RoutedEvent &event, const RoutedEventHandler &handler)
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
	void raiseEvent(std::shared_ptr<RoutedEventArgs> args)
	{
		auto iter = m_eventHandlers.find(args->Event.hash());
		if (iter != m_eventHandlers.end())
		{
			for (auto &h : iter->second)
			{
					h.invoke(args);
			}
		}
	}

	std::map<size_t, std::vector<RoutedEventHandler>>	m_eventHandlers;


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
	t.addHandler(TT::ClickEvent(), RoutedEventHandler([](std::shared_ptr<RoutedEventArgs> args) {
		printf("on click 0\n");
	}));

	auto args = std::make_shared<MouseButtonEventArgs >(1000, MouseButtonE::Left);
	args->OriginalSource = &t;
	args->Event = TT::ClickEvent();
	t.raiseEvent(args);
}
