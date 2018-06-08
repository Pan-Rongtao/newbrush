#pragma once


#include "../../../Include/Gui/Page.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/System/Timer.h"
#include "../../../Include/Gui/ScrollViewer.h"
#include "../../../Include/Gui/LineMultiItemsTrack.h"


class ScrollCtrlerTestPage :
	public nb::Gui::Page
{
public:
	ScrollCtrlerTestPage(void);
	virtual ~ScrollCtrlerTestPage(void);
private:
	void OnTimerOut(nb::System::Timer::TimeoutParam &param);
	void On_LineMultItemsTrack_Move(nb::Gui::LineMultiItemsTrack::TrackMoveEventParam &param);

private:
	nb::System::TimerPtr m_timer;

	nb::Gui::Rectangle *m_rect;

	nb::Gui::ScrollViewer *m_pScrollViewer;

	nb::Gui::LineMultiItemsTrack *m_pTrack;
	
};
