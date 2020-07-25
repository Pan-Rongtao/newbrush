#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/core/media/Media.h"
#include "newbrush/core/media/Pen.h"

namespace nb{

class NB_API Shape : public UIElement
{
	RTTR_ENABLE(UIElement)
public:
	static DependencyPropertyPtr FillProperty();				//填充画刷的依赖属性(BrushPtr)
	static DependencyPropertyPtr StrokeProperty();				//轮廓画刷的依赖属性(BrushPtr)
	static DependencyPropertyPtr StrokeThicknessProperty();		//轮廓宽度的依赖属性(float)
	static DependencyPropertyPtr StrokeStartLineCapProperty();	//轮廓线条的起点笔帽样式的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeEndLineCapProperty();	//轮廓线条的终点笔帽样式的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeDashArrayProperty();		//虚线的间隙的依赖属性(std::vector<float>)
	static DependencyPropertyPtr StrokeDashOffsetProperty();	//虚线开始的偏移的依赖属性(float)
	static DependencyPropertyPtr StrokeDashCapProperty();		//笔画帽的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeLineJoinProperty();		//顶点联接样式的依赖属性(PenLineJoinE)
	static DependencyPropertyPtr StretchProperty();				//伸缩方式的依赖属性(StretchE)
	
protected:
	Shape() = default;

	PenPtr getPen();

private:
	static void onPenChanged(DependencyObject *d, const DependencyPropertyChangedEventArgs &e);

	PenPtr	m_pen;
};

}