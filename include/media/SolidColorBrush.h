#pragma once
#include "../media/Brush.h"

namespace nb {

class NB_API SolidColorBrush : public Brush
{
public:
	SolidColorBrush();
	explicit SolidColorBrush(const nb::Color &color);

	static DependencyProperty	ColorProperty();	//—’…´“¿¿µ Ù–‘

};

}