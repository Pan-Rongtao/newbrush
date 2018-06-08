#include "AnimationTestPage.h"

#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/VisualStateGroup.h"
#include "../../../Include/Gui/ObjectAnimation.h"
#include "../../../Include/Gui/VisualState.h"
#include "../../../Include/Gui/VisualStateStoryboard.h"
#include "../../../include/Gui/ElasticEase.h"
#include "../../../Include/Gui/BounceEase.h"
#include "../../../Include/Gui/PowerEase.h"
#include "../../../Include/Gui/FloatAnimation.h"
#include "../../../Include/Gui/Canvas.h"
#include "../../../Include/System/Colors.h"
#include "../../../Include/Gui/LineEase.h"
#include "../../../Include/Gui/TransformGroup.h"
#include "../../../Include/Gui/TranslateTransform.h"
#include "../../../Include/Gui/RotateTransform.h"
#include "../../../Include/Gui/MatrixTransform.h"
#include "../../../Include/Gui/ScaleTransform.h"

using namespace nb::Gui;

AnimationTestPage::AnimationTestPage(void)
{

	m_timer1 = new Timer();
	m_timer1->Start(1000 * 5);
	//m_timer1->Stop();
	m_timer1->TimeoutEvent.Add(this, &AnimationTestPage::OnTimerOut);

	//nb::Gui::GridPtr grid = new nb::Gui::Grid();
	nb::Gui::CanvasPtr canvas = new nb::Gui::Canvas();
	//SetRootPanel(grid);
	SetRootPanel(canvas);

// 	grid->RowDefCollection() = new RowDefinitionCollection();
// 	RowDefinitionCollection *rowColl =  grid->RowDefCollection();//->RowDefCollection()->Add(new RowDefinition());
// 
// 	RowDefinition *rd = new RowDefinition();
// 	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
// 	rowColl->Add(rd);
// 
// 	rd = new RowDefinition();
// 	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
// 	rowColl->Add(rd);
// 
// 	rd = new RowDefinition();
// 	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
// 	rowColl->Add(rd);
// 
// 
// 	//Cols
// 	grid->ColDefCollection() = new ColDefinitionCollection();
// 	ColDefinitionCollection *colColl =  grid->ColDefCollection();
// 
// 	ColDefinition *cd = new ColDefinition();
// 	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
// 	colColl->Add(cd);
// 
// 	cd = new ColDefinition();
// 	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
// 	colColl->Add(cd);

// 	cd = new ColDefinition();
// 	cd->Width() = GridLength(50, GridLength::UnitType_Length);
// 	colColl->Add(cd);

	m_rect = new nb::Gui::Rectangle();
	//m_rect->Fill(new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0)));
	m_rect->Fill = new nb::Media::SolidColorBrush(nb::System::Colors::Green());
	m_rect->Width() = 50;
	m_rect->Height() = 50;
	m_rect->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	m_rect->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	//grid->Children()->Add(m_rect);
	//canvas->AddChild(m_rect);
	canvas->Children()->Add(m_rect);
	//Grid::SetRow(m_rect, 0);
	Canvas::SetLeft(m_rect,0);
	Canvas::SetTop(m_rect,0);

    /*nb::Media::ElasticEase *ease = new nb::Media::ElasticEase();
    nb::Media::FloatAnimation *a = new nb::Media::FloatAnimation();
    a->Duration = new nb::System::TimeSpan(0, 0, 1);
	ease->SetEasingMode(nb::Media::EasingFunctionBase::EaseOut);
    a->EasingFun() = ease;
    a->From() = 0;
    a->To() = 180;
    nb::Media::Storyboard::SetTarget(a, m_rect);
    nb::Media::Storyboard::SetTargetProperty(a, m_rect->GetTestYProperty());
    m_storyboard.Children()->Add(a);
    m_storyboard.Begin();*/

	nb::Media::TranslateTransformPtr t1 = new nb::Media::TranslateTransform(0.5,2.0);
    nb::Media::ScaleTransformPtr t2 = new nb::Media::ScaleTransform(8.0,8.0,0.5,1.5);
    //nb::Media::MatrixTransformPtr t = new nb::Media::MatrixTransform();
    nb::Media::TransformGroupPtr ii = new nb::Media::TransformGroup();
    ii->Children()->Add(t1);
   	ii->Children()->Add(t2);
    Point m_point(1.0,1.0);
    //t->SetScaleXY(8.0,8.0);
    //t->SetCenterXY(0.5,1.2);
     Point mm;
     mm = ii->Translate(m_point);
     float vv = 2.5;
   	  

}

void AnimationTestPage::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	m_rect->TestY() = 0;
	m_storyboard.Begin();

	//param.m_sender->Stop();
}

AnimationTestPage::~AnimationTestPage(void)
{

}

