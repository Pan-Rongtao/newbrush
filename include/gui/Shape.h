#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"

namespace nb{ namespace gui{

//笔帽样式
enum class PenLineCapE
{
	Flat,		//没有笔帽
	Round,		//圆形笔帽
	Square,		//矩形笔帽
	Triangle,	//三角形笔帽
};

//联接样式
enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};

//形状类
class NB_API Shape : public UIElement
{
public:
	Property_rw<shared_ptr<Brush>>	Fill;						//填充画刷（仅封闭形状如rectangle、eclipse、polygon生效，line等不生效）
	Property_rw<shared_ptr<Brush>>	Stroke;						//轮廓画刷
	Property_rw<float>				StrokeThickness;			//轮廓宽度
	Property_rw<PenLineCapE>		StrokeStartLineCap;			//轮廓线条的起点笔帽样式（仅适用于Line、Polyline，其余封闭形状不生效）
	Property_rw<PenLineCapE>		StrokeEndLineCap;			//轮廓线条的终点笔帽样式（仅适用于Line、Polyline，其余封闭形状不生效）
	Property_rw<std::vector<float>>	StrokeDashArray;			//虚线的间隙占位，单位为StrokeThickness，比如{1, 2}，表示虚线1，间隙2，并以此循环至长度末
	Property_rw<float>				StrokeDashOffset;			//虚线开始的偏移（负值为左偏，正值为右偏）
	Property_rw<PenLineCapE>		StrokeDashCap;				//虚线两端的笔帽样式（仅适用于Line、Polyline，其余封闭形状不生效）
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

	std::shared_ptr<nb::gl::RenderObject>	m_fillObj;
	std::shared_ptr<nb::gl::RenderObject>	m_strokeObj;
};

//线
class NB_API Line : public Shape
{
public:
	Line();
	virtual ~Line() = default;

	Property_rw<float>			X1;				//X1
	Property_rw<float>			X2;				//X2
	Property_rw<float>			Y1;				//Y1
	Property_rw<float>			Y2;				//Y2
	static DependencyProperty	X1Property();	//X1的依赖属性
	static DependencyProperty	X2Property();	//X2的依赖属性
	static DependencyProperty	Y1Property();	//Y1的依赖属性
	static DependencyProperty	Y2Property();	//Y2的依赖属性

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

//多线段
class NB_API Polyline : public Shape
{
public:
	Polyline();
	virtual ~Polyline() = default;

	Property_rw<std::vector<Point>>	Points;				//点集合
	static DependencyProperty		PointsProperty();	//点集合的依赖属性

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

//多边形
class NB_API Polygon : public Shape
{
public:
	Polygon();
	virtual ~Polygon() = default;

	Property_rw<std::vector<Point>>	Points;				//点集合
	static DependencyProperty		PointsProperty();	//点集合的依赖属性

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

};

//椭圆
class NB_API Ellipse : public Shape
{
public:
	Ellipse();

	virtual void onRender(std::shared_ptr<nb::gl::Context> drawContext) override;

protected:
	virtual Size measureOverride(const Size &availableSize) override;
	virtual Size arrangeOverride(const Size &finalSize) override;

private:
	void onPropertyChanged(const PropertyChangedArgs & args);
};

}}