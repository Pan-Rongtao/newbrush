#include "ListPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/ImageButton.h"
#include "../../../Include/Gui/ImageSource.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/Image.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/ScrollViewer.h"
#include "../../../Include/Gui/RotateTransform.h"
#include "../../../Include/Gui/TranslateTransform.h"
#include "ListItem.h"
#include "../../../Include/System/Platform.h"

using namespace nb::Gui;
using namespace nb::Media;


//#define new DEBUG_NEW


ListPage::ListPage(void)
{
//	int *x = new int;
//	ButtonPtr xsdf = new Button();
//	return;


	nb::Gui::Grid * grid = new nb::Gui::Grid();
	SetRootPanel(grid);

//	grid->RenderTransform = new nb::Media::RotateTransform(50, 300, 240);
//	grid->RenderTransform = new nb::Media::TranslateTransform(100, 100);

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
//	rd->Height() = GridLength(50, GridLength::UnitType_Length);
	grid->RowDefCollection->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	grid->RowDefCollection->Add(rd);

//	ColDefinition *cd = new ColDefinition();
//	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
//	grid->ColDefCollection->Add(cd);

//	ListItem *x = new ListItem();
//	x->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
//	x->BottomLineImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\line.png");

	//	x->RenderTransform = new nb::Media::RotateTransform(50, 300, 240);
//	x->RenderTransform = new nb::Media::TranslateTransform(100, 100);
//	grid->Children()->Add(x);
//return;

	Image *image = new Image();
	image->Source = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\topbar.png");
//	image->RenderTransform = new nb::Media::TranslateTransform(100, 100);
	grid->Children()->Add(image);
//	return;

	Grid * contentGrid = new Grid();
	contentGrid->Margin() = nb::Gui::Thickness(0, -20, 0, 0);

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	contentGrid->ColDefCollection->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	contentGrid->ColDefCollection->Add(cd);


	grid->Children()->Add(contentGrid);
	grid->SetRow(contentGrid, 1);

	ImageButton *btn;


//	nb::Gui::Rectangle *rc = new nb::Gui::Rectangle();
//	rc->Fill = new SolidColorBrush(nb::System::Color(255, 0, 0));
//	rc->Height() = 20;
//	grid->Children()->Add(rc);

	ScrollViewer *sv = new ScrollViewer();
	contentGrid->Children()->Add(sv);
//	sv->Height() = 300;
	contentGrid->SetCol(sv, 1);

	StackPanel *panel = new StackPanel();
	panel->Orientation() = Orientation_Vert;
	panel->Margin() = nb::Gui::Thickness(-30, 0, 0, 0);

	sv->Content = panel;


//	contentGrid->Children()->Add(panel);
//	contentGrid->SetCol(panel, 1);


//	btn = new ImageButton();
//	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_subfocus.png");
//	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
//	panel->Children()->Add(btn);

/*	btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_subfocus.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
	panel->Children()->Add(btn);

	for(int i=0; i<2; i++)
	{
		btn = new ImageButton();
		btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_subfocus.png");
		btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
		panel->Children()->Add(btn);
	}*/

	int tick = nb::System::Platform::GetTickCount();

	for(int i=0; i<2; i++)
	{
	//	Control *x = new Control();
//		nb::Gui::Rectangle * x = new nb::Gui::Rectangle();
//	image = new Image();
//	image->Source = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_subfocus.png");
//	panel->Children()->Add(image);

		ListItem *x = new ListItem();
		x->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
		x->BottomLineImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\line.png");

	//	x->RenderTransform = new nb::Media::RotateTransform(50, 300, 240);
		x->RenderTransform = new nb::Media::TranslateTransform(100, 100);

		panel->Children()->Add(x);//*/

//		nb::Gui::Rectangle * rc = new nb::Gui::Rectangle();
	//	rc->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\6List_press.png");
//		rc->Height() = 50;
	//	rc->Fill = new SolidColorBrush(nb::System::Color(255, 0, 0));
	//	panel->Children()->Add(rc);
	}
	
	tick = nb::System::Platform::GetTickCount() - tick;

//	btn = new ImageButton();
//	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\back_n.png");
//	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\back_p.png");
//	btn->Margin() = Thickness(0, -24, 0, 0);
//	contentGrid->Children()->Add(btn);

	image = new Image();
	image->Source = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\01_List\\back_n.png");
//	image->RenderTransform = new nb::Media::TranslateTransform(100, 100);

	contentGrid->Children()->Add(image);
}

ListPage::~ListPage(void)
{
}
