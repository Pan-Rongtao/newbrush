#include "newbrush/gui/shapes/Rectangle.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/media/GradientBrush.h"
#include "newbrush/core/media/ImageBrush.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/shapes/Shape.h"
#include "newbrush/gui/panels/WrapPanel.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test WrapPanel", "[WrapPanel]")
{
	Application app;
	auto w = std::make_shared<Window>();
	auto wp = std::make_shared<WrapPanel>();
	w->setValue<UIElementPtr>(Window::ContentProperty(), wp);
	wp->setValue(WrapPanel::OrientationProperty(), OrientationE::Horizontal);
//	wp->ItemHeight = 150;
//	wp->ItemWidth = 150;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 50);
//	rc0->VerticalAlignment = VerticalAlignmentE::Top;
//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->setValue(Shape::WidthProperty(), 200);
	rc1->setValue(Shape::HeightProperty(), 100);
//	rc1->VerticalAlignment = VerticalAlignmentE::Top;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 300);
	rc2->setValue(Shape::HeightProperty(), 150);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 400);
	rc3->setValue(Shape::HeightProperty(), 100);
	
	auto rc4 = std::make_shared<Rectangle>();
	rc4->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkCyan()));
	rc4->setValue(Shape::WidthProperty(), 50);
	rc4->setValue(Shape::HeightProperty(), 100);

	auto rc5 = std::make_shared<Rectangle>();
	rc5->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::gold()));
	rc5->setValue(Shape::WidthProperty(), 50);
	rc5->setValue(Shape::HeightProperty(), 100);

	auto rc6 = std::make_shared<Rectangle>();
	rc6->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellow()));
	rc6->setValue(Shape::WidthProperty(), 350);
	rc6->setValue(Shape::HeightProperty(), 100);

	auto rc7 = std::make_shared<Rectangle>();
	rc7->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellowGreen()));
	
	wp->children().add(rc0);
	wp->children().add(rc1);
	wp->children().add(rc2);
	wp->children().add(rc3);
	wp->children().add(rc4);
	wp->children().add(rc5);
	wp->children().add(rc6);
	wp->children().add(rc7);
	
	app.run(0, nullptr);
}
