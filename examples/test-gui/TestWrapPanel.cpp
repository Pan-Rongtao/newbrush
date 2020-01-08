#include "TestWrapPanel.h"
#include "gui/Rectangle.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestWrapPanel::test()
{
	m_window = std::make_shared<Window>();

	auto wp = std::make_shared<WrapPanel>();
	wp->set(WrapPanel::OrientationProperty(), OrientationE::Horizontal);
//	wp->ItemHeight = 150;
//	wp->ItemWidth = 150;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->set(Shape::WidthProperty(), 100);
	rc0->set(Shape::HeightProperty(), 50);
//	rc0->VerticalAlignment = VerticalAlignmentE::Top;
//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	rc1->set(Shape::WidthProperty(), 200);
	rc1->set(Shape::HeightProperty(), 100);
//	rc1->VerticalAlignment = VerticalAlignmentE::Top;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	rc2->set(Shape::WidthProperty(), 300);
	rc2->set(Shape::HeightProperty(), 150);

	auto rc3 = std::make_shared<Rectangle>();
	rc3->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->set(Shape::WidthProperty(), 400);
	rc3->set(Shape::HeightProperty(), 100);
	
	auto rc4 = std::make_shared<Rectangle>();
	rc4->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::darkCyan()));
	rc4->set(Shape::WidthProperty(), 50);
	rc4->set(Shape::HeightProperty(), 100);

	auto rc5 = std::make_shared<Rectangle>();
	rc5->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::gold()));
	rc5->set(Shape::WidthProperty(), 50);
	rc5->set(Shape::HeightProperty(), 100);

	auto rc6 = std::make_shared<Rectangle>();
	rc6->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellow()));
	rc6->set(Shape::WidthProperty(), 350);
	rc6->set(Shape::HeightProperty(), 100);

	auto rc7 = std::make_shared<Rectangle>();
	rc7->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::yellowGreen()));
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
	m_window->set(Window::ContentProperty(), wp);
}
