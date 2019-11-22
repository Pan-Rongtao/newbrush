#include "TestPolyline.h"
#include "gui/Polyline.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestPolyline::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	linearBrush->GradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	auto pl = std::make_shared<Polyline>();
	pl->Points = { {0,0}, {100,100}, {100,200}, {300, 250} };
	pl->StrokeThickness = 20;
	pl->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	pl->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg"));
	//pl->Stroke = linearBrush;
	m_window->Content = pl;
}
