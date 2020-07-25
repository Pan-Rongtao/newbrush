/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 潘荣涛

 * 编写日期: 2018-09

 * 简要描述: 表格布局容器

			表格布局容器为一个按表格方式布局的容器，该容器包含有RowDefCollection
			和ColDefCollection两种属性，分别记录了每行的高度信息和每列的宽度信息，
			对于行的高度或者列的宽度，都使用GridLength来记录长度信息。
			在表格中的所有元素都可以指定行和列。当元素指定行和列之后，元素将会在
			合适的位置表现出来。

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "newbrush/gui/panels/Panel.h"

namespace nb{

enum class GridUnitType
{
	Auto,
	Pixcel,
	Star
};

///////class GridLength
class NB_API GridLength
{
public:
	GridLength();
	GridLength(float value);
	GridLength(GridUnitType type, float value);
	static GridLength automate();
	bool operator == (const GridLength &other) const;
	bool operator != (const GridLength &other) const;

	bool isAuto() const;
	bool isStar() const;
	float value() const;

	GridUnitType gridUnitType() const;
	
private:
	GridUnitType	m_type;
	float			m_value;
};

///////class RowDefinition
class NB_API RowDefinition : public DependencyObject
{
public:
	RowDefinition() = default;
	~RowDefinition() = default;

	static DependencyPropertyPtr HeightProperty();		//高的依赖属性
	static DependencyPropertyPtr MinHeightProperty();	//最小高的依赖属性
	static DependencyPropertyPtr MaxHeightProperty();	//最大高的依赖属性
	static DependencyPropertyPtr ActualHeightProperty();//实际高的依赖属性

};

///////class ColumnDefinition
class NB_API ColumnDefinition : public DependencyObject
{
public:
	ColumnDefinition() = default;
	~ColumnDefinition() = default;

	static DependencyPropertyPtr WidthProperty();		//设定宽的依赖属性
	static DependencyPropertyPtr MinWidthProperty();	//最小宽的依赖属性
	static DependencyPropertyPtr MaxWidthProperty();	//最大宽的依赖属性
	static DependencyPropertyPtr ActualWidthProperty();	//实际宽的依赖属性

};

using RowDefinitionPtr = std::shared_ptr<RowDefinition>;
using ColumnDefinitionPtr = std::shared_ptr<ColumnDefinition>;

///////class Grid
class NB_API Grid : public Panel
{
	RTTR_ENABLE(Panel)
public:
	Grid() = default;
	virtual ~Grid() = default;

	static DependencyPropertyPtr RowDefinitionsProperty();	//行定义的依赖属性
	static DependencyPropertyPtr ColumnDefinitionsProperty();//列定义的依赖属性

	static DependencyPropertyPtr RowProperty();		//行下标的附加属性
	static DependencyPropertyPtr ColumnProperty();	//列下标的附加属性
	static DependencyPropertyPtr RowSpanProperty();	//行跨度的附加属性
	static DependencyPropertyPtr ColumnSpanProperty();	//列跨度的附加属性

	static void setRow(UIElementPtr element, uint32_t row);
	static uint32_t getRow(UIElementPtr element);

	static void setColumn(UIElementPtr element, uint32_t col);
	static uint32_t getColumn(UIElementPtr element);

	static void setRowSpan(UIElementPtr element, uint32_t rowSpan);
	static uint32_t getRowSpan(UIElementPtr element);

	static void setColumnSpan(UIElementPtr element, uint32_t colSpan);
	static uint32_t getColumnSpan(UIElementPtr element);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;


	virtual UIElementPtr clone() const;
private:
	std::vector<float>	m_pixcelWidthsForEachCols;
	std::vector<float>	m_pixcelHeightsForEachRows;
};

}
