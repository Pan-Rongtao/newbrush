/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 苏志飞

 * 编写日期: 2016-04

 * 简要描述: 通过SetTop()和SetLeft()来设置Canvas控件下面的元素放置的位置
		

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "newbrush/gui/panels/Panel.h"
#include "newbrush/core/Size.h"

namespace nb{

class NB_API Canvas : public Panel
{
	RTTR_ENABLE(Panel)
public:
	Canvas() = default;
	virtual ~Canvas() = default;

	static DependencyPropertyPtr LeftProperty();
	static DependencyPropertyPtr RightProperty();
	static DependencyPropertyPtr TopProperty();
	static DependencyPropertyPtr BottomProperty();
	
	static void setLeft(UIElementPtr element, float left);
	static float getLeft(UIElementPtr element);

	static void setRight(UIElementPtr element, float right);
	static float getRight(UIElementPtr element);

	static void setTop(UIElementPtr element, float top);
	static float getTop(UIElementPtr element);

	static void setBottom(UIElementPtr element, float bottom);
	static float getBottom(UIElementPtr element);

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;
};

}