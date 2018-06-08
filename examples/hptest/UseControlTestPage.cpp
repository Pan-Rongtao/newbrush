#include "UseControlTestPage.h"
#include "../../../Include/Gui/SolidColorBrush.h"

using namespace nb::Gui;

MyUseControl::MyUseControl()
	: UseControl(new Grid())
{
	m_body = (Grid *)GetBody();

//	m_body->RowDefCollection = new RowDefinitionCollection();
//	m_body->ColDefCollection = new ColDefinitionCollection();

for(int i=0; i<1; i++)
{
	nb::Gui::RectanglePtr rect = new nb::Gui::Rectangle();
	rect->Fill = new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0));
	rect->Width() = 50;
	rect->Height() = 50;
	//rect->Margin() = nb::Gui::Thickness(5, 0, 5, 10);
	//rect->VertAlignment() = nb::Gui::VerticalAlignment_Top;
	m_body->Children()->Add(rect);

	Grid::SetRow(rect, 0);
}
}

UseControlTestPage::UseControlTestPage(void)
{
	nb::Gui::GridPtr grid = new nb::Gui::Grid();
	SetRootPanel(grid);


//	grid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

/*	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	rowColl->Add(rd);*/


	//Cols
//	grid->ColDefCollection = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  grid->ColDefCollection;

/*	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(50, GridLength::UnitType_Length);
	colColl->Add(cd);*/



	MyUseControl *ctrl = new MyUseControl();

	grid->Children()->Add(ctrl);

}

UseControlTestPage::~UseControlTestPage(void)
{
}
