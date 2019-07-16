/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-04

 * 简要描述: 通过SetTop()和SetLeft()来设置Canvas控件下面的元素放置的位置
		

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "../gui/Panel.h"
#include "../core/Size.h"

namespace nb{ namespace gui {

class NB_API Canvas : public Panel
{
public:
	Canvas();
	virtual ~Canvas();

	static constexpr char *AttachedPropertyLeft		= "Canvas.Left";
	static constexpr char *AttachedPropertyRight	= "Canvas.Right";
	static constexpr char *AttachedPropertyTop		= "Canvas.Top";
	static constexpr char *AttachedPropertyBottom	= "Canvas.Bottom";
	
	void setLeft(std::shared_ptr<UIElement> element, double left);
	double getLeft(std::shared_ptr<UIElement> element);

	void setRight(std::shared_ptr<UIElement> element, double right);
	double getRight(std::shared_ptr<UIElement> element);

	void setTop(std::shared_ptr<UIElement> element, double top);
	double getTop(std::shared_ptr<UIElement> element);

	void setBottom(std::shared_ptr<UIElement> element, double bottom);
	double getBottom(std::shared_ptr<UIElement> element);


protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;
};

}}
