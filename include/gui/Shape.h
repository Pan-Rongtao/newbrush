#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"

namespace nb{ namespace gui{

enum class PenLineCapE
{
	Flat,
	Round,
	Square,
	Triangle,
};

enum class PenLineJoinE
{
	Beval,
	Miter,
	Round,
};

class NB_API Shape : public UIElement
{
public:
	Property_rw<shared_ptr<Brush>>		Fill;
	Property_rw<StretchE>				Stretch;
	Property_rw<shared_ptr<Brush>>		Stroke;
	Property_rw<PenLineCapE>			StrokeDashCap;
	Property_rw<PenLineJoinE>			StrokeLineJoin;
	Property_rw<Thickness>				StrokeThickness;
	
	static const DependencyProperty		FillProperty();
	static const DependencyProperty		StretchProperty();
	static const DependencyProperty		StrokeProperty();
	static const DependencyProperty		StrokeDashCapProperty();
	static const DependencyProperty		StrokeLineJoinProperty();
	static const DependencyProperty		StrokeThicknessProperty();

protected:
	Shape();

};

}}