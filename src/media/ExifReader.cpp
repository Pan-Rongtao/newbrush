#include "media/ExifReader.h"
#include "ExifReader_Internal.h"

using namespace nb::core;
using namespace nb::media;

ExifReader::ExifReader()
: m_internal(nullptr)
{
	m_internal = new ExifReader_Internal();
}

ExifReader::ExifReader(const String &fileName)
: m_internal(nullptr)
{
	m_internal = new ExifReader_Internal();
	open(fileName);
}

ExifReader::ExifReader(const ExifReader &other)
{
	m_internal = new ExifReader_Internal(*(other.m_internal));
}

void ExifReader::operator = (const ExifReader &other)
{
	delete m_internal;
	m_internal = new ExifReader_Internal(*(other.m_internal));
}

ExifReader::~ExifReader()
{
	delete m_internal;
}

void ExifReader::open(const String &fileName)
{
	m_internal->open(fileName);
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
