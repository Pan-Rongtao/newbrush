#include "media/ImageSources.h"
#include "ImageSources_Internal.h"

using nb::System::String;
using nb::Media::ImageSources;

ImageSources::ImageSources()
{
	m_Internal = new ImageSources_Internal();
}

ImageSources::~ImageSources()
{
	delete m_Internal;
}

void ImageSources::PushBack(const nb::System::String &source)
{
	m_Internal->PushBack(source);
}

void ImageSources::Insert(int index, const nb::System::String &source)
{
	m_Internal->Insert(index, source);
}

void ImageSources::Remove(int index)
{
	m_Internal->Remove(index);
}

void ImageSources::Clear()
{
	m_Internal->Clear();
}

int ImageSources::GetCount() const
{
	return m_Internal->GetCount();
}

const nb::System::String &ImageSources::operator [] (int index) const
{
	return m_Internal->operator [](index);
}

void ImageSources::Get(std::vector<nb::System::String> &ret) const
{
	m_Internal->Get(ret);
}

void ImageSources::Set(const std::vector<nb::System::String> &sources)
{
	m_Internal->Set(sources);
}
