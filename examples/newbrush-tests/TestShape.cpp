#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/gui/Line.h"
#include "newbrush/gui/Polygon.h"
#include "newbrush/gui/Polyline.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "catch2/catch.hpp"
#include "bezier.h"

using namespace nb;

TEST_CASE("test Rectangle", "[Rectangle]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Rectangle");

	auto rc = std::make_shared<Rectangle>();
	//rc->setValue(Shape::WidthProperty(), 100.0f);
	//rc->setValue(Shape::HeightProperty(), 100.0f);
	rc->setValue(Rectangle::MarginProperty(), Thickness(100));
	rc->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	//rc->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("g:/pics/shibuya.jpg")));
	rc->setValue(Rectangle::RadiusXProperty(), 50);
	rc->setValue(Rectangle::RadiusYProperty(), 50);

	rc->setValue(Rectangle::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc->setValue(Rectangle::StrokeThicknessProperty(), 5.0f);
	rc->setValue<std::vector<float>>(Rectangle::StrokeDashArrayProperty(), {  });
	rc->setValue(Rectangle::StrokeDashOffsetProperty(), 0);
	
	w->setValue(Window::ContentProperty(), rc);

	app.run(0, nullptr);
}

TEST_CASE("Test Ellipse", "[Ellipse]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Ellipse");

	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	linearBrush->setValue(LinearGradientBrush::GradientStopsProperty(), std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 }));

	auto ep = std::make_shared<Ellipse>();
	ep->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("g:/pics/boat.jpg")));
//	ep->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
//	ep->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	ep->setValue<BrushPtr>(Shape::FillProperty(), linearBrush);
	ep->setValue(Shape::StrokeThicknessProperty(), 50);
	ep->setValue(Shape::StrokeDashArrayProperty(), std::vector<float>{1});
	ep->setValue(Shape::MarginProperty(), Thickness(100));

	w->setValue<UIElementPtr>(Window::ContentProperty(), ep);

	app.run(0, nullptr);
}

TEST_CASE("Test Line", "[Line]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Line");

	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->setValue(LinearGradientBrush::GradientStopsProperty(), gradientStops);
	auto ln = std::make_shared<Line>();
	ln->setValue(Line::X1Property(), 100);
	ln->setValue(Line::Y1Property(), 100);
	ln->setValue(Line::X2Property(), 500);
	ln->setValue(Line::Y2Property(), 500);
	//	ln->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	ln->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("g:/pics/scene0.jpg")));
	ln->setValue<BrushPtr>(Shape::StrokeProperty(), linearBrush);
	ln->setValue(Shape::StrokeThicknessProperty(), 50);
	ln->setValue(Shape::StrokeDashArrayProperty(), std::vector<float>{});
	ln->setValue<Thickness>(Shape::MarginProperty(), 100);

	w->setValue<UIElementPtr>(Window::ContentProperty(), ln);

	app.run(0, nullptr);
}

TEST_CASE("Test Polyline", "[Polyline]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Polyline");

	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->setValue(LinearGradientBrush::GradientStopsProperty(), gradientStops);
	auto pl = std::make_shared<Polyline>();
	std::vector<Point> points;// = { { 0, 0 },{ 100,100 },{ 100,200 },{ 300, 250 } };

	Bezier::Bezier<3> cubicBezier({ { 0, 0 },{ 100,100 },{ 100,200 },{ 300, 250 } }/*{ { 120, 160 },{ 35, 200 },{ 220, 260 },{ 220, 40 } }*/);
	for (float i = 0.0f; i <= 1.000001; i += 0.1f)
	{
			Bezier::Point p = cubicBezier.valueAt(i);
			points.push_back({p.x, p.y});
	}

	pl->setValue(Polyline::PointsProperty(), points);
	//pl->setValue(Polyline::PointsProperty(), std::vector<Point>{ {0, 0}, { 100,100 }, { 100,200 }, { 300, 250 } });
	pl->setValue(Shape::StrokeThicknessProperty(), 20);
	pl->setValue<BrushPtr>(Shape::StrokeProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
//	pl->setValue(Shape::StrokeProperty(), std::make_shared<ImageBrush>(std::make_shared<ImageSource>("g:/pics/doudou.jpg")));
	//pl->Stroke = linearBrush;

	w->setValue<UIElementPtr>(Window::ContentProperty(), pl);
	app.run(0, nullptr);
}

TEST_CASE("Test nb::Polygon", "[Polygon]")
{
	Application app;
	auto w = std::make_shared<Window>();
	w->setValue(Window::TitleProperty(), "Polygon");

	auto linearBrush = std::make_shared<LinearGradientBrush>();
	auto stops = std::vector<GradientStop>();
	auto gs0 = std::make_shared<GradientStop>(Color(255, 255, 255, 255), 0.0f);
	auto gs1 = std::make_shared<GradientStop>(Color(255, 255, 0, 0), 0.33f);
	auto gs2 = std::make_shared<GradientStop>(Color(255, 0, 0, 255), 0.66f);
	auto gs3 = std::make_shared<GradientStop>(Color(255, 0, 125, 0), 1.0f);
	auto gradientStops = std::make_shared<GradientStopCollection>(std::vector<GradientStopPtr>{ gs0, gs1, gs2, gs3 });
	linearBrush->setValue(LinearGradientBrush::GradientStopsProperty(), gradientStops);
	auto pl = std::make_shared<Polygon>();
	pl->setValue(Polygon::PointsProperty(), std::vector<Point>{ { 0, 0 }, { 500,0 }, { 300,100 }, { 0,800 }});
	//pl->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	pl->setValue<BrushPtr>(Shape::FillProperty(), linearBrush);
	pl->setValue(Shape::StrokeThicknessProperty(), 20);
	//pl->Stroke = std::make_shared<SolidColorBrush>(Colors::red());
	//pl->Stroke = std::make_shared<ImageBrush>(std::make_shared<ImageSource>("e:/Pics/5.jpg"));
	//pl->Stroke = linearBrush;

	w->setValue<UIElementPtr>(Window::ContentProperty(), pl);
	app.run(0, nullptr);
}
