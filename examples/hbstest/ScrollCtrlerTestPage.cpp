#include "ScrollCtrlerTestPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/SolidColorBrush.h"

#include "../../../Include/Gui/Application.h"

using namespace nb::Gui;

ScrollCtrlerTestPage::ScrollCtrlerTestPage()
{
	m_timer = new Timer();
	m_timer->TimeoutEvent.Add(this, &ScrollCtrlerTestPage::OnTimerOut);
	m_timer->Start(1);

	
	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);


	m_pScrollViewer = new nb::Gui::ScrollViewer();
	grid->Children()->Add(m_pScrollViewer);

	

	StackPanel *panel =new StackPanel();
	panel->Orientation() = ::nb::Gui::Orientation_Vert;
	nb::Gui::Rectangle *rc1 = new nb::Gui::Rectangle;
	rc1->Fill = new nb::Media::SolidColorBrush(nb::System::Color(6/25, 0, 100));
	rc1->Height() = 100;
	rc1->Width() = 200;
	panel->Children()->Add(rc1);

	for(int i=0; i<25; i++)
	{
		nb::Gui::Rectangle *rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(i/25, 0, 100));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, i/25, 100));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(i/25, 100, i/25));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(100, i/25, i/25));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		//nb::Gui::Image * image = new nb::Gui::Image();

	}

	m_pScrollViewer->Content = panel;
	m_pTrack = App()->GetGuiWindow()->CreateLineMultiItemsTrack(NULL);
	m_pTrack->TrackMoveEvent.Add(this, &ScrollCtrlerTestPage::On_LineMultItemsTrack_Move);
	m_pTrack->SetItemCount(100);
	m_pTrack->SetItemSize(71);
	m_pTrack->SetPageSize(426);
	m_pTrack->SetFirstItem(0);
	m_pTrack->SetFirstItemOffset(0.0f);

}

ScrollCtrlerTestPage::~ScrollCtrlerTestPage()
{
}

void ScrollCtrlerTestPage::On_LineMultItemsTrack_Move(nb::Gui::LineMultiItemsTrack::TrackMoveEventParam &param)
{
	int a = 0;
	float fItemSize = m_pTrack->GetItemSize();
	m_pScrollViewer->ScrollToVerticalOffset(-(fItemSize*param.m_nFirstItem - param.m_fFirstItemOffset));
	int b = 0;
	int c = a + b;
	c++;
}


void ScrollCtrlerTestPage::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	static float pos = 0.0f;
	pos --;
	if(pos <= -200)
	{
		pos = 0.0f;
	}
	//m_pScrollViewer->ScrollToVerticalOffset(pos);
}
