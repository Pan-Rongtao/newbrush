#include "TestRoutedEvent.h"
#include "core/MouseEvent.h"

RoutedEvent TT::ClickEvent()
{
	static auto e = RoutedEventManager::registerRoutedEvent<TestRoutedEvent, MouseButtonEventArgs>("Click", RoutingStrategyE::bubble);
	return e;
}

void TestRoutedEvent::test()
{
	TT t;
	t.addHandler(TT::ClickEvent(), RoutedEventHandler<MouseButtonEventArgs>([](const MouseButtonEventArgs &args) {
		printf("on click 0\n");
	}));

	MouseButtonEventArgs args(1000, MouseButtonE::Left);
	args.Event = TT::ClickEvent();
	t.raiseEvent(args);
}
