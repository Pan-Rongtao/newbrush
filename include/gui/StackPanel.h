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
	nb::core::Property_r<float>				ExtentWidth;
	nb::core::Property_r<float>				ExtentHeight;
	nb::core::Property_r<float>				HorizontalOffset;
	nb::core::Property_r<float>				VerticalOffset;
	nb::core::Property_r<float>				ViewportWidth;
	nb::core::Property_r<float>				ViewportHeight;
	//nb::core::Property_rw<Scrollview>		ScrollOwner;
	//nb::core::Property_rw<bool>			CanHorizontallyScroll;
	//nb::core::Property_rw<bool>			CanVerticallyScroll;

protected:
	virtual nb::core::Size measureOverride(const nb::core::Size &availableSize) override;
	virtual nb::core::Size arrangeOverride(const nb::core::Size &finalSize) override;

private:
	float									m_extentWidth;
	float									m_extentHeight;
	float									m_horizontalOffset;
	float									m_verticalOffset;
	float									m_viewportWidth;
	float									m_viewportHeight;
};

}}
