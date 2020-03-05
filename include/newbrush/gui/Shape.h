#pragma once
#include "newbrush/gui/UIElement.h"
#include "newbrush/gui/Stretch.h"
#include "newbrush/media/Media.h"

namespace nb{
class Brush;
namespace gui{

using nb::media::PenLineCapE;
using nb::media::PenLineJoinE;
class NB_API Shape : public UIElement
{
public:
	static DependencyProperty FillProperty();				//填充画刷的依赖属性(std::shared_ptr<Brush>)
	static DependencyProperty StrokeProperty();				//轮廓画刷的依赖属性(std::shared_ptr<Brush>)
	static DependencyProperty StrokeThicknessProperty();	//轮廓宽度的依赖属性(float)
	static DependencyProperty StrokeStartLineCapProperty();	//轮廓线条的起点笔帽样式的依赖属性(PenLineCapE)
	static DependencyProperty StrokeEndLineCapProperty();	//轮廓线条的终点笔帽样式的依赖属性(PenLineCapE)
	static DependencyProperty StrokeDashArrayProperty();	//虚线的间隙的依赖属性(std::vector<float>)
	static DependencyProperty StrokeDashOffsetProperty();	//虚线开始的偏移的依赖属性(float)
	static DependencyProperty StrokeDashCapProperty();		//笔画帽的依赖属性(PenLineCapE)
	static DependencyProperty StrokeLineJoinProperty();		//顶点联接样式的依赖属性(PenLineJoinE)
	static DependencyProperty StretchProperty();			//伸缩方式的依赖属性(StretchE)

protected:
	Shape();
	void updateMeterial(std::shared_ptr<nb::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<RenderObject>	m_fillObject;
	std::shared_ptr<RenderObject>	m_strokeObject;
};

}}