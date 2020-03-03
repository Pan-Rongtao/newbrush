#include "newbrush/media/ImageBrush.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
{
	auto bm = imgSource->getValue<std::shared_ptr<Bitmap>>(ImageSource::BmProperty());
	//由于img->Bm()使用的是std::shared，在执行Source =时，将调用ImageBrush::SourceProperty()中的std::make_shared<ImageSource>()，将bm重置为null
	//使得最终执行Source = imgSource后的bm为null，该问题目前无解，暂时用保存bm副本的方式
	auto bmx = std::make_shared<Bitmap>(*bm);
	setValue(SourceProperty(), imgSource);
	imgSource->setValue(ImageSource::BmProperty(), bmx);
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", std::make_shared<ImageSource>());
	return dp;
}
