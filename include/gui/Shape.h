#pragma once
#include "../gui/UIElement.h"
#include "../gui/Stretch.h"
#include "../media/Media.h"

namespace nb{
class Brush;
namespace gui{

using nb::media::PenLineCapE;
using nb::media::PenLineJoinE;
class NB_API Shape : public UIElement
{
public:
	Property_rw<std::shared_ptr<Brush>>	Fill;						//填充画刷（仅封闭形状如rectangle、eclipse、polygon生效，line等不生效）
	Property_rw<std::shared_ptr<Brush>>	Stroke;						//轮廓画刷
	Property_rw<float>				StrokeThickness;			//轮廓宽度
	Property_rw<PenLineCapE>		StrokeStartLineCap;			//轮廓线条的起点笔帽样式（仅适用于Line、Polyline，其余封闭形状不生效）
	Property_rw<PenLineCapE>		StrokeEndLineCap;			//轮廓线条的终点笔帽样式（仅适用于Line、Polyline，其余封闭形状不生效）
	Property_rw<std::vector<float>>	StrokeDashArray;			//虚线的间隙占位，单位为StrokeThickness，比如{1, 2}，表示虚线1，间隙2，并以此循环至长度末
	Property_rw<float>				StrokeDashOffset;			//虚线开始的偏移（负值为左偏，正值为右偏）
	Property_rw<PenLineCapE>		StrokeDashCap;				//虚线两端的笔帽样式
	Property_rw<PenLineJoinE>		StrokeLineJoin;				//顶点联接样式
	Property_rw<StretchE>			Stretch;					//伸缩方式
	
	static DependencyProperty		FillProperty();				//填充画刷的依赖属性
	static DependencyProperty		StrokeProperty();			//轮廓画刷的依赖属性
	static DependencyProperty		StrokeThicknessProperty();	//轮廓宽度的依赖属性
	static DependencyProperty		StrokeStartLineCapProperty();//轮廓线条的起点笔帽样式的依赖属性
	static DependencyProperty		StrokeEndLineCapProperty();	//轮廓线条的终点笔帽样式的依赖属性
	static DependencyProperty		StrokeDashArrayProperty();	//虚线的间隙的依赖属性
	static DependencyProperty		StrokeDashOffsetProperty();	//虚线开始的偏移的依赖属性
	static DependencyProperty		StrokeDashCapProperty();	//笔画帽的依赖属性
	static DependencyProperty		StrokeLineJoinProperty();	//顶点联接样式的依赖属性
	static DependencyProperty		StretchProperty();			//伸缩方式的依赖属性

protected:
	Shape();
	void updateMeterial(std::shared_ptr<nb::RenderObject> ro, std::shared_ptr<Brush> brush);

	std::shared_ptr<RenderObject>	m_fillObject;
	std::shared_ptr<RenderObject>	m_strokeObject;
};

}}