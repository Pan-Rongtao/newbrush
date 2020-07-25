/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 潘荣涛

 * 编写日期: 2018-9

 * 简要描述: 自动换行布局容器

			

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "newbrush/gui/panels/Panel.h"

namespace nb{

class NB_API WrapPanel : public Panel
{
	RTTR_ENABLE(Panel)
public:
	WrapPanel();
	virtual ~WrapPanel() = default;

	static DependencyPropertyPtr OrientationProperty();	//方向的依赖属性
	static DependencyPropertyPtr ItemWidthProperty();	//项宽的依赖属性
	static DependencyPropertyPtr ItemHeightProperty();	//项高的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}
