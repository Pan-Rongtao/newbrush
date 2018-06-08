#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"

class GridPage : public nb::Gui::Page
{
public:
	GridPage(void);
	virtual ~GridPage(void);

	void OnTimerOut(nb::System::Timer::TimeoutParam &param);

	nb::Gui::GridPtr m_grid;
	nb::System::TimerPtr m_timer;

	nb::Gui::RectanglePtr m_rect;
};
