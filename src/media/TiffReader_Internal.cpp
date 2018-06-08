#include "TiffReader_Internal.h"
#include "Bitmap_Internal.h"

using nb::Media::TiffReader_Internal;

TiffReader_Internal::TiffReader_Internal()
: m_pFreeImage(NULL)
{
}

TiffReader_Internal::~TiffReader_Internal()
{
	Close();
}

bool TiffReader_Internal::Open(const nb::System::String &path)
{
	m_pFreeImage = FreeImage_OpenMultiBitmap(FIF_TIFF, path.ToUtf8().GetData(), false, true, true, TIFF_ADOBE_DEFLATE);
	return m_pFreeImage != NULL;
}

void TiffReader_Internal::Close()
{
	FreeImage_CloseMultiBitmap(m_pFreeImage);
	m_pFreeImage = NULL;
}

bool TiffReader_Internal::HasData() const
{
	return m_pFreeImage == NULL || GetFrameCount() == 0;
}

int TiffReader_Internal::GetFrameCount() const
{
	return m_pFreeImage ? FreeImage_GetPageCount(m_pFreeImage) : 0;
}

nb::Media::Bitmap TiffReader_Internal::GetFrame(int index) const
{
	if(index <0 || index >= GetFrameCount())
		NB_THROW_EXCEPTION("out of range.");

	if(m_pFreeImage == NULL)
		return Bitmap();

	FIBITMAP *p = FreeImage_LockPage(m_pFreeImage, index);
	//需转到24位，可能是因为gif帧只有256色，无法识别到alpha通道（转到16或32位不行）
	p = FreeImage_ConvertTo24Bits(p);
	Bitmap_Internal bm_interal;
	bm_interal.m_pFreeImage = p;
	Bitmap bm(bm_interal.GetData(), bm_interal.GetPixelWidth(), bm_interal.GetPixelHeight(), bm_interal.GetPixelFormat());
	FreeImage_UnlockPage(m_pFreeImage, p, false);
	return bm;
}
