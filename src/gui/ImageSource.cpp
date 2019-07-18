#include "gui/ImageSource.h"
#include "gles/Texture2D.h"
#include "core/Size.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gui;
using namespace nb::gl;

ImageSource::ImageSource()
	: Bm(std::make_shared<Bitmap>())
{
}

ImageSource::ImageSource(const std::string & uri)
	: Bm(std::make_shared<Bitmap>(uri))
{
}

float nb::gui::ImageSource::width() const
{
	return (float)Bm()->width();
}

float nb::gui::ImageSource::heigth() const
{
	return (float)Bm()->height();
}
