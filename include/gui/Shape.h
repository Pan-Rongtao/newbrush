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
	nb::core::Property_rw<std::shared_ptr<Brush>>		Fill;
	nb::core::Property_rw<nb::gui::StretchE>			Stretch;
	nb::core::Property_rw<std::shared_ptr<Brush>>		Stroke;
	nb::core::Property_rw<PenLineCapE>					StrokeDashCap;
	nb::core::Property_rw<PenLineJoinE>					StrokeLineJoin;
	nb::core::Property_rw<Thickness>					StrokeThickness;

protected:
	Shape();

};

}}