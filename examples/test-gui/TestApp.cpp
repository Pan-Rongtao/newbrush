#include "TestApp.h"
#include "gui/Image.h"
#include "gui/Shape.h"
#include "core/Color.h"
#include "gui/Rectangle.h"
#include "media/ImageSource.h"
#include "media/SolidColorBrush.h"

using namespace nb;
using namespace nb::gui;
void TestApp::test()
{
	m_window = std::make_shared<nb::gui::Window>();
#if 0
	auto image = std::make_shared<Image>();
	image->Source = std::make_shared<ImageSource>("e:/Pics/5.jpg");
	image->Margin = Thickness(20);
	image->Stretch = StretchE::Uniform;
	m_window->Content = image;
#else
	auto rect = std::make_shared<Rectangle>();
	rect->Fill = std::make_shared<SolidColorBrush>(Colors::darkBlue());
	rect->Margin = Thickness(100);
	rect->MinHeight = 1;
	rect->Height = 10.0f;
	m_window->Content = rect;
#endif

/*	auto ellipse = std::make_shared<nb::gui::Ellipse>();
	//ellipse->Fill = std::make_shared<SolidColorBrush>(Colors::darkBlue());
	ellipse->Fill = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/3.jpg"));
	m_window.Content = ellipse;*/

//	m_window.Content()->Margin = Thickness(300, 200, 300, 200);

}
