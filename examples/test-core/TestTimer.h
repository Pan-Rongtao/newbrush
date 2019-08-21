#pragma once
#include "../TestBase.h"
#include "core/Timer.h"

using namespace nb;

class TestTimer : public TestBase
{
public:
	void test();


private:
	void onTick0(const Timer::TickArgs &args);
	void onTick1(const Timer::TickArgs &args);
	void onTick2(const Timer::TickArgs &args);
	Timer		m_timer0;
	Timer		m_timer1;
	Timer		m_timer2;

};