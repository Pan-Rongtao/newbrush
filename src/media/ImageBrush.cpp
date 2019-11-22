#include "media/ImageBrush.h"
#include "media/Bitmap.h"

using namespace nb;

ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
	: Source([&](shared_ptr<ImageSource> v) {set(SourceProperty(), v); }, [&]()->shared_ptr<ImageSource> & {return get<shared_ptr<ImageSource>>(SourceProperty()); })
{
	auto bm = imgSource->Bm();
	//由于img->Bm()使用的是std::shared，在执行Source =时，将调用ImageBrush::SourceProperty()中的std::make_shared<ImageSource>()，将bm重置为null
	//使得最终执行Source = imgSource后的bm为null，该问题目前无解，暂时用保存bm副本的方式
	auto bmx = std::make_shared<Bitmap>(*bm);
	Source = imgSource;
	imgSource->Bm() = bmx;
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", std::make_shared<ImageSource>());
	return dp;
}
