#include "gui/Brush.h"

using namespace nb::core;
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
	: SolidColorBrush(nb::core::Color())
{
}

SolidColorBrush::SolidColorBrush(const nb::core::Color &color)
	: Color([&](nb::core::Color v){ set(ColorProperty(), v); }, [&](){return get<nb::core::Color>(ColorProperty()); })
{
	Color = color;
}

const DependencyProperty SolidColorBrush::ColorProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Brush, nb::core::Color>("Color", nb::core::Color());
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
