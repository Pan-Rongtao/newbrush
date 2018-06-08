/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 何平

 * 编写日期: 2016-03

 * 简要描述: 表格布局容器

			表格布局容器为一个按表格方式布局的容器，该容器包含有RowDefCollection
			和ColDefCollection两种属性，分别记录了每行的高度信息和每列的宽度信息，
			对于行的高度或者列的宽度，都使用GridLength来记录长度信息。
			在表格中的所有元素都可以指定行和列。当元素指定行和列之后，元素将会在
			合适的位置表现出来。

 * 修改记录:

 *****************************************************************************/

#pragma once

#include "Panel.h"
#include "system/Size.h"
#include "RowDefinitionCollection.h"
#include "ColDefinitionCollection.h"


namespace nb { namespace Gui {

class GridPrivate;

//class __declspec(dllimport) GridTest
//{
//public:
//	static int a();
//};

class NB_GUI_DECLSPEC_INTERFACE Grid : public Panel
{
	NB_OBJECT_TYPE_DECLARE();

public:
	Grid(void);
	virtual ~Grid(void);

	static void SetRow(UIElement *element, int row);
	static int GetRow(UIElement *element);

	static bool IsSetRow(UIElement *element);
	static bool IsSetCol(UIElement *element);

	static void SetCol(UIElement *element, int col);
	static int GetCol(UIElement *element);

	NB_X_OBJECT_PROPERTY_DECLARE_IMMOBILE(RowDefCollection, RowDefinitionCollection, Grid);
	NB_X_OBJECT_PROPERTY_DECLARE_IMMOBILE(ColDefCollection, ColDefinitionCollection, Grid);

	NB_X_OBJECT_EXTERNAL_PROPERTY_DECLARE(Row, aInt);
	NB_X_OBJECT_EXTERNAL_PROPERTY_DECLARE(Col, aInt);

	GridPrivate * GetPrivate() const;

protected:
	virtual System::Size ArrangeOverride(const nb::System::Size &finalSize);
	virtual System::Size MeasureOverride(const System::Size &availableSize);

private:
	inline int GetElementActualRow(UIElement *element, int rows) const;
	inline int GetElementActualCol(UIElement *element, int cols) const;

	void OnColDefinitionCollectionChanged(Core::PropertyValueChangedEventArgs &args);
	void OnRowDefinitionCollectionChanged(Core::PropertyValueChangedEventArgs &args);


	GridPrivate *m_private;
};

typedef nbObjectPtrDerive<Grid, PanelPtr> GridPtr;
	

class TestObjectEx : public TestObject
{
};

}}
