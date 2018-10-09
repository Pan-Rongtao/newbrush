#include "media/ImageSources.h"
#include "ImageSources_Internal.h"

using namespace nb::core;
using namespace nb::media;

ImageSources::ImageSources()
{
	m_Internal = new ImageSources_Internal();
}

ImageSources::~ImageSources()
{
	delete m_Internal;
}

void ImageSources::pushBack(const String &source)
{
	m_Internal->pushBack(source);
}

void ImageSources::insert(int index, const String &source)
{
	m_Internal->insert(index, source);
}

void ImageSources::remove(int index)
{
	m_Internal->remove(index);
}

void ImageSources::clear()
{
	m_Internal->clear();
}

int ImageSources::count() const
{
	return m_Internal->count();
}

const String &ImageSources::operator [] (int index) const
{
	return m_Internal->operator [](index);
}

void ImageSources::get(std::vector<String> &ret) const
{
	m_Internal->get(ret);
}

void ImageSources::set(const std::vector<String> &sources)
{
	m_Internal->set(sources);
}
