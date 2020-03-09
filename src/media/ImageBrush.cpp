#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
{
	setValue(SourceProperty(), imgSource);
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", nullptr);
	return dp;
}
