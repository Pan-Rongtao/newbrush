#include "newbrush/media/ImageSource.h"
#include "newbrush/media/Bitmap.h"

using namespace nb;

ImageSource::ImageSource()
	: m_width(0)
	, m_height(0)
	, m_channels(0)
{
}

ImageSource::ImageSource(const std::string & uri)
	: m_width(0)
	, m_height(0)
	, m_channels(0)
{
	Bitmap bm;
	bm.load(uri);
	m_stream.assign((const char *)bm.data(), bm.bytes());
	m_width = bm.width();
	m_height = bm.height();
	m_channels = bm.channels();
}

void ImageSource::load(const unsigned char *buffer, uint32_t bytes)
{
	Bitmap bm;
	bm.load(buffer, bytes);
	m_stream.assign((const char *)bm.data(), bm.bytes());
	m_width = bm.width();
	m_height = bm.height();
	m_channels = bm.channels();
}

const std::string &ImageSource::stream() const
{
	return m_stream;
}

int ImageSource::width() const
{
	return m_width;
}

int ImageSource::height() const
{
	return m_height;
}

int ImageSource::channels() const
{
	return m_channels;
}