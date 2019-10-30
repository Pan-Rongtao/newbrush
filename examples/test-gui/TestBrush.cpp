#include "TestBrush.h"

void TestBrush::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto rc = std::make_shared<Rectangle>();
	rc->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc->Margin = Thickness(0);
	m_window->Content = rc;
	
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	stops.push_back(GradientStop(Color(255, 255, 0, 0), 0));
	stops.push_back(GradientStop(Color(255, 0, 0, 0), 1));
	linearBrush->GradientStops = GradientStopCollection(stops);
	rc->Fill = linearBrush;
}
