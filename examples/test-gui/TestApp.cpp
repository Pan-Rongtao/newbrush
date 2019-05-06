#include "TestApp.h"
#include "TestRectanglePage.h"
#include "gui/Image.h"

using namespace nb::gui;
void TestApp::test()
{
	Window w;
	auto image = std::make_shared<Image>();
	image->Source = std::make_shared<ImageSource>("E:/Pics/5.jpg");
	image->Margin = Thickness(1);
	w.Content = image;
	this->run();
}
