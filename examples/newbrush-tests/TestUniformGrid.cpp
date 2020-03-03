#include "newbrush/gui/Shape.h"
#include "newbrush/gui/TextBlock.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/UniformGrid.h"
#include "newbrush/gui/Window.h"
#include "catch2/catch.hpp"

using namespace nb;
using namespace nb::gui;

TEST_CASE("Test nb::UniformGrid", "[UniformGrid]")
{
	auto m_window = std::make_shared<Window>();

	auto uniformGrid = std::make_shared<UniformGrid>();
	uniformGrid->setValue(UniformGrid::RowsProperty(), 8);
	uniformGrid->setValue(UniformGrid::ColumnsProperty(), 4);
	uniformGrid->setValue(UniformGrid::FirstColumnProperty(), 1);
	
	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 50);
	rc0->setValue(Shape::HeightProperty(), 50);
	//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	//	rc1->Width = 100;
	//	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	//	rc2->Width = 100;
	//	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);

	auto es0 = std::make_shared<Ellipse>();
	es0->setValue(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::floralWhite()));
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
	m_window->setValue(Window::ContentProperty(), uniformGrid);
}
