#include "newbrush/core/media/ImageBrush.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(ImageSourcePtr imgSource)
{
	setValue(SourceProperty(), imgSource);
}

DependencyPropertyPtr ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<ImageBrush, ImageSourcePtr>("Source", nullptr);
	return dp;
}
