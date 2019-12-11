#include "TestUniformGrid.h"
#include "gui/Shape.h"
#include "gui/TextBlock.h"
#include "gui/Rectangle.h"
#include "gui/Ellipse.h"
#include "media/SolidColorBrush.h"
#include "media/GradientBrush.h"
#include "media/ImageBrush.h"

void TestUniformGrid::test()
{
	m_window = std::make_shared<nb::gui::Window>();

	auto uniformGrid = std::make_shared<UniformGrid>();
	uniformGrid->Rows = 8;
	uniformGrid->Columns = 4;
	uniformGrid->FirstColumn = 1;
	
	auto rc0 = std::make_shared<Rectangle>();
	rc0->Fill = std::make_shared<SolidColorBrush>(Colors::red());
	rc0->Width = 50;
	rc0->Height = 50;
	//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->Fill = std::make_shared<SolidColorBrush>(Colors::green());
	//	rc1->Width = 100;
	//	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->Fill = std::make_shared<SolidColorBrush>(Colors::blue());
	//	rc2->Width = 100;
	//	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->Fill = std::make_shared<SolidColorBrush>(Colors::firebrick());
	rc3->Width = 100;
	rc3->Height = 100;

	auto es0 = std::make_shared<Ellipse>();
	es0->Fill = std::make_shared<SolidColorBrush>(Colors::floralWhite());
	//	es0->Width = 100;
	//	es0->Height = 100;

	auto text = std::make_shared<TextBlock>("abcdefg");
	
	uniformGrid->Children().add(rc0);
	uniformGrid->Children().add(rc1);
	uniformGrid->Children().add(rc2);
	uniformGrid->Children().add(rc3);
	uniformGrid->Children().add(es0);
	uniformGrid->Children().add(text);
	
	m_window->Content = uniformGrid;
}
