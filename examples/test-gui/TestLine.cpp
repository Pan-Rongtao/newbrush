#include "TestLine.h"
#include "gui/Line.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestLine::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	linearBrush->GradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	auto ln = std::make_shared<Line>();
	ln->X1 = 0;
	ln->Y1 = 0;
	ln->X2 = 500;
	ln->Y2 = 500;
	ln->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	ln->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg"));
//	ln->Stroke = linearBrush;
	ln->StrokeThickness = 50;
	ln->StrokeDashArray = {};
	ln->Margin = 100;
	m_window->Content = ln;
}
