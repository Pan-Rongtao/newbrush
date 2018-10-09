#include "gui/ImageSource.h"
#include "gles/Texture.h"

using namespace nb::media;
using namespace nb::gui;
using namespace nb::gl;

ImageSource::ImageSource()
{
}

ImageSource::ImageSource(const std::string &uri)
{
	load(uri);
}

void ImageSource::load(const std::string &uri)
{
	m_bm = std::make_shared<Bitmap>(uri.data());
}