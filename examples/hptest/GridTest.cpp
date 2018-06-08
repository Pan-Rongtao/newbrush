#include "GridTest.h"
#include "../../../Include/Gui/Application.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/RowDefinitionCollection.h"
#include "../../../Include/Gui/ColDefinitionCollection.h"

using namespace nb::Gui;

GridTest::GridTest(void)
{
}

GridTest::~GridTest(void)
{
}

void GridTest::Run()
{
	nbApplication app;
//	app.Init();

	nb::Gui::Window *pwin = app.GetGuiWindow();

	GridPtr grid = new nb::Gui::Grid();
	pwin->SetRootPanel(grid);

//	grid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Auto);
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


	nb::Gui::Rectangle *r;
	//1
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(155, 0, 0);
//	r->Height() = 100;
	r->Margin() = nb::Gui::Thickness(5, 20, 5, 10);
	//r->VertAlignment() = nb::Gui::VerticalAlignment_Bottom;
	grid->Children()->Add(r);
	Grid::SetRow(r, 0);

	//2
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 155, 0);
	r->Height() = 80;
	r->Width() = 100;
//	r->Margin() = nb::Gui::Thickness(20, 5, 20, 1005);
	//r->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	//r->HorzAlignment()= nb::Gui::HorizontalAlignment_Right;
	grid->Children()->Add(r);
	Grid::SetRow(r, 1);

	//grid->AddChild(NULL);

	//3
	r = new nb::Gui::Rectangle();
	r->Height() = 100;
	r->Width() = 200;
	r->TestColor() = nb::System::Color(0, 0, 155);
	r->VertAlignment() = VerticalAlignment_Center;
	grid->Children()->Add(r);
	Grid::SetRow(r, 2);
	Grid::SetCol(r, 1);

	//4
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 155, 155);
	r->Height() = 80;
	r->Width() = 70;
	grid->Children()->Add(r);
	Grid::SetCol(r, 1);

	//5
	r = new nb::Gui::Rectangle();
	r->TestColor() = nb::System::Color(0, 55, 105);
	r->Height() = 40;
	r->Width() = 158;
	grid->Children()->Add(r);
	Grid::SetRow(r, 1);
	Grid::SetCol(r, 1);
//	app.Run();
}
