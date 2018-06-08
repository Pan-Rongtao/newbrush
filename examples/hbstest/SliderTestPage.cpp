#include "SliderTestPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/SolidColorBrush.h"

using namespace nb::System;
using namespace nb::Gui;
using namespace nb::Media;


SliderTestPage::SliderTestPage()
{
	m_timer = new Timer();
	m_timer->TimeoutEvent.Add(this, &SliderTestPage::OnTimerOut);
	//m_timer->Start(1);

	
	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);


	StackPanel *panel =new StackPanel();
	panel->Orientation() = ::nb::Gui::Orientation_Vert;

	grid->Children()->Add(panel);
	for(int i=0; i<3; i++)
	{
		m_pSlider = new nb::Gui::Slider();
		panel->Children()->Add(m_pSlider);

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
}


SliderTestPage::~SliderTestPage()
{
}


void SliderTestPage::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	static float pos = 0.0f;
	pos --;
	if(pos <= -200)
	{
		pos = 0.0f;
	}
}