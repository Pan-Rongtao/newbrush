#include "media/ExifReader.h"
#include "ExifReader_Internal.h"

using namespace nb::core;
using namespace nb::media;

ExifReader::ExifReader()
	: m_internal(nullptr)
{
	m_internal = new ExifReader_Internal();
}

ExifReader::~ExifReader()
{
	delete m_internal;
}

void ExifReader::open(const std::string &path)
{
	m_internal->open(path);
}

int ExifReader::width() const
{
	return m_internal->width();
}

int ExifReader::height() const
{
	return m_internal->height();
}

void ExifReader::getThumbnailsProperties(std::vector<ThumbnailProperties> &results) const
{
	m_internal->getThumbnailsProperties(results);
}

void ExifReader::getThumbnails(std::vector<Bitmap> &results) const
{
	m_internal->getThumbnails(results);
}
