#include "ImageSources_Internal.h"

using nb::Media::ImageSources_Internal;

void ImageSources_Internal::PushBack(const nb::System::String &source)
{
	m_Sources.push_back(source);
}

void ImageSources_Internal::Insert(int index, const nb::System::String &source)
{
	m_Sources.insert(m_Sources.begin() + index, source);
}

void ImageSources_Internal::Remove(int index)
{
	if(index < 0 || index >= (int)m_Sources.size())
		NB_THROW_EXCEPTION("out of index");

	m_Sources.erase(m_Sources.begin() + index);
}

void ImageSources_Internal::Clear()
{
	m_Sources.clear();
}

int ImageSources_Internal::GetCount() const
{
	return (int)m_Sources.size();
}

const nb::System::String &ImageSources_Internal::operator [] (int index) const
{
	return m_Sources[index];
}

void ImageSources_Internal::Set(const std::vector<nb::System::String> &sources)
{
	m_Sources = sources;
}

void ImageSources_Internal::Get(std::vector<nb::System::String> &ret) const
{
	ret = m_Sources;
}