#include "ImageSources_Internal.h"

using namespace nb::core;
using namespace nb::media;

void ImageSources_Internal::pushBack(const String &source)
{
	m_Sources.push_back(source);
}

void ImageSources_Internal::insert(int index, const String &source)
{
	m_Sources.insert(m_Sources.begin() + index, source);
}

void ImageSources_Internal::remove(int index)
{
	if(index < 0 || index >= (int)m_Sources.size())
		NB_THROW_EXCEPTION("out of index");

	m_Sources.erase(m_Sources.begin() + index);
}

void ImageSources_Internal::clear()
{
	m_Sources.clear();
}

int ImageSources_Internal::count() const
{
	return (int)m_Sources.size();
}

const String &ImageSources_Internal::operator [] (int index) const
{
	return m_Sources[index];
}

void ImageSources_Internal::set(const std::vector<String> &sources)
{
	m_Sources = sources;
}

void ImageSources_Internal::get(std::vector<String> &ret) const
{
	ret = m_Sources;
}