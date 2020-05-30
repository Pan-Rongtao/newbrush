#pragma once
#include "newbrush/media/Brush.h"

namespace nb {

class NB_API SolidColorBrush : public Brush
{
public:
	SolidColorBrush();
	explicit SolidColorBrush(const nb::Color &color);

	static DependencyPropertyPtr ColorProperty();	//—’…´“¿¿µ Ù–‘

};

}