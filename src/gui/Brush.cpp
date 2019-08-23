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

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
	: Source([&](shared_ptr<ImageSource> &v) {set(SourceProperty(), imgSource); }, [&]()->shared_ptr<ImageSource> & {return get<shared_ptr<ImageSource>>(SourceProperty()); })
{
	Source = imgSource;
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", std::make_shared<ImageSource>());
	return dp;
}
