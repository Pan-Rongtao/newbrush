#pragma once
#include "newbrush/media/Brush.h"

namespace nb {

class NB_API ImageBrush : public Brush
{
public:
	ImageBrush();
	explicit ImageBrush(std::shared_ptr<ImageSource> imgSource);

	static DependencyPropertyPtr SourceProperty();	//‘¥“¿¿µ Ù–‘
};


}