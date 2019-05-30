#include "TiffReader_Internal.h"
#include "Bitmap_Internal.h"

using namespace nb::core;
using namespace nb::media;

TiffReader_Internal::TiffReader_Internal()
: m_pFreeImage(NULL)
{
}

TiffReader_Internal::~TiffReader_Internal()
{
	close();
}

bool TiffReader_Internal::open(const std::string &path)
{
	m_pFreeImage = FreeImage_OpenMultiBitmap(FIF_TIFF, path.data(), false, true, true, TIFF_ADOBE_DEFLATE);
	return m_pFreeImage != NULL;
}

void TiffReader_Internal::close()
{
	FreeImage_CloseMultiBitmap(m_pFreeImage);
	m_pFreeImage = NULL;
}

bool TiffReader_Internal::hasData() const
{
	return m_pFreeImage == NULL || frameCount() == 0;
}

int TiffReader_Internal::frameCount() const
{
	return m_pFreeImage ? FreeImage_GetPageCount(m_pFreeImage) : 0;
}

Bitmap TiffReader_Internal::frame(int index) const
{
	if(index <0 || index >= frameCount())
		NB_THROW_EXCEPTION(std::out_of_range, "index[%d] is out of range [%d, %d).", index, 0, frameCount());

	if(m_pFreeImage == NULL)
		return Bitmap();

	FIBITMAP *p = FreeImage_LockPage(m_pFreeImage, index);
	//需转到24位，可能是因为gif帧只有256色，无法识别到alpha通道（转到16或32位不行）
	p = FreeImage_ConvertTo24Bits(p);
	Bitmap_Internal bm_interal;
	bm_interal.m_pFreeImage = p;
	Bitmap bm(bm_interal.data(), bm_interal.pixelWidth(), bm_interal.pixelHeight(), bm_interal.pixelFormat());
	FreeImage_UnlockPage(m_pFreeImage, p, false);
	return bm;
}
