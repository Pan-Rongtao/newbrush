#include "gui/ImageBrush.h"

using namespace nb::System;
using namespace nb::Media;
using namespace nb::gl::Gles;

ImageBrush::ImageBrush()
: m_Stretch(Origion)
{

}

ImageBrush::ImageBrush(const ImageSourcePtr &imgSource)
: m_Stretch(Origion)
{
	SetImageSource(imgSource);
}

ImageBrush::~ImageBrush()
{
}

void ImageBrush::SetImageSource(const ImageSourcePtr &imgSource)
{
	m_imgSource = imgSource;
}

const ImageSourcePtr &ImageBrush::GetImageSource() const
{
	return m_imgSource;
}

void ImageBrush::SetStretch(Stretch mode)
{
	m_Stretch = mode;
}

Stretch ImageBrush::GetStretch() const
{
	return m_Stretch;
}

Size ImageBrush::GetPixcelSize() const
{
	if(m_imgSource == NULL)
		return Size(0, 0);
	else
		return Size(m_imgSource->GetPixelWidth(), m_imgSource->GetPixcelHeight());
}
