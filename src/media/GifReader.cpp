#include "media/GifReader.h"
#include "GifReader_Internal.h"

using nb::Media::GifReader;

GifReader::GifReader()
: m_internal(NULL)
{
	m_internal = new GifReader_Internal();
}

GifReader::~GifReader()
{
	delete m_internal;
}

bool GifReader::Open(const nb::System::String &path)
{
	return m_internal->Open(path);
}

void GifReader::Close()
{
	return m_internal->Close();
}

bool GifReader::HasData() const
{
	return m_internal->HasData();
}

int GifReader::GetFrameCount() const
{
	return m_internal->GetFrameCount();
}

nb::Media::Bitmap GifReader::GetFrame(int index) const
{
	return m_internal->GetFrame(index);
}
