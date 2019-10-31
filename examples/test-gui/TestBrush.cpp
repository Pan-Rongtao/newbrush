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
	auto gs0 = GradientStop(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = GradientStop(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = GradientStop(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = GradientStop(Color(255, 0, 125, 0), 1.0f);
	stops.push_back(gs0);
	stops.push_back(gs1);
	stops.push_back(gs2);
	stops.push_back(gs3);
	linearBrush->GradientStops = GradientStopCollection(stops);
	rc->Fill = linearBrush;
}
