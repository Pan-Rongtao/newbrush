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
	Property_rw<shared_ptr<Brush>>	Fill;						//ÃÓ≥‰
	Property_rw<StretchE>			Stretch;					//…ÏÀı∑Ω Ω
	Property_rw<shared_ptr<Brush>>	Stroke;						//± ª≠
	Property_rw<PenLineCapE>		StrokeDashCap;				//± ª≠√±
	Property_rw<PenLineJoinE>		StrokeLineJoin;				//
	Property_rw<Thickness>			StrokeThickness;			//ª≠± ∫Ò∂»
	
	static DependencyProperty		FillProperty();				//ÃÓ≥‰µƒ“¿¿µ Ù–‘
	static DependencyProperty		StretchProperty();			//…ÏÀı∑Ω Ωµƒ“¿¿µ Ù–‘
	static DependencyProperty		StrokeProperty();			//± ª≠µƒ“¿¿µ Ù–‘
	static DependencyProperty		StrokeDashCapProperty();	//± ª≠√±µƒ“¿¿µ Ù–‘
	static DependencyProperty		StrokeLineJoinProperty();	//
	static DependencyProperty		StrokeThicknessProperty();	//± ª≠∫Ò∂»µƒ“¿¿µ Ù–‘

protected:
	Shape();

};

}}