#include "ScrollViewerPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/Image.h"

using namespace nb::Gui;
ScrollViewerPage::ScrollViewerPage(void)
{
	nb::Gui::Grid * grid = new nb::Gui::Grid();
	SetRootPanel(grid);

	m_sv = new nb::Gui::ScrollViewer();
	grid->Children()->Add(m_sv);

	StackPanel *panel =new StackPanel();
	panel->Orientation() = ::nb::Gui::Orientation_Vert;

	for(int i=0; i<3; i++)
	{
		nb::Gui::Rectangle *rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(100, 0, 0));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 100, 0));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(100, 0, 100));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

			rc = new nb::Gui::Rectangle;
		rc->Fill = new nb::Media::SolidColorBrush(nb::System::Color(0, 80, 100));
		rc->Height() = 50;
		rc->Width() = 200;
		panel->Children()->Add(rc);

		nb::Gui::Image * image = new nb::Gui::Image();

	}

	m_sv->Content = panel;

	m_timer = new nb::System::Timer();
//	m_timer->Start(1);
	m_timer->TimeoutEvent.Add(this, &ScrollViewerPage::OnTimeout);
}

ScrollViewerPage::~ScrollViewerPage(void)
{
}

void ScrollViewerPage::OnTimeout(nb::System::Timer::TimeoutParam &param)
{
	static float a = 0;
	a -= 1;
	if(a < -200) a = 0;
	m_sv->ScrollToVerticalOffset(a);

}
