#pragma once
#include "newbrush/media/Brush.h"
#include "newbrush/media/Color.h"

namespace nb {

class NB_API SolidColorBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	SolidColorBrush();
	explicit SolidColorBrush(const Color &color);

	static DependencyPropertyPtr ColorProperty();	//—’…´“¿¿µ Ù–‘

};

}