#pragma once

#include "System/Timer.h"
#include "Gui/Storyboard.h"
#include "Gui/Rectangle.h"

class HPTest : public nbObject
{
public:
	HPTest(void);
	virtual ~HPTest(void);

	int Run(int argc, char* argv[]);

	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
	void OnTimeout2(nb::System::Timer::TimeoutParam &param);

	nb::System::TimerPtr m_timer1;
	nb::System::TimerPtr m_timer2;

	nb::Media::Storyboard m_storyboard;
	nb::Gui::Rectangle *m_rect;

	int Run_Animation(int argc, char* argv[]);

};
