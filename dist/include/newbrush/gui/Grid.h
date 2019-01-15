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
#include "../gui/RowDefinition.h"
#include "../gui/ColumnDefinition.h"

namespace nb { namespace gui {

class NB_API Grid : public Panel
{
public:
	Grid();
	virtual ~Grid();

	void setRow(int row, std::shared_ptr<UIElement> element);
	int getRow(std::shared_ptr<UIElement> element);

	void setColumn(int col, std::shared_ptr<UIElement> element);
	int getColumn(std::shared_ptr<UIElement> element);

	void setRowSpan(std::shared_ptr<UIElement> element, int value);
	int getRowSpan(std::shared_ptr<UIElement> element);

	void setColumnSpan(std::shared_ptr<UIElement> element, int value);
	int getColumnSpan(std::shared_ptr<UIElement> element);

public:
	nb::core::Property_rw<std::vector<std::shared_ptr<RowDefinition>>>		RowDefinitions;
	nb::core::Property_rw<std::vector<std::shared_ptr<RowDefinition>>>		ColumnDefinitions;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

private:

};

}}
