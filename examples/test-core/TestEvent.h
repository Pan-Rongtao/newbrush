#pragma once
#include "../TestBase.h"
#include "core/Event.h"

using namespace nb::core;

class EventSender
{
public:
	struct TimeoutArgs { int a; float b; std::string c; };
	Event<TimeoutArgs> Timeout;

};

class TestEvent : public TestBase
{
public:
	void test();

private:
	void onTimeout(const EventSender::TimeoutArgs &args);
};