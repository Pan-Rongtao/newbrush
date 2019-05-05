#include "media/TiffReader.h"
#include "TiffReader_Internal.h"

using namespace nb::core;
using namespace nb::media;

TiffReader::TiffReader()
: m_internal(nullptr)
{
	m_internal = new TiffReader_Internal();
}

TiffReader::~TiffReader()
{
	delete m_internal;
}

bool TiffReader::open(const std::string &path)
{
	return m_internal->open(path);
}

void TiffReader::close()
{
	return m_internal->close();
}

bool TiffReader::hasData() const
{
	return m_internal->hasData();
}

int TiffReader::frameCount() const
{
	return m_internal->frameCount();
}

Bitmap TiffReader::frame(int index) const
{
	return m_internal->frame(index);
}
