#pragma once
#include "../gui/UIElement.h"
#include "../gui/Brush.h"
#include "../gui/Stretch.h"

namespace nb{ namespace gui{

enum PenLineCap
{
	PenLineCap_Flat,
	PenLineCap_Round,
	PenLineCap_Square,
	PenLineCap_Triangle,
};

enum PenLineJoin
{
	PenLineJoin_Beval,
	PenLineJoin_Miter,
	PenLineJoin_Round,
};

class NB_API Shape : public UIElement
{
public:
	nb::core::Property_rw<std::shared_ptr<Brush>>		Fill;
	nb::core::Property_rw<nb::gui::StretchE>			Stretch;
	nb::core::Property_rw<std::shared_ptr<Brush>>		Stroke;
	nb::core::Property_rw<PenLineCap>					StrokeDashCap;
	nb::core::Property_rw<PenLineJoin>					StrokeLineJoin;
	nb::core::Property_rw<Thickness>					StrokeThickness;

protected:
	Shape();

};

}}