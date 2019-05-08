#include "TestApp.h"
#include "TestRectanglePage.h"
#include "gui/Image.h"
#include "gui/Rectangle.h"
#include "core/Color.h"

using namespace nb::core;
using namespace nb::gui;
void TestApp::test()
{
	Window w;
/*	auto image = std::make_shared<Image>();
	image->Source = std::make_shared<ImageSource>("e:/Pics/3.jpg");
	image->Margin = Thickness(20);
	image->Stretch = Stretch::Uniform;
	w.Content = image;*/

	auto rect = std::make_shared<Rectangle>();
	//rect->Fill = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/3.jpg"));
	rect->Fill = std::make_shared<SolidColorBrush>(Colors::aliceBlue());
	w.Content = rect;
	w.Content()->Margin = 20;
	this->run();
}
