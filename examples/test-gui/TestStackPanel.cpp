#include "TestStackPanel.h"

void TestStackPanel::test()
{
	auto sp = std::make_shared<StackPanel>();
//	sp->Orientation = OrientationE::Vertical;

	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 100;
	rc0->Height = 100;
//	rc0->VerticalAlignment = VerticalAlignmentE::Top;
//	rc0->HorizontalAlignment = HorizontalAlignmentE::Right;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->Fill = std::make_shared<SolidColorBrush>(Colors::green());
	rc1->Width = 100;
	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->Fill = std::make_shared<SolidColorBrush>(Colors::blue());
	rc2->Width = 100;
	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->Fill = std::make_shared<SolidColorBrush>(Colors::firebrick());
	rc3->Width = 100;
	rc3->Height = 100;

	sp->addChild(rc0);
	sp->addChild(rc1);
	sp->addChild(rc2);
	sp->addChild(rc3);

	m_window.Content = sp;
}
