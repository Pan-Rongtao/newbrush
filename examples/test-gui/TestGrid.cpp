#include "TestGrid.h"
#include "gui/Rectangle.h"
#include "gui/Ellipse.h"
#include "gui/Brush.h"
#include "core/Color.h"
#include "gui/TextBlock.h"

using namespace nb::core;

void TestGrid::test()
{
	m_window = std::make_shared<nb::gui::Window>();
	auto grid = std::make_shared<Grid>();
	
	auto rowdef0 = std::make_shared<RowDefinition>();
	//rowdef0->Height = 200;
	//rowdef0->Height = GridLength(1, GridLength::GridUnitType::Star);
	rowdef0->Height = GridLength::automate();
	auto rowdef1 = std::make_shared<RowDefinition>();
	//rowdef1->Height = 200;
	rowdef1->Height = GridLength(2, GridLength::GridUnitType::Star);
	auto rowdef2 = std::make_shared<RowDefinition>();
	rowdef2->Height = GridLength(3, GridLength::GridUnitType::Star);
	grid->RowDefinitions().push_back(rowdef0);
	grid->RowDefinitions().push_back(rowdef1);
	grid->RowDefinitions().push_back(rowdef2);

	auto coldef0 = std::make_shared<ColumnDefinition>();
	//coldef0->Width = 100;
	auto coldef1 = std::make_shared<ColumnDefinition>();
	//coldef1->Width = 100;
	auto coldef2 = std::make_shared<ColumnDefinition>();
	//coldef2->Width = 100;
	grid->ColumnDefinitions().push_back(coldef0);
	grid->ColumnDefinitions().push_back(coldef1);
	grid->ColumnDefinitions().push_back(coldef2);


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

	grid->addChild(rc0);
	grid->addChild(rc1);
	grid->addChild(rc2);
	grid->addChild(rc3);
	grid->addChild(es0);
	grid->addChild(text);

	grid->setRow(rc0, 0);
	grid->setColumn(rc0, 0);
	grid->setRow(rc1, 1);
	grid->setColumn(rc1, 0);
	grid->setRowSpan(rc0, 2);
	grid->setRow(rc2, 2);
	grid->setColumn(rc2, 0);
	grid->setRow(rc3, 0);
	grid->setColumn(rc3, 2);
	grid->setRow(text, 1);
	grid->setColumn(text, 1);
	grid->setRow(es0, 2);
	grid->setColumn(es0, 2);


	doubleAni.From = 800;
	doubleAni.To = 2000;
	doubleAni.Easing = std::make_shared<ElasticEase>();
	doubleAni.BeginTime = nb::core::TimeSpan::fromSeconds(1);
	doubleAni.Duration = nb::core::TimeSpan::fromSeconds(5);
//	doubleAni.StateChangedEvent += std::bind(&TestCanvas::onStateChanged, this, std::placeholders::_1);
//	doubleAni.ProgressEvent += std::bind(&TestCanvas::onProgress, this, std::placeholders::_1);
//	doubleAni.CompleteEvent += std::bind(&TestCanvas::onCompleted, this, std::placeholders::_1);
//	doubleAni.TargetProperty = &m_window->Width;
//	doubleAni.begin();

	m_window->Content = grid;
}
