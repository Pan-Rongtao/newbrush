#include "gui/Brush.h"

using namespace nb::core;
using namespace nb::gui;

//class Brush
Brush::Brush()
	: Opacity(1.0)
{
}

Brush::Brush(float opacity)
	: Opacity(opacity)
{
}

Brush::~Brush()
{
}

//class SolidColorBrush
SolidColorBrush::SolidColorBrush()
	: Color(Colors::black())
{
}

SolidColorBrush::SolidColorBrush(const nb::core::Color &color)
	: Color(color)
{
}

//class ImageBrush
ImageBrush::ImageBrush()
{
}

ImageBrush::ImageBrush(const std::shared_ptr<nb::gui::ImageSource> &imgSource)
	: Source(imgSource)
{
}
