#include "core/Event.h"
#include "catch2/catch.hpp"

using namespace nb;

class EventSender
{
public:
	struct TimeoutArgs { int a; float b; std::string c; };
	Event<TimeoutArgs> Timeout;

};

void onTimeout(const EventSender::TimeoutArgs & args)
{
	int a = args.a;
	float b = args.b;
	std::string c = args.c;
	printf("TestEvent::onTimeout::a=%d, b=%.2f, c=%s\n", a, b, c.data());
}

TEST_CASE("Test nb::Event", "Event")
{
	printf("----------------test event-----------------\n");
	EventSender sender;
	auto h = sender.Timeout.addHandler(std::bind(onTimeout, std::placeholders::_1));
	h = sender.Timeout.addHandler(std::bind(onTimeout, std::placeholders::_1));
	//sender.Timeout.removeHandler(h);
	//sender.Timeout.clear();
	sender.Timeout.invoke({ 1, 2.2f, "yes" });
	printf("----------------test event-----------------\n\n");
}
