#include "TestDockPanel.h"

void TestDockPanel::test()
{
	auto cv = std::make_shared<DockPanel>();

	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 100;
	rc0->Height = 100;

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

	cv->Children().push_back(rc0);
	cv->Children().push_back(rc1);
	cv->Children().push_back(rc2);
	cv->Children().push_back(rc3);
	
	cv->setDock(rc0, DockE::Top);
	cv->setDock(rc1, DockE::Bottom);
	cv->setDock(rc2, DockE::Left);
	cv->setDock(rc3, DockE::Right);

	m_window.Content = cv;
}
