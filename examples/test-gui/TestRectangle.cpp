#include "TestRectanglePage.h"
#include "gui/Grid.h"
#include "gui/Rectangle.h"
#include "gui/Brush.h"
#include "gui/ImageSource.h"
#include "gui/Image.h"

using namespace nb::gui;
void TestRectanglePage::test()
{
	TestSolidColorBrush();
	TestImageBrush();
	TestImage();
}

void TestRectanglePage::TestSolidColorBrush()
{
/*	g_Brush = new SolidColorBrush(nb::System::Color::greenPure());

	nb::gui::Rectangle *rectangle = new nb::gui::Rectangle();
	rectangle->Fill = g_Brush;//new nb::Media::SolidColorBrush(nb::System::Color(155, 0, 0));
	rectangle->Fill->SetOpacity(0.3);
	rectangle->Margin() = 0;//nb::gui::Thickness(5, 20, 5, 10);
	Grid::SetRow(rectangle, 0);
	m_RootGrid->Children()->Add(rectangle);
	rectangle->RenderTransform = new TranslateTransform(0, 0);

	return;
	nb::gui::Rectangle *rectangle1 = new nb::gui::Rectangle();
	rectangle1->Margin() = 10;
	rectangle1->Fill = g_Brush;//new nb::Media::SolidColorBrush(nb::System::Color(0, 255, 0));

	Grid::SetRow(rectangle1, 2);
	Grid::SetCol(rectangle1, 0);
	m_RootGrid->Children()->Add(rectangle1);

	*/
}

//²âÊÔÍ¼Æ¬»­Ë¢
void TestRectanglePage::TestImageBrush()
{
/*	nb::gui::Rectangle *imgRectangle = new nb::gui::Rectangle();
	imgRectangle->Fill = new ImageBrush(new ImageSource("f:/download/a.bmp"));
	imgRectangle->Fill->SetOpacity(0.5);
	imgRectangle->Margin() = 0;
	//rc->VertAlignment() = nb::gui::VerticalAlignment_Bottom;
	Grid::SetRow(imgRectangle, 0);
	Grid::SetCol(imgRectangle, 0); 
	m_RootGrid->Children()->Add(imgRectangle);*/
}

//²âÊÔImage
void TestRectanglePage::TestImage()
{
/*	nb::gui::ImagePtr img = new Image();
	img->Source = new ImageSource("f:/download/b.bmp");
	img->Margin() = Thickness(0);
//	img->Width() = 200;
//	img->Height() = 200;
	img->HorzAlignment() = HorizontalAlignment_Stretch;
//	img->Stretch = Uniform;
	Grid::SetRow(img, 2);
	Grid::SetCol(img, 0);
	m_RootGrid->Children()->Add(img);*/
}