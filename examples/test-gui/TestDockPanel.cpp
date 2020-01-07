#include "TestDockPanel.h"
#include "gui/Rectangle.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestDockPanel::test()
{
	m_window = std::make_shared<nb::gui::Window>();
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
