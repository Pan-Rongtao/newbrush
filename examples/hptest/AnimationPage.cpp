#include "AnimationPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/ElasticEase.h"
#include "../../../Include/Gui/FloatAnimation.h"

using namespace nb::Gui;
AnimationPage::AnimationPage(void)
{
//	m_timer1 = new Timer();
//	m_timer1->Start(1000 * 5);
	//m_timer1->Stop();
//	m_timer1->TimeoutEvent.Add(this, &AnimationTest::OnTimerOut);

	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);

//	grid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);


	//Cols
//	grid->ColDefCollection = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);


	m_rect = new nb::Gui::Rectangle();
//	m_rect->Fill(new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0)));
	m_rect->Fill = new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0));
	m_rect->Width() = 50;
	m_rect->Height() = 50;
	m_rect->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	m_rect->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	grid->Children()->Add(m_rect);
	Grid::SetRow(m_rect, 0);


// 	nb::Media::ElasticEase *ease = new 	nb::Media::ElasticEase();
// 	nb::Media::FloatAnimation *a = new nb::Media::FloatAnimation();
// 	a->Duration() = nb::System::TimeSpan(0, 0, 3);
// 	//nb::System::TimeSpan t = a->Duration();
// 
// 	a->EasingFun() = ease;
// 	a->From() = 0;
// 	a->To() = 80;
// 	
// 	nb::Media::Storyboard::SetTarget(a, m_rect);
// 	nb::Media::Storyboard::SetTargetProperty(a, m_rect->GetTestYProperty());
	nb::Media::ElasticEase *ease = new nb::Media::ElasticEase();
	nb::Media::FloatAnimation *a = new nb::Media::FloatAnimation();
	a->Duration = new nb::System::TimeSpan(0, 0, 3);
	//nb::System::TimeSpan t = a->Duration();

//	ease->SetEasingMode(EasingFunctionBase::EaseIn);
	a->EasingFun() = ease;
	a->From() = 0;
	a->To() = 100;

	nb::Media::Storyboard::SetTarget(a, m_rect);
	nb::Media::Storyboard::SetTargetProperty(a, m_rect->GetTestYProperty());

	m_storyboard.Children()->Add(a);

//	m_storyboard.Duration() = nb::System::TimeSpan(1, 1, 5);

	m_storyboard.Begin();
}

AnimationPage::~AnimationPage(void)
{
}
