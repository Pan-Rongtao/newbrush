
#include "gui/Rectangle.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"
#include "gui/StackPanel.h"
#include "gui/Window.h"
#include "gui/Shape.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::StackPanel", "[StackPanel]")
{
	auto m_window = std::make_shared<Window>();

	auto sp = std::make_shared<StackPanel>();
//	sp->Orientation = OrientationE::Vertical;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->set(Shape::WidthProperty(), 100);
	rc0->set(Shape::HeightProperty(), 100);
	rc0->set(UIElement::VerticalAlignmentProperty(), VerticalAlignmentE::Top);
	rc0->set(UIElement::HorizontalAlignmentProperty(), HorizontalAlignmentE::Right);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
//	rc1->set(Shape::WidthProperty(), 100);
//	rc1->set(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->set(Shape::WidthProperty(), 100);
	rc2->set(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->set(Shape::WidthProperty(), 100);
	rc3->set(Shape::HeightProperty(), 100);

/*	sp->Children().add(rc0);
	sp->Children().add(rc1);
	sp->Children().add(rc2);
	sp->Children().add(rc3);
	*/
	m_window->set(Window::ContentProperty(), sp);
}
