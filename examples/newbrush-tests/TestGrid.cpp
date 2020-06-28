#include "newbrush/gui/Shape.h"
#include "newbrush/gui/Rectangle.h"
#include "newbrush/media/Color.h"
#include "newbrush/gui/TextBlock.h"
#include "newbrush/gui/Ellipse.h"
#include "newbrush/media/SolidColorBrush.h"
#include "newbrush/media/GradientBrush.h"
#include "newbrush/media/ImageBrush.h"
#include "newbrush/gui/Window.h"
#include "newbrush/gui/Grid.h"
#include "newbrush/gui/Application.h"
#include "catch2/catch.hpp"

using namespace nb;

TEST_CASE("Test Grid", "[Grid]")
{
	Application app;
	std::shared_ptr<Window> w = std::make_shared<Window>();
	auto grid = std::make_shared<Grid>();
	w->setValue(Window::ContentProperty(), std::dynamic_pointer_cast<UIElement>(grid));
	
	auto rowdef0 = std::make_shared<RowDefinition>();
	//rowdef0->Height = 200;
	//rowdef0->Height = GridLength(1, GridLength::GridUnitType::Star);
	rowdef0->setValue(RowDefinition::HeightProperty(), GridLength::automate());
	auto rowdef1 = std::make_shared<RowDefinition>();
	//rowdef1->Height = 200;
	rowdef1->setValue(RowDefinition::HeightProperty(), GridLength(GridUnitType::Star, 2));
	auto rowdef2 = std::make_shared<RowDefinition>();
	rowdef2->setValue(RowDefinition::HeightProperty(), GridLength(GridUnitType::Star, 3));

	std::vector<std::shared_ptr<RowDefinition>> rowDefinitions = { rowdef0, rowdef1, rowdef2 };
	grid->setValue(Grid::RowDefinitionsProperty(), rowDefinitions);

	auto coldef0 = std::make_shared<ColumnDefinition>();
	//coldef0->Width = 100;
	auto coldef1 = std::make_shared<ColumnDefinition>();
	//coldef1->Width = 100;
	auto coldef2 = std::make_shared<ColumnDefinition>();
	//coldef2->Width = 100;

	std::vector<std::shared_ptr<ColumnDefinition>> colDefinitions = { coldef0, coldef1, coldef2 };
	grid->setValue(Grid::ColumnDefinitionsProperty(), colDefinitions);


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

	grid->children().add(rc0);
	grid->children().add(rc1);
	grid->children().add(rc2);
	grid->children().add(rc3);
	grid->children().add(es0);
	grid->children().add(text);

	grid->setRow(rc0, 0);
	grid->setColumn(rc0, 0);
	grid->setRow(rc1, 1);
	grid->setColumn(rc1, 0);
	grid->setColumnSpan(rc0, 2);
	grid->setRow(rc2, 2);
	grid->setColumn(rc2, 0);
	grid->setRow(rc3, 0);
	grid->setColumn(rc3, 2);
	grid->setRow(text, 1);
	grid->setColumn(text, 1);
	grid->setRow(es0, 2);
	grid->setColumn(es0, 2);

	app.run(0, nullptr);
}
