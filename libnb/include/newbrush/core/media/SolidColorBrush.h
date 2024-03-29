#pragma once
#include "newbrush/core/media/Brush.h"
#include "newbrush/core/media/Color.h"

namespace nb {

class NB_API SolidColorBrush : public Brush
{
	RTTR_ENABLE(Brush)
public:
	SolidColorBrush();
	explicit SolidColorBrush(const Color &color);

	static DependencyPropertyPtr ColorProperty();	//��ɫ��������

};

}