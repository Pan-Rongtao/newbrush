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
}

const DependencyProperty Brush::OpacityProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Brush, float>("Opacity", 1.0f);
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

const DependencyProperty SolidColorBrush::ColorProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Brush, nb::Color>("Color", nb::Color());
	return dp;
}

//class ImageBrush
ImageBrush::ImageBrush()
	: ImageBrush(nullptr)
{
}

ImageBrush::ImageBrush(const std::shared_ptr<ImageSource> &imgSource)
	: Source([&](std::shared_ptr<ImageSource> &v) {set(SourceProperty(), imgSource); }, [&]() {return get<std::shared_ptr<ImageSource>>(SourceProperty()); })
{
	Source = imgSource;
}

const DependencyProperty nb::gui::ImageBrush::SourceProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", nullptr);
	return dp;
}
