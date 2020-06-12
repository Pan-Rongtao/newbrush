#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/ImageSource.h"
#include "newbrush/core/DependencyProperty.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
{
	setValue(SourceProperty(), imgSource);
}

DependencyPropertyPtr ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<ImageBrush, std::shared_ptr<ImageSource>>("Source", nullptr);
	return dp;
}
