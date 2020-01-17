#pragma once
#include "../TestBase.h"
#include "core/Timer.h"

using namespace nb;

class TestTimer : public TestBase
{
public:
	void test();


private:
	void onTick(const EventArgs &args);
	Timer		m_timer0;
	Timer		m_timer1;
	Timer		m_timer2;

};