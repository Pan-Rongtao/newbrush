#include "GridPage.h"

#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/RowDefinitionCollection.h"
#include "../../../Include/Gui/ColDefinitionCollection.h"
#include "../../../Include/Gui/TranslateTransform.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/Image.h"
#include "../../../Include/Gui/ImageSource.h"

using namespace nb::Gui;
using namespace nb::Core;

GridPage::GridPage(void)
{
	m_grid = new nb::Gui::Grid();
	SetRootPanel(m_grid);


	StackPanel *sp = new StackPanel();
	sp->Orientation() = Orientation_Vert;
	sp->HorzAlignment() = HorizontalAlignment_Right;


	nb::Gui::Grid *grid = new nb::Gui::Grid();
	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3, GridLength::UnitType_Star);
	grid->RowDefCollection->Add(rd);

//	ColDefinition *cd = new ColDefinition();
//	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
//	grid->ColDefCollection->Add(cd);


	Image *image = new Image;
//	image->Width() = 300;
	image->Source = new nb::Media::ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\next_n.png");
	grid->Children()->Add(image);

//	image = new Image;
//	image->Source = new nb::Media::ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\folder_n.png");
//	grid->Children()->Add(image);

	sp->Children()->Add(grid);

	m_grid->Children()->Add(sp);


/*	RowDefinitionCollection *rowColl =  m_grid->RowDefCollection;//->RowDefCollection()->Add(new RowDefinition());

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
	//grid->ColDefCollection = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  m_grid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.3, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(120, GridLength::UnitType_Length);
	colColl->Add(cd);



	m_rect = new nb::Gui::Rectangle();
	m_rect->Fill = new nb::Media::SolidColorBrush(nb::System::Color(100, 0, 0));

	m_grid->Children()->Add(m_rect);

	m_rect->RenderTransform = new nb::Media::TranslateTransform(50, 0);
	m_grid->RenderTransform = new nb::Media::TranslateTransform(0, 30);





	m_timer = new Timer();
	m_timer->TimeoutEvent.Add(this, &GridPage::OnTimerOut);
	m_timer->SetSingleShot(true);
	m_timer->Start(2000);*/
}

GridPage::~GridPage(void)
{
}

void GridPage::OnTimerOut(Timer::TimeoutParam &param)
{
//	ColDefinition *cd = new ColDefinition();
//	cd->Width() = GridLength(120, GridLength::UnitType_Length);
//	m_grid->ColDefCollection->Add(cd);

//	static bool a = true;
//	if(a)
	{
		m_rect->RenderTransform = NULL;
	}
//	else
//	{
//		m_rect->RenderTransform = new nb::Media::TranslateTransform(50, 0);
//
//	}
//	a = !a;
return;

	nb::Gui::RectanglePtr 	r = new nb::Gui::Rectangle();
	r->Fill = new nb::Media::SolidColorBrush(nb::System::Color(100, 100, 0));
	r->Width() = 100;
	r->Height() = 50;
	m_grid->Children()->Add(r);

	Grid::SetRow(r, 1);

}
