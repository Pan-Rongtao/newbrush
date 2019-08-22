#include "gui/Brush.h"

using namespace nb;
using namespace nb::gui;

//class Brush
Brush::Brush()
	: Brush(1.0f)
{
}

Brush::Brush(float opacity)
	: Opacity([&](float v) { set(OpacityProperty(), v); }, [&]() {return get<float>(OpacityProperty()); })
{
	Opacity = opacity;
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
	: Color([&](nb::Color v){ set(ColorProperty(), v); }, [&](){return get<nb::Color>(ColorProperty()); })
{
	Color = color;
}

DependencyProperty SolidColorBrush::ColorProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color");
	return dp;
}

//class ImageBrush
ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(std::shared_ptr<ImageSource> imgSource)
	: Source([&](std::shared_ptr<ImageSource> &v) {set(SourceProperty(), imgSource); }, [&]() {return get<std::shared_ptr<ImageSource>>(SourceProperty()); })
{
	Source = imgSource;
}

DependencyProperty ImageBrush::SourceProperty()
{
	static auto dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source");
	return dp;
}
