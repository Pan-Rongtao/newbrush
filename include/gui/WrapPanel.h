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
	virtual ~WrapPanel();

public:
	nb::core::Property_rw<Orientation>	Orientation;
	nb::core::Property_rw<double>		ItemWidth;
	nb::core::Property_rw<double>		ItemHeight;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) const;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) const;

};

}}
