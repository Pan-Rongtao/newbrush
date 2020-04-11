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
#include "newbrush/gui/Panel.h"

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
	RowDefinition();
	~RowDefinition() = default;

	static DependencyProperty	HeightProperty();		//高的依赖属性
	static DependencyProperty	MinHeightProperty();	//最小高的依赖属性
	static DependencyProperty	MaxHeightProperty();	//最大高的依赖属性
	static DependencyProperty	ActualHeightProperty();	//实际高的依赖属性

};

///////class ColumnDefinition
class NB_API ColumnDefinition : public DependencyObject
{
public:
	ColumnDefinition();
	~ColumnDefinition() = default;

	static DependencyProperty	WidthProperty();		//设定宽的依赖属性
	static DependencyProperty	MinWidthProperty();		//最小宽的依赖属性
	static DependencyProperty	MaxWidthProperty();		//最大宽的依赖属性
	static DependencyProperty	ActualWidthProperty();	//实际宽的依赖属性

};

///////class Grid
class NB_API Grid : public Panel
{
public:
	Grid();
	virtual ~Grid() = default;

	static constexpr char *AttachedPropertyRow			= "Grid.Row";
	static constexpr char *AttachedPropertyColumn		= "Grid.Column";
	static constexpr char *AttachedPropertyRowSpan		= "Grid.RowSpan";
	static constexpr char *AttachedPropertyColumnSpan	= "Grid.ColumnSpan";

	void setRow(std::shared_ptr<UIElement> element, uint32_t row);
	uint32_t getRow(std::shared_ptr<UIElement> element);

	void setColumn(std::shared_ptr<UIElement> element, uint32_t col);
	uint32_t getColumn(std::shared_ptr<UIElement> element);

	void setRowSpan(std::shared_ptr<UIElement> element, uint32_t rowSpan);
	uint32_t getRowSpan(std::shared_ptr<UIElement> element);

	void setColumnSpan(std::shared_ptr<UIElement> element, uint32_t colSpan);
	uint32_t getColumnSpan(std::shared_ptr<UIElement> element);

	static DependencyProperty								RowDefinitionsProperty();	//行定义的依赖属性
	static DependencyProperty								ColumnDefinitionsProperty();//列定义的依赖属性

	static EditorInfo getEditorInfo();

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;


	virtual std::shared_ptr<UIElement> clone() const;
private:
	std::vector<float>	m_pixcelWidthsForEachCols;
	std::vector<float>	m_pixcelHeightsForEachRows;
};

}
