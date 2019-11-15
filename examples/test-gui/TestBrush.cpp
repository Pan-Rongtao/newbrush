#include "TestBrush.h"

void TestBrush::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto rc = std::make_shared<Rectangle>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	linearBrush->GradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc->Fill = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/3.jpg"));
	rc->RadiusX = 50;
	rc->RadiusY = 50;
	rc->Margin = Thickness(50);
	rc->Stroke = std::make_shared<SolidColorBrush>(Colors::blue());
	rc->StrokeThickness = 30;
//	rc->StrokeDashArray = {3, 3};
	rc->StrokeDashOffset = 2;
	m_window->Content = rc;
	
//	rc->Fill = linearBrush;
//	rc->Stroke = linearBrush;
	rc->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/5.jpg"));
}
