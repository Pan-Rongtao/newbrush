#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Shape.h"
#include "newbrush/gui/WrapPanel.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::WrapPanel", "[WrapPanel]")
{
	auto m_window = std::make_shared<Window>();

	auto wp = std::make_shared<WrapPanel>();
	wp->setValue(WrapPanel::OrientationProperty(), OrientationE::Horizontal);
//	wp->ItemHeight = 150;
//	wp->ItemWidth = 150;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 50);
//	rc0->VerticalAlignment = VerticalAlignmentE::Top;
//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->setValue(Shape::WidthProperty(), 200);
	rc1->setValue(Shape::HeightProperty(), 100);
//	rc1->VerticalAlignment = VerticalAlignmentE::Top;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 300);
	rc2->setValue(Shape::HeightProperty(), 150);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 400);
	rc3->setValue(Shape::HeightProperty(), 100);
	
	auto rc4 = std::make_shared<Rectangle>();
	rc4->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkCyan()));
	rc4->setValue(Shape::WidthProperty(), 50);
	rc4->setValue(Shape::HeightProperty(), 100);

	auto rc5 = std::make_shared<Rectangle>();
	rc5->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::gold()));
	rc5->setValue(Shape::WidthProperty(), 50);
	rc5->setValue(Shape::HeightProperty(), 100);

	auto rc6 = std::make_shared<Rectangle>();
	rc6->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellow()));
	rc6->setValue(Shape::WidthProperty(), 350);
	rc6->setValue(Shape::HeightProperty(), 100);

	auto rc7 = std::make_shared<Rectangle>();
	rc7->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellowGreen()));
	/*
	wp->Children().add(rc0);
	wp->Children().add(rc1);
	wp->Children().add(rc2);
	wp->Children().add(rc3);
	wp->Children().add(rc4);
	wp->Children().add(rc5);
	wp->Children().add(rc6);
	wp->Children().add(rc7);
	*/
	//m_window.Width = 599;
	m_window->setValue(Window::ContentProperty(), wp);
}
