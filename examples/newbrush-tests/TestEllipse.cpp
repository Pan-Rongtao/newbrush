#include "TestEllipse.h"
#include "gui/Ellipse.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestEllipse::test()
{
	m_window = std::make_shared<Window>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
/*	linearBrush->GradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	auto ep = std::make_shared<Ellipse>();
	ep->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	ep->Fill = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/3.jpg"));
	ep->Stroke = std::make_shared<SolidColorBrush>(Colors::blue());
	ep->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg"));
	ep->Stroke = linearBrush;
	ep->StrokeThickness = 50;
	ep->StrokeDashArray = {};
//	ep->Margin = 100;
	m_window->Content = ep;*/
}
