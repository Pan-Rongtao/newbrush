#include "TestBrush.h"

void TestBrush::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto rc = std::make_shared<Rectangle>();
	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc->Margin = Thickness(20);
	m_window->Content = rc;
	
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	linearBrush->GradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
//	rc->Fill = linearBrush;
}
