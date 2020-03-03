
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/StackPanel.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Shape.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::StackPanel", "[StackPanel]")
{
	auto m_window = std::make_shared<Window>();

	auto sp = std::make_shared<StackPanel>();
//	sp->Orientation = OrientationE::Vertical;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 100);
	rc0->setValue(UIElement::VerticalAlignmentProperty(), VerticalAlignmentE::Top);
	rc0->setValue(UIElement::HorizontalAlignmentProperty(), HorizontalAlignmentE::Right);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
//	rc1->set(Shape::WidthProperty(), 100);
//	rc1->set(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 100);
	rc2->setValue(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);

/*	sp->Children().add(rc0);
	sp->Children().add(rc1);
	sp->Children().add(rc2);
	sp->Children().add(rc3);
	*/
	m_window->setValue(Window::ContentProperty(), sp);
}
