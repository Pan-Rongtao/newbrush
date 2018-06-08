#include "VideoPage.h"
#include "../../../Include/Gui/Grid.h"
#include "../../../Include/Gui/StackPanel.h"
#include "../../../Include/Gui/Image.h"
#include "../../../Include/Gui/ImageSource.h"
#include "../../../Include/Gui/ImageButton.h"
#include "../../../Include/Gui/ImageTextButton.h"
#include "../../../Include/Gui/Rectangle.h"
#include "../../../Include/Gui/SolidColorBrush.h"
#include "../../../Include/Gui/TranslateTransform.h"

using namespace nb::Gui;
using namespace nb::Media;

VideoPage::VideoPage(void)
{
	nb::Gui::Grid * grid = new nb::Gui::Grid();
	SetRootPanel(grid);

/*	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.5, GridLength::UnitType_Star);
	grid->RowDefCollection->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.5, GridLength::UnitType_Star);
	grid->RowDefCollection->Add(rd);

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(1, GridLength::UnitType_Star);
	grid->ColDefCollection->Add(cd);
*/

	ImageSource * s;
	Image *image;

	image = new Image();
	//image->Height() = 100;
	image->Source = new ImageSource("C:\\a\\123456.jpg");
//	grid->Children()->Add(image);

	image = new Image();
	image->Source = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\video_bg.png");
	image->VertAlignment() = VerticalAlignment_Bottom;
//	grid->Children()->Add(image);

//	image->Visibility() = Visibility_Collapsed;
//	image = new Image();
//	image->Height() = 100;
//	image->Source = new ImageSource("C:\\a\\123456.jpg");
//	grid->Children()->Add(image);
//	Grid::SetRow(image, 1);

//	return;
//	image = new Image();
//	image->Source = s;

	nb::Gui::Rectangle *rg = new nb::Gui::Rectangle();
//	rg->Height() = 100;
//	rg->Width() = 50;
	rg->Fill = new nb::Media::SolidColorBrush(nb::System::Color(128, 0, 0));
//	rg->VertAlignment() = VerticalAlignment_Bottom;
//	grid->Children()->Add(rg);

//	rg = new nb::Gui::Rectangle();
//	rg->Height() = 100;
//	rg->Width() = 50;
//	rg->Fill = new nb::Media::SolidColorBrush(nb::System::Color(128, 0, 0));
//	grid->Children()->Add(rg);

	StackPanel *panel = new StackPanel();
	panel->Orientation() = Orientation_Vert;
//	panel->VertAlignment() = VerticalAlignment_Bottom;
	panel->HorzAlignment() = HorizontalAlignment_Right;
//	panel->Children()->Add(image);

	grid->Children()->Add(panel);


/*	ImageButton *btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\menu_n.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\menu_p.png");
	btn->RenderTransform = new TranslateTransform(100, 10);
	panel->Children()->Add(btn);

	btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\list_n.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\list_p.png");
	panel->Children()->Add(btn);

	btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\folder_n.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\folder_p.png");
	panel->Children()->Add(btn);

	btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\previous_n.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\previous_p.png");
	panel->Children()->Add(btn);

	btn = new ImageButton();
	btn->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\pause_n.png");
	btn->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\pause_p.png");
	panel->Children()->Add(btn);//*/

	ImageTextButton *btn1 = new ImageTextButton();
	btn1->NormalImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\next_n.png");
	btn1->PressImage = new ImageSource("F:\\G4\\14_D&UI\\Mazda J36R\\+_video\\next_p.png");
	//btn1->Text = "asdf";
	panel->Children()->Add(btn1);//*/

}

VideoPage::~VideoPage(void)
{
}
