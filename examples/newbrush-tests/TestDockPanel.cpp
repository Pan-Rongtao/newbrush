#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/DockPanel.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Shape.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::DockPanel", "[DockPanel]")
{
	auto m_window = std::make_shared<Window>();
	auto cv = std::make_shared<DockPanel>();
	cv->setValue(DockPanel::LastChildFillProperty(), true);

	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 100);
	rc0->setValue(Shape::HeightProperty(), 100);

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->setValue(Shape::WidthProperty(), 100);
	rc1->setValue(Shape::HeightProperty(), 100);

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->setValue(Shape::WidthProperty(), 100);
	rc2->setValue(Shape::HeightProperty(), 100);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);
//	rc3->HorizontalAlignment = HorizontalAlignmentE::Left;

/*	cv->Children().add(rc0);
	cv->Children().add(rc1);
	cv->Children().add(rc2);
	cv->Children().add(rc3);*/
	cv->setDock(rc0, DockE::Top);
	cv->setDock(rc1, DockE::Left);
	cv->setDock(rc2, DockE::Right);
	cv->setDock(rc3, DockE::Bottom);

	m_window->setValue(Window::ContentProperty(), cv);
}
