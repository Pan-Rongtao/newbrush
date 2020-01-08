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
	uniformGrid->set(UniformGrid::RowsProperty(), 8);
	uniformGrid->set(UniformGrid::ColumnsProperty(), 4);
	uniformGrid->set(UniformGrid::FirstColumnProperty(), 1);
	
	auto rc0 = std::make_shared<Rectangle>();
	rc0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->set(Shape::WidthProperty(), 50);
	rc0->set(Shape::HeightProperty(), 50);
	//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	//	rc1->Width = 100;
	//	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	//	rc2->Width = 100;
	//	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->set(Shape::WidthProperty(), 100);
	rc3->set(Shape::HeightProperty(), 100);

	auto es0 = std::make_shared<Ellipse>();
	es0->set(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::floralWhite()));
	//	es0->Width = 100;
	//	es0->Height = 100;

	auto text = std::make_shared<TextBlock>("abcdefg");
	/*
	uniformGrid->Children().add(rc0);
	uniformGrid->Children().add(rc1);
	uniformGrid->Children().add(rc2);
	uniformGrid->Children().add(rc3);
	uniformGrid->Children().add(es0);
	uniformGrid->Children().add(text);
	*/
	m_window->set(Window::ContentProperty(), uniformGrid);
}
