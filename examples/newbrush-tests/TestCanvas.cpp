#include <glm/gtx/spline.hpp>
#include "gui/Rectangle.h"
#include "gui/Line.h"
#include "gui/Polyline.h"
#include "gui/Ellipse.h"
#include "gui/Polygon.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"
#include "gui/Canvas.h"
#include "gui/Window.h"
#include "gui/Shape.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::Canvas", "[Canvas]")
{
	std::shared_ptr<nb::gui::Window> m_window;
	m_window = std::make_shared<Window>();
	auto cv = std::make_shared<Canvas>();

	auto rc0 = std::make_shared<Rectangle>();
	rc0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->set(Shape::WidthProperty(), 100);
	rc0->set(Shape::HeightProperty(), 100);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->set(Shape::WidthProperty(), 100);
	rc1->set(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->set(Shape::WidthProperty(), 100);
	rc2->set(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->set(Shape::WidthProperty(), 100);
	rc3->set(Shape::HeightProperty(), 100);

	auto es0 = std::make_shared<Ellipse>();
	es0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::floralWhite()));
	es0->set(Shape::WidthProperty(), 100);
	es0->set(Shape::HeightProperty(), 100);

	auto line0 = std::make_shared<Line>();
	line0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	line0->set(Line::X1Property(), 100); 
	line0->set(Line::Y1Property(), 100);
	line0->set(Line::X2Property(), 200);
	line0->set(Line::Y2Property(), 200);

	auto pl0 = std::make_shared<Polyline>();
	pl0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	std::vector<Point> points;// { Point(0, 0), Point(100, 100), Point(150, 50), Point(200, 50), };
	for (float i = 0.0f; i <= 1.000001; i += 0.01f)
	{
	//	Bezier::Bezier<3> cubicBezier({ { 120, 160 },{ 35, 200 },{ 220, 260 },{ 220, 40 } });
		//glm::vec2 p0 = glm::cubic(glm::vec2(0, 0), glm::vec2(100, 100), glm::vec2(150, 50), glm::vec2(200, 50), 0.1 * i);
	//	Bezier::Point p = cubicBezier.valueAt(i);
	//	points.push_back({p.x, p.y});
	}

	pl0->set(Polyline::PointsProperty(), std::vector<Point>(points));

	auto pg0 = std::make_shared<Polygon>();
	pg0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkBlue()));
	//std::vector<Point> points{ Point(0, 0), Point(100, 100), Point(150, 50), Point(200, 50), };
	pg0->set(Polyline::PointsProperty(), std::vector<Point>(points));
	/*
	doubleAni.From = 800;
	doubleAni.To = 1000;
	doubleAni.Easing = std::make_shared<ElasticEase>();
	doubleAni.BeginTime = TimeSpan::fromSeconds(1);
	doubleAni.Duration = TimeSpan::fromSeconds(1);
	doubleAni.StateChangedEvent += std::bind(&TestCanvas::onStateChanged, this, std::placeholders::_1);
	doubleAni.ProgressEvent += std::bind(&TestCanvas::onProgress, this, std::placeholders::_1);
	doubleAni.CompleteEvent += std::bind(&TestCanvas::onCompleted, this, std::placeholders::_1);
//	doubleAni.TargetProperty = &m_window->Width;
	doubleAni.begin();
	*/

/*	cv->Children().add(rc0);
	cv->Children().add(rc1);
	cv->Children().add(rc2);
	cv->Children().add(rc3);
	cv->Children().add(es0);
	cv->Children().add(line0);
	cv->Children().add(pl0);
	cv->Children().add(pg0);*/
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

	m_window->set(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(cv));
	
}
