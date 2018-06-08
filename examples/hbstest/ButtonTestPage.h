#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/Gui/ImageTextButton.h"
#include "../../../Source/Gui/RepeatButton.h"
#include "../../../Include/System/Timer.h"

class ButtonTestPage : public nb::Gui::Page
{
public:
	ButtonTestPage(void);
	virtual ~ButtonTestPage(void);
private:
	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
	void OnRepeatClick(nb::Gui::RepeatButton::RepeatClickEventParam &param);
private:
	nb::System::TimerPtr m_timer;

	ImageTextButtonPtr m_pImageTextButton;

	RepeatButtonPtr m_pRepeatButton;

};