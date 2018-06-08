#include "media/TiffReader.h"
#include "TiffReader_Internal.h"

using nb::Media::TiffReader;

TiffReader::TiffReader()
: m_internal(NULL)
{
	m_internal = new TiffReader_Internal();
}

TiffReader::~TiffReader()
{
	delete m_internal;
}

bool TiffReader::Open(const nb::System::String &path)
{
	return m_internal->Open(path);
}

void TiffReader::Close()
{
	return m_internal->Close();
}

bool TiffReader::HasData() const
{
	return m_internal->HasData();
}

int TiffReader::GetFrameCount() const
{
	return m_internal->GetFrameCount();
}

nb::Media::Bitmap TiffReader::GetFrame(int index) const
{
	return m_internal->GetFrame(index);
}
