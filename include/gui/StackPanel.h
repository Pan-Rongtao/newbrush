/******************************************************************************

 * Copyright (c) 2016，德赛西威汽车电子有限公司

 * All rights reserved

 * 编写者: 潘荣涛

 * 编写日期: 2018-09

 * 简要描述: 堆栈容器


 * 修改记录:

 *****************************************************************************/
#pragma once
#include "../gui/Panel.h"

namespace nb{ namespace gui{

class NB_API StackPanel : public Panel
{
public:
	StackPanel();
	virtual ~StackPanel();

public:
	nb::core::Property_rw<Orientation>	Orientation1;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;
};

}}
