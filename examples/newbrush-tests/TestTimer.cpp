#include "core/Timer.h"
#include "catch2/catch.hpp"

using namespace nb;

Timer		m_timer0;
Timer		m_timer1;
Timer		m_timer2;

void onTick(const EventArgs & args)
{
	printf("on timer0 tick\n");
	//	m_timer1.stop();

	printf("on timer1 tick\n");
	if (!m_timer2.isActive())
		m_timer2.start();

	printf("on timer2 tick\n");
	printf("timer0 isActive=%d\n", m_timer0.isActive());
	printf("timer1 isActive=%d\n", m_timer1.isActive());
	printf("timer2 isActive=%d\n", m_timer2.isActive());
	m_timer0.stop();
	m_timer1.stop();
	m_timer2.stop();
	m_timer1.start();
	m_timer1.stop();
	m_timer1.start();
	printf("timer0 isActive=%d\n", m_timer0.isActive());
	printf("timer1 isActive=%d\n", m_timer1.isActive());
	printf("timer2 isActive=%d\n", m_timer2.isActive());
}

TEST_CASE("Test nb::Timer", "[Timer]")
{
	m_timer0.setInterval(1000);
	m_timer0.Tick += std::bind(onTick, std::placeholders::_1);
	m_timer0.start();
	m_timer1.setInterval(2000);
	m_timer1.Tick += std::bind(onTick, std::placeholders::_1);
	m_timer1.start(1);
	m_timer1.start(10);
	m_timer1.start(100);
	m_timer1.start(10000);
//	m_timer1.stop();
	m_timer2.setInterval(3000);
	m_timer2.Tick += std::bind(onTick, std::placeholders::_1);
	m_timer2.setSingleShot(true);
	m_timer2.start();

	while (true)
	{
		Timer::driveInLoop();
	}
}
