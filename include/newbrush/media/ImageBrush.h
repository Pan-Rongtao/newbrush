#pragma once
#include "newbrush/media/Brush.h"

namespace nb {

class ImageSource;
using ImageSourcePtr = std::shared_ptr<ImageSource>;
class NB_API ImageBrush : public Brush
{
public:
	ImageBrush();
	explicit ImageBrush(ImageSourcePtr imgSource);

	static DependencyPropertyPtr SourceProperty();	//‘¥“¿¿µ Ù–‘
};


}