#include "newbrush/gui/shapes/Rectangle.h"
#include "newbrush/core/media/SolidColorBrush.h"
#include "newbrush/core/media/GradientBrush.h"
#include "newbrush/core/media/ImageBrush.h"
#include "newbrush/gui/panels/StackPanel.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/shapes/Shape.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test StackPanel", "[StackPanel]")
{
	Application app;
	auto w = std::make_shared<Window>();
	auto sp = std::make_shared<StackPanel>();
	w->setValue<UIElementPtr>(Window::ContentProperty(), sp);
	sp->setValue(StackPanel::OrientationProperty(), OrientationE::Horizontal);

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100.0f);
	rc0->setValue(Shape::HeightProperty(), 100.0);
	auto ww = rc0->getValue<float>(Shape::WidthProperty());
//	rc0->setValue(UIElement::VerticalAlignmentProperty(), VerticalAlignmentE::Top);
//	rc0->setValue(UIElement::HorizontalAlignmentProperty(), HorizontalAlignmentE::Right);

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

	sp->children().add(rc0);
	sp->children().add(rc1);
	sp->children().add(rc2);
	sp->children().add(rc3);

	app.run(0, nullptr);
	
}
