/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 潘荣涛

 * 编写日期: 2018-9

 * 简要描述: 自动换行布局容器

			

 * 修改记录:

 *****************************************************************************/
#pragma once
#include "Panel.h"

namespace nb{ namespace gui{

class NB_API WrapPanel : public Panel
{
public:
	WrapPanel();
	virtual ~WrapPanel() = default;

	Property_rw<OrientationE>	Orientation;			//方向
	Property_rw<float>			ItemWidth;				//项宽
	Property_rw<float>			ItemHeight;				//项高
	static DependencyProperty	OrientationProperty();	//方向的依赖属性
	static DependencyProperty	ItemWidthProperty();	//项宽的依赖属性
	static DependencyProperty	ItemHeightProperty();	//项高的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
