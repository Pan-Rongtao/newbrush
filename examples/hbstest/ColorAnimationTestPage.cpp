#include "ColorAnimationTestPage.h"
#include "../../../Include/Gui/ColorAnimation.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/SolidColorBrush.h"

using namespace nb::Gui;

ColorAnimationTestPage::ColorAnimationTestPage(void)
{
	m_timerPosAnimation = new Timer();
	m_timerPosAnimation->Start(1000*4);
	m_timerPosAnimation->TimeoutEvent.Add(this, &ColorAnimationTestPage::OnTimerOut);



	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);

	//grid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3f, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3f, GridLength::UnitType_Star);
	rowColl->Add(rd);


	//Cols
	//grid->ColDefCollection = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3f, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);


	m_rect = new nb::Gui::Rectangle();
	m_rect->Fill = new nb::Media::SolidColorBrush(nb::System::Color(155, 155, 155));
	m_rect->Width() = 50;
	m_rect->Height() = 50;
	m_rect->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	m_rect->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	grid->Children()->Add(m_rect);
	Grid::SetRow(m_rect, 0);
}

ColorAnimationTestPage::~ColorAnimationTestPage(void)
{
}

void ColorAnimationTestPage::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	//m_rect->TestY() = 0;
	m_rect->Fill = new nb::Media::SolidColorBrush(nb::System::Color(155, 155, 155));
	m_storyboard.Begin();
}
