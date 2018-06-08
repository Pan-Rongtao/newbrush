#pragma once

#include "../../../Include/Gui/Page.h"
#include "../../../Include/Gui/ScrollViewer.h"
#include "../../../Include/System/Timer.h"

class ScrollViewerPage : public nb::Gui::Page
{
public:
	ScrollViewerPage(void);
	virtual ~ScrollViewerPage(void);

	void OnTimeout(nb::System::Timer::TimeoutParam &param);

	nb::Gui::ScrollViewerPtr m_sv;
	nb::System::TimerPtr m_timer;
};
