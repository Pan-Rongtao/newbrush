#include "TestLine.h"
#include "gui/Line.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestLine::test()
{
	m_window = std::make_shared<Window>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->set(LinearGradientBrush::GradientStopsProperty(), gradientStops);
	auto ln = std::make_shared<Line>();
	ln->set(Line::X1Property(), 0);
	ln->set(Line::Y1Property(), 0);
	ln->set(Line::X2Property(), 500);
	ln->set(Line::Y2Property(), 500);
//	ln->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	ln->set(Shape::StrokeProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg")));
//	ln->Stroke = linearBrush;
	ln->set(Shape::StrokeThicknessProperty(), 50);
	ln->set(Shape::StrokeDashArrayProperty(), std::vector<float>{});
	ln->set(Shape::MarginProperty(), 100);
	m_window->set(Window::ContentProperty(), ln);
}
