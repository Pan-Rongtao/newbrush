#include "TestApp.h"
#include "TestRectanglePage.h"
#include "gui/Image.h"

using namespace nb::gui;
void TestApp::test()
{
	Window w;
	auto image = std::make_shared<Image>();
	image->Source = std::make_shared<ImageSource>("e:/Pics/3.jpg");
	image->Margin = Thickness(20);
	image->Stretch = Stretch::Uniform;
	w.Content = image;
	this->run();
}
