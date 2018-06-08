#pragma once
#include "../../../Include/Gui/Page.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Storyboard.h"
#include "../../../Include/Gui/Rectangle.h"

class PointAnimationTestPage :	public nb::Gui::Page
{
public:
	PointAnimationTestPage(void);
	virtual ~PointAnimationTestPage(void);
private:
	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
private:
	nb::System::TimerPtr m_timerPosAnimation;

	nb::Media::Storyboard m_storyboard;
	nb::Gui::Rectangle *m_rect;
};
