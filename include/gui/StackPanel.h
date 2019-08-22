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

	Property_rw<OrientationE>	Orientation;				//方向
	Property_r<float>			ExtentWidth;				//外部宽
	Property_r<float>			ExtentHeight;				//外部高
	Property_r<float>			HorizontalOffset;			//横向偏移量
	Property_r<float>			VerticalOffset;				//纵向偏移量
	Property_r<float>			ViewportWidth;				//视口宽
	Property_r<float>			ViewportHeight;				//视口高
	//Property_rw<Scrollview>	ScrollOwner;
	//Property_rw<bool>			CanHorizontallyScroll;
	//Property_rw<bool>			CanVerticallyScroll;

	static DependencyProperty	OrientationProperty();		//方向的依赖属性
	static DependencyProperty	ExtentWidthProperty();		//外部宽的依赖属性
	static DependencyProperty	ExtentHeightProperty();		//外部高的依赖属性
	static DependencyProperty	HorizontalOffsetProperty();	//横向偏移量的依赖属性
	static DependencyProperty	VerticalOffsetProperty();	//纵向偏移量的依赖属性
	static DependencyProperty	ViewportWidthProperty();	//视口宽的依赖属性
	static DependencyProperty	ViewportHeightProperty();	//视口高的依赖属性

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

}}
