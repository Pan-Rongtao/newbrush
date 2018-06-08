#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Storyboard.h"
#include "../../../Include/Gui/Rectangle.h"

class AnimationTestPage : public nb::Gui::Page
{
public:
	AnimationTestPage(void);
	virtual ~AnimationTestPage(void);

	nb::System::TimerPtr m_timer1;
	nb::System::TimerPtr m_timer2;
	nb::Media::Storyboard m_storyboard;
	nb::Gui::Rectangle *m_rect;

	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
};