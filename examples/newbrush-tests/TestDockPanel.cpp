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
	cv->set(DockPanel::LastChildFillProperty(), true);

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
//	rc3->HorizontalAlignment = HorizontalAlignmentE::Left;

/*	cv->Children().add(rc0);
	cv->Children().add(rc1);
	cv->Children().add(rc2);
	cv->Children().add(rc3);*/
	cv->setDock(rc0, DockE::Top);
	cv->setDock(rc1, DockE::Left);
	cv->setDock(rc2, DockE::Right);
	cv->setDock(rc3, DockE::Bottom);

	m_window->set(Window::ContentProperty(), cv);
}
