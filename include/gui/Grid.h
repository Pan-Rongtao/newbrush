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
#include "../gui/Panel.h"

namespace nb { namespace gui {

///////class GridLength
class NB_API GridLength
{
public:
	enum class GridUnitType
	{
		Auto,
		Pixcel,
		Star
	};

public:
	GridLength();
	GridLength(float value);
	GridLength(float value, GridUnitType type);
	bool operator == (const GridLength &other) const;
	bool operator != (const GridLength &other) const;

	bool isAuto() const;
	bool isStar() const;
	float value() const;

	GridUnitType gridUnitType() const;

	static GridLength automate();

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

	nb::core::Property_rw<GridLength>		Height;			//设定高
	nb::core::Property_rw<GridLength>		MinHeight;		//最小高限制
	nb::core::Property_rw<GridLength>		MaxHeight;		//最大高限制
	nb::core::Property_r<float>				ActualHeight;	//实际高度
	
	static DependencyProperty				HeightProperty();
	static DependencyProperty				MinHeightProperty();
	static DependencyProperty				MaxHeightProperty();

private:
	float	m_actualHeight;
};

///////class ColumnDefinition
class NB_API ColumnDefinition : public DependencyObject
{
public:
	ColumnDefinition();
	~ColumnDefinition() = default;

	nb::core::Property_rw<GridLength>		Width;			//设定宽
	nb::core::Property_rw<GridLength>		MinWidth;		//最小宽限制
	nb::core::Property_rw<GridLength>		MaxWidth;		//最大宽限制
	nb::core::Property_r<float>				ActualWidth;	//实际宽度

	static DependencyProperty				WidthProperty();
	static DependencyProperty				MinWidthProperty();
	static DependencyProperty				MaxWidthProperty();

private:
	float	m_actualWidth;
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

	nb::core::Property_rw<std::vector<std::shared_ptr<RowDefinition>>>		RowDefinitions;
	nb::core::Property_rw<std::vector<std::shared_ptr<ColumnDefinition>>>	ColumnDefinitions;

	static DependencyProperty	RowDefinitionsProperty();
	static DependencyProperty	ColumnDefinitionsProperty();

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	std::vector<float>	m_pixcelWidthsForEachCols;
	std::vector<float>	m_pixcelHeightsForEachRows;
};

}}
