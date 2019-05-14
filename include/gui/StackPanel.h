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
	nb::core::Property_rw<OrientationE>		Orientation;
	nb::core::Property_r<double>			ExtentWidth;
	nb::core::Property_r<double>			ExtentHeight;
	nb::core::Property_r<double>			HorizontalOffset;
	nb::core::Property_r<double>			VerticalOffset;
	nb::core::Property_r<double>			ViewportWidth;
	nb::core::Property_r<double>			ViewportHeight;
	//nb::core::Property_rw<Scrollview>		ScrollOwner;
	//nb::core::Property_rw<bool>			CanHorizontallyScroll;
	//nb::core::Property_rw<bool>			CanVerticallyScroll;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	double									m_extentWidth;
	double									m_extentHeight;
	double									m_horizontalOffset;
	double									m_verticalOffset;
	double									m_viewportWidth;
	double									m_viewportHeight;
};

}}
