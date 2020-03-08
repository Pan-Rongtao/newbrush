#include "newbrush/gui/Shape.h"
#include "newbrush/gui/TextBlock.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/UniformGrid.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test UniformGrid", "[UniformGrid]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto uniformGrid = std::make_shared<UniformGrid>();
	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(uniformGrid));
	uniformGrid->setValue(UniformGrid::RowsProperty(), 8);
	uniformGrid->setValue(UniformGrid::ColumnsProperty(), 4);
	uniformGrid->setValue(UniformGrid::FirstColumnProperty(), 1);
	
	auto rc0 = std::make_shared<Rectangle>();
	rc0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::red()));
	rc0->setValue(Shape::WidthProperty(), 50);
	rc0->setValue(Shape::HeightProperty(), 50);
	//	rc0->HorizontalAlignment = HorizontalAlignmentE::Left;

	auto rc1 = std::make_shared<Rectangle>();
	rc1->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::green()));
	//	rc1->Width = 100;
	//	rc1->Height = 100;

	auto rc2 = std::make_shared<Rectangle>();
	rc2->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::blue()));
	//	rc2->Width = 100;
	//	rc2->Height = 100;

	auto rc3 = std::make_shared<Rectangle>();
	rc3->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::firebrick()));
	rc3->setValue(Shape::WidthProperty(), 100);
	rc3->setValue(Shape::HeightProperty(), 100);

	auto es0 = std::make_shared<Ellipse>();
	es0->setValue<BrushPtr>(Shape::FillProperty(), std::make_shared<SolidColorBrush>(Colors::floralWhite()));
	//	es0->Width = 100;
	//	es0->Height = 100;

	auto text = std::make_shared<TextBlock>("abcdefg");
	
	uniformGrid->children().add(rc0);
	uniformGrid->children().add(rc1);
	uniformGrid->children().add(rc2);
	uniformGrid->children().add(rc3);
	uniformGrid->children().add(es0);
	uniformGrid->children().add(text);
	

	app.run(0, nullptr);
}
