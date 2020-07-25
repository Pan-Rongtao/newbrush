#pragma once
#include "newbrush/core/media/Brush.h"
#include "newbrush/core/media/ImageSource.h"

namespace nb {

class NB_API ImageBrush : public Brush
{
public:
	ImageBrush();
	explicit ImageBrush(ImageSourcePtr imgSource);

	static DependencyPropertyPtr SourceProperty();	//‘¥“¿¿µ Ù–‘
};

using ImageBrushPtr = std::shared_ptr<ImageBrush>;
}