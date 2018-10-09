#include "media/GifReader.h"
#include "GifReader_Internal.h"

using namespace nb::core;
using namespace nb::media;

GifReader::GifReader()
: m_internal(NULL)
{
	m_internal = new GifReader_Internal();
}

GifReader::~GifReader()
{
	delete m_internal;
}

bool GifReader::open(const String &path)
{
	return m_internal->open(path);
}

void GifReader::close()
{
	return m_internal->close();
}

bool GifReader::hasData() const
{
	return m_internal->hasData();
}

int GifReader::frameCount() const
{
	return m_internal->frameCount();
}

Bitmap GifReader::frame(int index) const
{
	return m_internal->frame(index);
}
