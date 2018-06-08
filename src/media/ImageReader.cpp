#include "media/ImageReader.h"
#include "core/Exception.h"
#include "media/ExifReader.h"
#include "system/System.h"

using nb::Media::ImageReader;
using nb::Media::Bitmap;
using nb::Media::ExifReader;
using nb::System::SizeI;

ImageReader::ImageReader()
: m_ScaleSize(160, 160)
{

}

ImageReader::ImageReader(const nb::System::SizeI &size)
: m_ScaleSize(size)
{
	if(size.Width() < 0 || size.Height() < 0)
		NB_THROW_EXCEPTION("size illegal.");
}

ImageReader::~ImageReader()
{

}

void ImageReader::SetScaledSize(const nb::System::SizeI &size)
{
	m_ScaleSize = size;
}

nb::System::SizeI ImageReader::GetScaledSize() const
{
	return m_ScaleSize;
}

void ImageReader::Read(const nb::System::String &path, nb::Media::Bitmap *pBm)
{
	ExifReader exif;
	try{
		exif.Open(path);
	}
	catch(nb::Core::ExceptionPtr &e){
		(void)e;
	}
	std::vector<ExifReader::ThumbnailProperties> thumbsProperties;
	exif.GetThumbnailsProperties(thumbsProperties);
	nb::System::SizeI maxThumb(0, 0);
	for(int i = 0; i != thumbsProperties.size(); ++i)
	{
		nb::System::SizeI szOne(thumbsProperties[i].Width, thumbsProperties[i].Height);
		if(szOne.Width() > maxThumb.GetWidth() && szOne.Height() > maxThumb.GetHeight())
			maxThumb = szOne;
	}
	//如果需要伸缩的尺寸大于最大取缩略图尺寸100，直接读原图
	if(thumbsProperties.empty() || (GetScaledSize().GetWidth() - maxThumb.GetWidth() > 100 || GetScaledSize().GetHeight() - maxThumb.GetHeight() > 100))
	{
		pBm->LoadFile(path);
//		*pBm = pBm->Scale(GetScaledSize());
	}
	else
	{
		std::vector<nb::Media::Bitmap> thumbs;
		exif.GetThumbnails(thumbs);
		*pBm = thumbs[0];
//		*pBm = pBm->Scale(GetScaledSize());
	}
	*pBm = pBm->Scale(GetScaledSize());
}

void ImageReader::ReadUniform(const nb::System::String &path, nb::Media::Bitmap *pBm, nb::System::SizeI &OriginalSize)
{
	ExifReader exif;
	try{
		exif.Open(path);
	}
	catch(nb::Core::ExceptionPtr &e){
		(void)e;
	}
	OriginalSize = nb::System::SizeI(exif.GetWidth(), exif.GetHeight());
	std::vector<ExifReader::ThumbnailProperties> thumbsProperties;
	exif.GetThumbnailsProperties(thumbsProperties);
	nb::System::SizeI maxThumb(0, 0);
	for(int i = 0; i != thumbsProperties.size(); ++i)
	{
		nb::System::SizeI szOne(thumbsProperties[i].Width, thumbsProperties[i].Height);
		if(szOne.Width() > maxThumb.GetWidth() && szOne.Height() > maxThumb.GetHeight())
			maxThumb = szOne;
	}
	//如果需要伸缩的尺寸大于最大取缩略图尺寸100，直接读原图
	if(thumbsProperties.empty() || (GetScaledSize().GetWidth() - maxThumb.GetWidth() > 100 || GetScaledSize().GetHeight() - maxThumb.GetHeight() > 100))
	{
		int nSourceSize = exif.GetWidth() * exif.GetHeight();
		int nDestSize = m_ScaleSize.GetWidth() * m_ScaleSize.GetHeight();
		int nJpegNarrow = 8;
		for(int i = 1; i <= 8; i = i << 1)
		{
			if((nSourceSize >> i) <= nDestSize)
			{
				nJpegNarrow = i;
				break;
			}
		}
		//取最近的nJpegNarrow
		if(nJpegNarrow != 1 && (nb::System::Abs(nSourceSize >> nJpegNarrow) - nDestSize) > (nb::System::Abs((nSourceSize >> (nJpegNarrow >> 1)) - nDestSize)))
		{
			nJpegNarrow = (nJpegNarrow >> 1);
		}
		pBm->LoadFileNarrowed(path, nJpegNarrow);
	}
	else
	{
		std::vector<nb::Media::Bitmap> thumbs;
		exif.GetThumbnails(thumbs);
		*pBm = thumbs[0];
	}

	SizeI szFinal;
	float pixcelRatio = (float)(pBm->GetWidth()) / pBm->GetHeight();
	float containerRatio = (float)(m_ScaleSize.Width()) / m_ScaleSize.Height();
	if(pixcelRatio < containerRatio)
	{
		szFinal.Height() = m_ScaleSize.Height();
		szFinal.Width() = (int)(szFinal.Height() * pixcelRatio);
	}
	else
	{
		szFinal.Width() = m_ScaleSize.Width();
		szFinal.Height() = (int)(szFinal.Width() / pixcelRatio);
	}
	//使之四像素对齐
	szFinal.Width() = szFinal.Width() / 4 * 4;
	szFinal.Height() = szFinal.Height() / 4 * 4;
	*pBm = pBm->Scale(szFinal);
}
