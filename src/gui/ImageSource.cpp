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

double nb::gui::ImageSource::width() const
{
	return Bm()->width();
}

double nb::gui::ImageSource::heigth() const
{
	return Bm()->height();
}
