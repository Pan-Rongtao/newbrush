#include "ButtonTestPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/System/String.h"


using namespace nb::Gui;
using namespace nb::Media;
using namespace nb::System;

ButtonTestPage::ButtonTestPage()
{
	m_timer = new Timer();
	m_timer->TimeoutEvent.Add(this, &ButtonTestPage::OnTimerOut);
	//m_timer->Start(1);

	
	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);


	StackPanel *panel =new StackPanel();
	panel->Orientation() = ::nb::Gui::Orientation_Vert;

	grid->Children()->Add(panel);


	m_pImageTextButton = new ImageTextButton();
	m_pImageTextButton->NormalImage = new ImageSource("F:\\nwet\\work\\project\\Control\\OpenGL\\NewBrush_TeamWork\\TestImage\\scan_n.png");
	m_pImageTextButton->PressImage = new ImageSource("F:\\nwet\\work\\project\\Control\\OpenGL\\NewBrush_TeamWork\\TestImage\\scan_p.png");
	m_pImageTextButton->Text = new nb::System::String("Scan");


	m_pRepeatButton = new RepeatButton();
	m_pRepeatButton->Delay = 2000;
	m_pRepeatButton->Interval = 1000;
	m_pRepeatButton->Width() = 100;
	m_pRepeatButton->Height() = 30;

	m_pRepeatButton->RepeatClickEvent.Add(this, &ButtonTestPage::OnRepeatClick);

	panel->Children()->Add(m_pRepeatButton);
	panel->Children()->Add(m_pImageTextButton);

}


ButtonTestPage::~ButtonTestPage()
{
}

void ButtonTestPage::OnRepeatClick(nb::Gui::RepeatButton::RepeatClickEventParam &param)
{
	static int a = 0;
	printf("OnRepeatClick a = %d\n", a);
	a ++;
}

void ButtonTestPage::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	static float pos = 0.0f;
	pos --;
	if(pos <= -200)
	{
		pos = 0.0f;
	}
}