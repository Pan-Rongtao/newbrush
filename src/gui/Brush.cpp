#include "gui/Brush.h"

using namespace nb;
using namespace nb::gui;

//class Brush
Brush::Brush()
	: Opacity([&](float v) { set(OpacityProperty(), v); }, [&]()->float & {return get<float>(OpacityProperty()); })
{
}

DependencyProperty Brush::OpacityProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
	return dp;
}

//class SolidColorBrush
SolidColorBrush::SolidColorBrush()
	: SolidColorBrush(nb::Color())
{
}

SolidColorBrush::SolidColorBrush(const nb::Color &color)
	: Color([&](nb::Color v){ set(ColorProperty(), v); }, [&]()->nb::Color & {return get<nb::Color>(ColorProperty()); })
{
	Color = color;
}

DependencyProperty SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color", nb::Color());
	return dp;
}

//class ImageBrush
ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}
#include "media/Bitmap.h"
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
