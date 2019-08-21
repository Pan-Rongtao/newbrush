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
	virtual ~StackPanel() = default;

	Property_rw<OrientationE>			Orientation;
	Property_r<float>					ExtentWidth;
	Property_r<float>					ExtentHeight;
	Property_r<float>					HorizontalOffset;
	Property_r<float>					VerticalOffset;
	Property_r<float>					ViewportWidth;
	Property_r<float>					ViewportHeight;
	//Property_rw<Scrollview>			ScrollOwner;
	//Property_rw<bool>					CanHorizontallyScroll;
	//Property_rw<bool>					CanVerticallyScroll;

	static const DependencyProperty		OrientationProperty();
	static const DependencyProperty		ExtentWidthProperty();
	static const DependencyProperty		ExtentHeightProperty();
	static const DependencyProperty		HorizontalOffsetProperty();
	static const DependencyProperty		VerticalOffsetProperty();
	static const DependencyProperty		ViewportWidthProperty();
	static const DependencyProperty		ViewportHeightProperty();

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
