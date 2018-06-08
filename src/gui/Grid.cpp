/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 何平

 * 编写日期: 2016-03

 * 简要描述:

 * 修改记录:

 *****************************************************************************/

#include "gui/Grid.h"
#include "core/TypesPropertyValuesStore.h"
#include "core/Exception.h"
#include "GridPrivate.h"

using namespace nb::Gui;
using namespace nb::Core;

NB_OBJECT_TYPE_IMPLEMENT(Grid, Panel, NULL, NULL);

NB_X_OBJECT_PROPERTY_IMPLEMENT_IMMOBILE(Grid, RowDefCollection, RowDefinitionCollection, &Grid::OnRowDefinitionCollectionChanged);
NB_X_OBJECT_PROPERTY_IMPLEMENT_IMMOBILE(Grid, ColDefCollection, ColDefinitionCollection, &Grid::OnColDefinitionCollectionChanged);

NB_X_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(Grid, Row, aInt);
NB_X_OBJECT_EXTERNAL_PROPERTY_IMPLEMENT(Grid, Col, aInt);

//nbDependencyPropertyPtr Grid::property_RowDefCollection = nbDependencyProperty::PrepareProperty("asd", typeid(Grid), typeid(RowDefinitionCollection), NULL);
//nbDependencyProperty * Grid::GetRowDefCollectionProperty() const {return property_RowDefCollection;}

//int GridTest::a()
//{
//	return 10;
//}

namespace nb { namespace Gui {
class GridTypeProperties
{
public:
	GridTypeProperties()
	{
	//	nbDependencyProperty::PrepareExternalProperty("Row", typeid(Grid), typeid(Int), NULL);
	//	nbDependencyProperty::PrepareExternalProperty("Col", typeid(Grid), typeid(Int), NULL);
	}
} s_GridTypeProperties;
}}

Grid::Grid(void)
{
	m_private = new GridPrivate(this);

	RowDefCollection = new RowDefinitionCollection();
	ColDefCollection = new ColDefinitionCollection();
}

Grid::~Grid(void)
{
	delete m_private;
}

GridPrivate * Grid::GetPrivate() const
{
	return m_private;
}

nb::System::Size Grid::ArrangeOverride(const nb::System::Size &finalSize)
{
	return GetPrivate()->ArrangeWork(finalSize);
}

nb::System::Size Grid::MeasureOverride(const nb::System::Size &availableSize)
{
	return GetPrivate()->MeasureWork(availableSize);
}

void Grid::SetRow(UIElement *element, int row)
{
	GridPrivate::SetRow(element, row);
}

void Grid::SetCol(UIElement *element, int col)
{
	GridPrivate::SetCol(element, col);
}

int Grid::GetRow(UIElement *element)
{
	return GridPrivate::GetRow(element);
}

int Grid::GetCol(UIElement *element)
{
	return GridPrivate::GetCol(element);
}

bool Grid::IsSetRow(UIElement *element)
{
	return GridPrivate::IsSetRow(element);
}

bool Grid::IsSetCol(UIElement *element)
{
	return GridPrivate::IsSetCol(element);
}

inline int Grid::GetElementActualRow(UIElement *element, int rows) const
{
	return GetPrivate()->GetElementActualRow(element, rows);
}

inline int Grid::GetElementActualCol(UIElement *element, int cols) const
{
	return GetPrivate()->GetElementActualCol(element, cols);
}

void Grid::OnColDefinitionCollectionChanged(PropertyValueChangedEventArgs &args)
{
	InvalidateArrange();
	InvalidateMeasure();
}

void Grid::OnRowDefinitionCollectionChanged(PropertyValueChangedEventArgs &args)
{
	InvalidateArrange();
	InvalidateMeasure();
}
