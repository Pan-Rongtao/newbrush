#include "media/ImageReader.h"
#include "media/ExifReader.h"

using namespace nb::core;
using namespace nb::media;

ImageReader::ImageReader()
	: m_ScaleSize(160, 160)
{

}

ImageReader::ImageReader(const SizeI &size)
	: m_ScaleSize(size)
{
	if(size.width() < 0 || size.height() < 0)
		NB_THROW_EXCEPTION(std::invalid_argument, "size illegal.");
}

ImageReader::~ImageReader()
{

}

void ImageReader::setScaledSize(const SizeI &size)
{
	m_ScaleSize = size;
}

SizeI ImageReader::scaledSize() const
{
	return m_ScaleSize;
}

void ImageReader::read(const std::string &path, Bitmap *pBm)
{
	ExifReader exif;
	try{
		exif.open(path.data());
	}
	catch(...){
	}
	std::vector<ExifReader::ThumbnailProperties> thumbsProperties;
	exif.getThumbnailsProperties(thumbsProperties);
	SizeI maxThumb(0, 0);
	for(int i = 0; i != thumbsProperties.size(); ++i)
	{
		SizeI szOne(thumbsProperties[i].Width, thumbsProperties[i].Height);
		if(szOne.width() > maxThumb.width() && szOne.height() > maxThumb.height())
			maxThumb = szOne;
	}
	//如果需要伸缩的尺寸大于最大取缩略图尺寸100，直接读原图
	if(thumbsProperties.empty() || (scaledSize().width() - maxThumb.width() > 100 || scaledSize().height() - maxThumb.height() > 100))
	{
		pBm->load(path);
//		*pBm = pBm->Scale(GetScaledSize());
	}
	else
	{
		std::vector<Bitmap> thumbs;
		exif.getThumbnails(thumbs);
		*pBm = thumbs[0];
//		*pBm = pBm->Scale(GetScaledSize());
	}
	*pBm = pBm->scale(m_ScaleSize.width(), m_ScaleSize.height());
}

void ImageReader::readUniform(const std::string &path, Bitmap *pBm, SizeI &OriginalSize)
{
	ExifReader exif;
	try{
		exif.open(path.data());
	}
	catch(...){
	}
	OriginalSize = SizeI(exif.width(), exif.height());
	std::vector<ExifReader::ThumbnailProperties> thumbsProperties;
	exif.getThumbnailsProperties(thumbsProperties);
	SizeI maxThumb(0, 0);
	for(int i = 0; i != thumbsProperties.size(); ++i)
	{
		SizeI szOne(thumbsProperties[i].Width, thumbsProperties[i].Height);
		if(szOne.width() > maxThumb.width() && szOne.height() > maxThumb.height())
			maxThumb = szOne;
	}
	//如果需要伸缩的尺寸大于最大取缩略图尺寸100，直接读原图
	if(thumbsProperties.empty() || (scaledSize().width() - maxThumb.width() > 100 || scaledSize().height() - maxThumb.height() > 100))
	{
		int nSourceSize = exif.width() * exif.height();
		int nDestSize = m_ScaleSize.width() * m_ScaleSize.height();
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
		if(nJpegNarrow != 1 && (std::abs(nSourceSize >> nJpegNarrow) - nDestSize) > (std::abs((nSourceSize >> (nJpegNarrow >> 1)) - nDestSize)))
		{
			nJpegNarrow = (nJpegNarrow >> 1);
		}
		pBm->load(path, nJpegNarrow);
	}
	else
	{
		std::vector<Bitmap> thumbs;
		exif.getThumbnails(thumbs);
		*pBm = thumbs[0];
	}

	SizeI szFinal;
	float pixcelRatio = (float)(pBm->width()) / pBm->height();
	float containerRatio = (float)(m_ScaleSize.width()) / m_ScaleSize.height();
	if(pixcelRatio < containerRatio)
	{
		szFinal.height() = m_ScaleSize.height();
		szFinal.width() = (int)(szFinal.height() * pixcelRatio);
	}
	else
	{
		szFinal.width() = m_ScaleSize.width();
		szFinal.height() = (int)(szFinal.width() / pixcelRatio);
	}
	//使之四像素对齐
	szFinal.width() = szFinal.width() / 4 * 4;
	szFinal.height() = szFinal.height() / 4 * 4;
	*pBm = pBm->scale(szFinal.width(), szFinal.height());
}
