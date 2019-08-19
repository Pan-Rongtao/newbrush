#include "gui/Brush.h"

using namespace nb::core;
using namespace nb::gui;

//class Brush
Brush::Brush()
	: Brush(1.0f)
{
}

Brush::Brush(float opacity)
	: Opacity(opacity)
{
	Opacity.notify([&](const float &_old, const float &_new) { setValue<float>(OpacityProperty(), _new); });
}

Brush::~Brush()
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
	: Color(color)
{
	Color.notify([&](const nb::core::Color &_old, const nb::core::Color &_new) { setValue<nb::core::Color>(ColorProperty(), _new); });
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
	: Source(imgSource)
{
	Source.notify([&](const std::shared_ptr<ImageSource> &_old, const std::shared_ptr<ImageSource> &_new) {setValue<std::shared_ptr<ImageSource>>(SourceProperty(), imgSource); });
}

const DependencyProperty nb::gui::ImageBrush::SourceProperty()
{
	static const DependencyProperty dp = DependencyProperty::registerDependency<Brush, std::shared_ptr<ImageSource>>("Source", nullptr);
	return dp;
}
