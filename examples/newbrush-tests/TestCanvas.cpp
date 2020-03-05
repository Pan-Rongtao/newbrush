#include <glm/gtx/spline.hpp>
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Line.h"
#include "newbrush/gui/Polyline.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/gui/Polygon.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Canvas.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test Canvas", "[Canvas]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto cv = std::make_shared<Canvas>();
	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(cv));

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 100);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->setValue(Shape::WidthProperty(), 100);
	rc1->setValue(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 100);
	rc2->setValue(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);

	auto es0 = std::make_shared<Ellipse>();
	es0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::floralWhite()));
	es0->setValue(Shape::WidthProperty(), 100);
	es0->setValue(Shape::HeightProperty(), 100);

	auto line0 = std::make_shared<Line>();
	line0->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	line0->setValue(Line::X1Property(), 100); 
	line0->setValue(Line::Y1Property(), 100);
	line0->setValue(Line::X2Property(), 200);
	line0->setValue(Line::Y2Property(), 200);

	auto pl0 = std::make_shared<Polyline>();
	pl0->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	std::vector<Point> plPoints = { Point(0, 0), Point(100, 100), Point(150, 50), Point(200, 50), };
	for (float i = 0.0f; i <= 1.000001; i += 0.01f)
	{
	//	Bezier::Bezier<3> cubicBezier({ { 120, 160 },{ 35, 200 },{ 220, 260 },{ 220, 40 } });
		//glm::vec2 p0 = glm::cubic(glm::vec2(0, 0), glm::vec2(100, 100), glm::vec2(150, 50), glm::vec2(200, 50), 0.1 * i);
	//	Bezier::Point p = cubicBezier.valueAt(i);
	//	points.push_back({p.x, p.y});
	}

	pl0->setValue(Polyline::PointsProperty(), std::vector<Point>(plPoints));

	auto pg0 = std::make_shared<Polygon>();
	pg0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	std::vector<Point> pgPoints{ Point(200, 0), Point(300, 100), Point(350, 50), Point(400, 50), };
	pg0->setValue(Polygon::PointsProperty(), std::vector<Point>(pgPoints));

	cv->children().add(rc0);
	cv->children().add(rc1);
	cv->children().add(rc2);
	cv->children().add(rc3);
	cv->children().add(es0);
	cv->children().add(line0);
	cv->children().add(pl0);
	cv->children().add(pg0);

	cv->setLeft(rc0, 100);
	cv->setTop(rc0, 100);
	cv->setLeft(rc1, 200);
	cv->setTop(rc1, 200);
	cv->setLeft(rc2, 300);
	cv->setTop(rc2, 300);
	cv->setLeft(rc3, 400);
	cv->setTop(rc3, 400);
	cv->setLeft(es0, 500);
	cv->setTop(es0, 100);
	cv->setLeft(line0, 100);
	cv->setTop(line0, 0);
	cv->setLeft(pl0, 10);
	cv->setTop(pl0, 10);
	cv->setLeft(pg0, 200);
	cv->setTop(pg0, 10);

	app.run(0, nullptr);
}
