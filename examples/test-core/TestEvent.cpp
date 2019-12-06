#include "TestEvent.h"

void TestEvent::test()
{
	printf("----------------test event-----------------\n");
	EventSender sender;
	auto h = sender.Timeout.addHandler(std::bind(&TestEvent::onTimeout, this, std::placeholders::_1));
	h = sender.Timeout.addHandler(std::bind(&TestEvent::onTimeout, this, std::placeholders::_1));
	//sender.Timeout.removeHandler(h);
	//sender.Timeout.clear();
	sender.Timeout.invoke({ 1, 2.2f, "yes" });
	printf("----------------test event-----------------\n\n");
}

void TestEvent::onTimeout(const EventSender::TimeoutArgs & args)
{
	int a = args.a;
	float b = args.b;
	std::string c = args.c;
	printf("TestEvent::onTimeout::a=%d, b=%.2f, c=%s\n", a, b, c.data());
}
