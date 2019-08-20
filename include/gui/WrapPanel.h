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

	nb::core::Property_rw<OrientationE>	Orientation;
	nb::core::Property_rw<float>		ItemWidth;
	nb::core::Property_rw<float>		ItemHeight;

	static const DependencyProperty		OrientationProperty();
	static const DependencyProperty		ItemWidthProperty();
	static const DependencyProperty		ItemHeightProperty();

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

};

}}
