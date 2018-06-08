#include "media/ExifReader.h"
#include "ExifReader_Internal.h"

using nb::Media::ExifReader;

ExifReader::ExifReader()
: m_internal(NULL)
{
	m_internal = new ExifReader_Internal();
}

ExifReader::ExifReader(const nb::System::String &fileName)
: m_internal(NULL)
{
	m_internal = new ExifReader_Internal();
	Open(fileName);
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

void ExifReader::Open(const nb::System::String &fileName)
{
	m_internal->Open(fileName);
}

int ExifReader::GetWidth() const
{
	return m_internal->GetWidth();
}

int ExifReader::GetHeight() const
{
	return m_internal->GetHeight();
}

void ExifReader::GetThumbnailsProperties(std::vector<ThumbnailProperties> &results) const
{
	m_internal->GetThumbnailsProperties(results);
}

void ExifReader::GetThumbnails(std::vector<nb::Media::Bitmap> &results) const
{
	m_internal->GetThumbnails(results);
}
