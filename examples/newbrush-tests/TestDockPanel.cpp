#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/DockPanel.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test DockPanel", "[DockPanel]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto cv = std::make_shared<DockPanel>();
	cv->setValue(DockPanel::LastChildFillProperty(), true);
	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(cv));

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
//	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 100);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->setValue(Shape::WidthProperty(), 100);
//	rc1->setValue(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 100);
//	rc2->setValue(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
//	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);
	rc3->setValue(UIElement::VerticalAlignmentProperty(), VerticalAlignmentE::Bottom);

	cv->children().add(rc0);
	cv->children().add(rc1);
	cv->children().add(rc2);
	cv->children().add(rc3);

	cv->setDock(rc0, DockE::Top);
	cv->setDock(rc1, DockE::Left);
	cv->setDock(rc2, DockE::Right);
	cv->setDock(rc3, DockE::Bottom);

	app.run(0, nullptr);
}
