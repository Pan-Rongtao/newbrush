#include "HPTest.h"

#include "Core/Type.h"
#include "Gui/Application.h"
#include "System/Point.h"
#include "Gui/Grid.h"
#include "Gui/Rectangle.h"
#include "System/Timer.h"
#include "Gui/FloatAnimation.h"
#include "Gui/ElasticEase.h"
#include "Gui/Storyboard.h"
#include "Gui/Window.h"

using namespace nb::Gui;


class xx
{
public:
	xx() {}
	int a;
};

//#include <windows.h>

HPTest::HPTest(void)
{
/*	int k = GetTickCount();
	for(int i=0; i<1000000; i++)
	{
	//	nb::System::Point nb;
		xx a;
	}

	k = GetTickCount() - k;//*/


	nb::Core::OriginObject::IsEqualTypeObjectFun fun = &nb::Core::OriginObject::IsEqualFun<nb::System::Point>;
	nb::Core::Type::IsEqualObjectFun xx = fun;
}

HPTest::~HPTest(void)
{
	//	std::vector<float> rowsPos;
	//	rowsPos.reserve
}

int HPTest::Run_Animation(int argc, char* argv[])
{
	Application app;
//	app.Init();


//	nb::Gui::Window *pwin = app.GetMainWindow();

	nb::Gui::GridPtr grid = new nb::Gui::Grid();
//	pwin->SetRootPanel(grid);

//	grid->RowDefCollection() = new RowDefinitionCollection();
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
//	grid->ColDefCollection() = new ColDefinitionCollection();
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
	m_rect->Width() = 50;
	m_rect->Height() = 50;
	m_rect->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	grid->Children()->Add(m_rect);
	Grid::SetRow(m_rect, 0);



	nb::Media::ElasticEase *ease = new 	nb::Media::ElasticEase();
	nb::Media::FloatAnimation *a = new nb::Media::FloatAnimation();
	a->Duration = new nb::System::TimeSpan(0, 0, 3);
	nb::System::TimeSpan t = *a->Duration;

	a->EasingFun() = ease;
	a->From() = 0;
	a->To() = 80;
	
	nb::Media::Storyboard::SetTarget(a, m_rect);

	m_storyboard.AddChild(a);

//	m_storyboard.Begin();

	app.Run();

	return 0;
}

int HPTest::Run(int argc, char* argv[])
{
//	m_timer1 = new Timer();
//	m_timer1->Start(1000 * 5);
	//m_timer1->Stop();
//	m_timer1->TimeoutEvent.Add(this, &HPTest::OnTimerOut);

//	m_timer2 = new Timer();
//	m_timer2->Start(0);
//	m_timer2->TimeoutEvent.Add(this, &HPTest::OnTimeout2);

//	return Run_Animation();

	Application app;
//	app.Init();

/*
	nb::Media::ElasticEase *ease = new 	nb::Media::ElasticEase();
	nb::Media::AnimationTimeline tm;
	tm.EasingFun() = ease;
	tm.Begin();


//	DomainPtr testdomain = new Domain();
//	testdomain->Init();

	//nb::Gui::WindowPtr pwin = new nb::Gui::Window("TestWindow", 400, 300);
	nb::Gui::Window *pwin = app.GetGuiWindow();

	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	pwin->SetRootPanel(grid);


	grid->RowDefCollection() = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection();//->RowDefCollection()->Add(new RowDefinition());

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
	grid->ColDefCollection() = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection();

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);


	nb::Gui::Rectangle *r;
	//1
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(155, 0, 0);
//	r->Height() = 100;
	r->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	//r->VertAlignment() = nb::Gui::VerticalAlignment_Bottom;
	grid->AddChild(r);
	Grid::SetRow(r, 0);

	//2
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 155, 0);
	r->Height() = 80;
	r->Width() = 100;
//	r->Margin() = nb::Gui::Thickness(20, 5, 20, 1005);
	//r->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	r->HorzAlignment()= nb::Gui::HorizontalAlignment_Right;
	grid->AddChild(r);
	Grid::SetRow(r, 1);

	//grid->AddChild(NULL);

	//3
	r = new nb::Gui::Rectangle();
	r->Height() = 50;
	r->TestColor() = nb::System::Color(0, 0, 155);
	r->VertAlignment() = VerticalAlignment_Center;
	grid->AddChild(r);
	Grid::SetRow(r, 2);
	Grid::SetCol(r, 1);

	//4
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 155, 155);
	r->Height() = 80;
	r->Width() = 70;
	grid->AddChild(r);
	Grid::SetCol(r, 1);

	//5
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 55, 105);
	r->Height() = 40;
	r->Width() = 158;
	grid->AddChild(r);
	Grid::SetRow(r, 1);
	Grid::SetCol(r, 1);


	///////////////////////////////

	nb::Gui::Grid *g1 = new nb::Gui::Grid();
	grid->AddChild(g1);
	Grid::SetRow(g1, 2);

	g1->RowDefCollection() = new RowDefinitionCollection();
	rowColl =  g1->RowDefCollection();//->RowDefCollection()->Add(new RowDefinition());

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);


	g1->ColDefCollection() = new ColDefinitionCollection();
	colColl =  g1->ColDefCollection();


	cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);


	//1
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 105, 155);
	r->Width() = 30;
	g1->AddChild(r);


	//2
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(100, 5, 155);
	r->Width() = 0.3;
	r->Height() = 0.2;
	r->HorzAlignment() = HorizontalAlignment_Left;
	Grid::SetCol(r, 1);
	g1->AddChild(r);

	//3
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(100, 5, 5);
	r->Width() = 50;
	Grid::SetCol(r, 1);
	Grid::SetRow(r, 1);
	g1->AddChild(r);

//	testdomain->Run();
//*/



	app.Run();

	return 0;

//	nb::System::Point *point = nbType::CreateObjectInstance<nb::System::Point>();

//	nbApplicationPtr px = nb::Core::Type::CreateObjectInstance<nbApplication>();

//	nbObject *pobj = new nbObject();
//	px->SetRefValueEx(px->GetTest3Property(), pobj);
//	px->SetRefValueEx(px->GetTest3Property(), new nbObject);

//	px->Test3() = pobj;

//	px->Bbb() = nb::System::Point(10, 22);

//	nb::System::Point pt = px->Bbb();

//	px->SetValueValue(px->GetBbbProperty(), nb::System::Point(10, 20));
//	px->SetValueValue(px->GetBbbProperty(), nb::System::Point(88, 55));

//	nbObject *pobjx = dynamic_cast<nbObject *>(px->GetRefValue(px->GetTest3Property()));

//	nbApplicationPtr pxx4 = (nbApplication *)NB_TYPE(nbApplication)->GetAssembly()->CreateObjectInstance();
	return 0;
}

void HPTest::OnTimerOut(nb::System::Timer::TimeoutParam &param)
{
	m_storyboard.Begin();

	//param.m_sender->Stop();
}

void HPTest::OnTimeout2(nb::System::Timer::TimeoutParam &param)
{
//	m_timer1 = NULL;
//	m_timer2 = NULL;
}