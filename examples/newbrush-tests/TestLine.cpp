#include "newbrush/gui/Line.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Window.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::Line", "[Line]")
{
	auto m_window = std::make_shared<Window>();
	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->setValue(LinearGradientBrush::GradientStopsProperty(), gradientStops);
	auto ln = std::make_shared<Line>();
	ln->setValue(Line::X1Property(), 0);
	ln->setValue(Line::Y1Property(), 0);
	ln->setValue(Line::X2Property(), 500);
	ln->setValue(Line::Y2Property(), 500);
//	ln->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	ln->setValue(Shape::StrokeProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg")));
//	ln->Stroke = linearBrush;
	ln->setValue(Shape::StrokeThicknessProperty(), 50);
	ln->setValue(Shape::StrokeDashArrayProperty(), std::vector<float>{});
	ln->setValue(Shape::MarginProperty(), 100);
	m_window->setValue(Window::ContentProperty(), ln);
}
