#include "gui/Brush.h"

using namespace nb::core;
using namespace nb::gui;

//class Brush
Brush::Brush()
	: Opacity(1.0)
{
}

Brush::Brush(double opacity)
	: Opacity(opacity)
{
}

Brush::~Brush()
{
}

//class SolidColorBrush
SolidColorBrush::SolidColorBrush()
	: Color(Color::black())
{
}

SolidColorBrush::SolidColorBrush(const nb::core::Color &color)
	: Color(color)
{
}

SolidColorBrush::~SolidColorBrush()
{
}

//class ImageBrush
ImageBrush::ImageBrush()
{
}

ImageBrush::ImageBrush(const std::shared_ptr<nb::gui::ImageSource> &imgSource)
	: ImageSource(imgSource)
{
}

ImageBrush::~ImageBrush()
{
}
