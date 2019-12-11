#include "TestWrapPanel.h"
#include "gui/Rectangle.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestWrapPanel::test()
{
	m_window = std::make_shared<nb::gui::Window>();

	auto wp = std::make_shared<WrapPanel>();
	wp->Orientation = OrientationE::Horizontal;
//	wp->ItemHeight = 150;
//	wp->ItemWidth = 150;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 100;
	rc0->Height = 50;
//	rc0->VerticalAlignment = VerticalAlignmentE::Top;
//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->Fill = std::make_shared<SolidColorBrush>(Colors::green());
	rc1->Width = 200;
	rc1->Height = 100;
//	rc1->VerticalAlignment = VerticalAlignmentE::Top;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->Fill = std::make_shared<SolidColorBrush>(Colors::blue());
	rc2->Width = 300;
	rc2->Height = 150;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->Fill = std::make_shared<SolidColorBrush>(Colors::firebrick());
	rc3->Width = 400;
	rc3->Height = 100;
	
	auto rc4 = std::make_shared<Rectangle>();
	rc4->Fill = std::make_shared<SolidColorBrush>(Colors::darkCyan());
	rc4->Width = 50;
	rc4->Height = 100;

	auto rc5 = std::make_shared<Rectangle>();
	rc5->Fill = std::make_shared<SolidColorBrush>(Colors::gold());
	rc5->Width = 50;
	rc5->Height = 100;

	auto rc6 = std::make_shared<Rectangle>();
	rc6->Fill = std::make_shared<SolidColorBrush>(Colors::yellow());
	rc6->Width = 350;
	rc6->Height = 100;

	auto rc7 = std::make_shared<Rectangle>();
	rc7->Fill = std::make_shared<SolidColorBrush>(Colors::yellowGreen());

	wp->Children().add(rc0);
	wp->Children().add(rc1);
	wp->Children().add(rc2);
	wp->Children().add(rc3);
	wp->Children().add(rc4);
	wp->Children().add(rc5);
	wp->Children().add(rc6);
	wp->Children().add(rc7);

	//m_window.Width = 599;
	m_window->Content = wp;
}
