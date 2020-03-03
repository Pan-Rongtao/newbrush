#include "newbrush/gui/Polyline.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Window.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::Polyline", "[Polyline]")
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
	auto pl = std::make_shared<Polyline>();
	pl->setValue(Polyline::PointsProperty(), std::vector<Point>{ {0,0}, {100,100}, {100,200}, {300, 250} });
	pl->setValue(Shape::StrokeThicknessProperty(), 20);
	pl->setValue(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	pl->setValue(Shape::StrokeProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg")));
	//pl->Stroke = linearBrush;
	m_window->setValue(Window::ContentProperty(), pl);
}
