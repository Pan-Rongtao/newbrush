/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 潘荣涛

 * 编写日期: 2018-09

 * 简要描述: 堆栈容器


 * 修改记录:

 *****************************************************************************/
#pragma once
#include "newbrush/gui/Panel.h"

namespace nb{

class NB_API StackPanel : public Panel
{
	RTTR_ENABLE(Panel)
public:
	StackPanel();
	virtual ~StackPanel() = default;
	
	static DependencyPropertyPtr OrientationProperty();		//方向的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	float	m_extentWidth;		//外部宽的依赖属性
	float	ExtentHeight;		//外部高的依赖属性
	float	HorizontalOffset;	//横向偏移量的依赖属性
	float	VerticalOffset;		//纵向偏移量的依赖属性
	float	ViewportWidth;		//视口宽的依赖属性
	float	ViewportHeight;		//视口高的依赖属性
};

}
