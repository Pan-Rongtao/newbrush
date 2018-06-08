#pragma once


#include "../../../Include/Gui/Page.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Slider.h"


class SliderTestPage : public nb::Gui::Page
{
public:
	SliderTestPage(void);
	virtual ~SliderTestPage(void);
private:
	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
private:
	nb::System::TimerPtr m_timer;

	nb::Gui::SliderPtr m_pSlider;

};