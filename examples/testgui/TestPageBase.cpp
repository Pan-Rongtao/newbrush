#include "TestPageBase.h"
#include "gui/Grid.h"

#include "gui/Rectangle.h"
#include "gui/SolidColorBrush.h"
#include "gui/ImageSource.h"
#include "gui/ImageBrush.h"

TestPageBase::TestPageBase()
{
	InitRootPage();
}

GridPtr TestPageBase::GetRootGrid() const
{
	return m_RootGrid;
}

void TestPageBase::InitRootPage()
{
	m_RootGrid = new nb::Gui::Grid();
	SetRootPanel(m_RootGrid);

	//rows
//	m_RootGrid->RowDefCollection = new RowDefinitionCollection();
	RowDefinitionCollection *rowColl =  m_RootGrid->RowDefCollection;

	RowDefinition *rd = new RowDefinition();
	rd->Height() = GridLength(0.3f, GridLength::UnitType_Star);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0, GridLength::UnitType_Auto);
	rowColl->Add(rd);

	rd = new RowDefinition();
	rd->Height() = GridLength(0.3f, GridLength::UnitType_Star);
	rowColl->Add(rd);


	//Cols
//	m_RootGrid->ColDefCollection() = new ColDefinitionCollection();
	ColDefinitionCollection *colColl =  m_RootGrid->ColDefCollection;

	ColDefinition *cd = new ColDefinition();
	cd->Width() = GridLength(0.9f, GridLength::UnitType_Star);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0, GridLength::UnitType_Auto);
	colColl->Add(cd);

	cd = new ColDefinition();
	cd->Width() = GridLength(0.2, GridLength::UnitType_Star);
	colColl->Add(cd);

	return;
}

void TestPageBase::Test()
{

}