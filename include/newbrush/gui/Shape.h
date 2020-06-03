#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Stretch.h"
#include "newbrush/media/Media.h"

namespace nb{
class Brush;
class RenderObject;

class NB_API Shape : public UIElement
{
	RTTR_ENABLE(UIElement)
	NB_OBJECT
public:
	static DependencyPropertyPtr FillProperty();				//填充画刷的依赖属性(std::shared_ptr<Brush>)
	static DependencyPropertyPtr StrokeProperty();				//轮廓画刷的依赖属性(std::shared_ptr<Brush>)
	static DependencyPropertyPtr StrokeThicknessProperty();	//轮廓宽度的依赖属性(float)
	static DependencyPropertyPtr StrokeStartLineCapProperty();	//轮廓线条的起点笔帽样式的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeEndLineCapProperty();	//轮廓线条的终点笔帽样式的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeDashArrayProperty();	//虚线的间隙的依赖属性(std::vector<float>)
	static DependencyPropertyPtr StrokeDashOffsetProperty();	//虚线开始的偏移的依赖属性(float)
	static DependencyPropertyPtr StrokeDashCapProperty();		//笔画帽的依赖属性(PenLineCapE)
	static DependencyPropertyPtr StrokeLineJoinProperty();		//顶点联接样式的依赖属性(PenLineJoinE)
	static DependencyPropertyPtr StretchProperty();			//伸缩方式的依赖属性(StretchE)
	
	std::shared_ptr<RenderObject> renderObject();

protected:
	Shape();
	void updateMeterial(std::shared_ptr<nb::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<RenderObject>	m_fillObject;
	std::shared_ptr<RenderObject>	m_strokeObject;
};

}