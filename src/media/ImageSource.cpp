#include "newbrush/media/ImageSource.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageSource::ImageSource()
{
}

ImageSource::ImageSource(const std::string & uri)
{
	m_bm.load(uri);
}

float ImageSource::width() const
{
	return (float)m_bm.width();
}

float ImageSource::height() const
{
	return (float)m_bm.height();
}

const Bitmap &ImageSource::bitmap() const
{
	return m_bm;
}
