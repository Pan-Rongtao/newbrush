#include "GifReader_Internal.h"
#include "Bitmap_Internal.h"
#include "core/Exception.h"

using namespace nb::core;
using namespace nb::media;

GifReader_Internal::GifReader_Internal()
: m_pFreeImage(nullptr)
{
}

GifReader_Internal::~GifReader_Internal()
{
	close();
}

bool GifReader_Internal::open(const String &path)
{
	m_pFreeImage = FreeImage_OpenMultiBitmap(FIF_GIF, path.ToUtf8().GetData(), false, true, true, GIF_PLAYBACK);
	return m_pFreeImage != nullptr;
}

void GifReader_Internal::close()
{
	FreeImage_CloseMultiBitmap(m_pFreeImage);
	m_pFreeImage = nullptr;
}

bool GifReader_Internal::hasData() const
{
	return m_pFreeImage == nullptr || frameCount() == 0;
}

int GifReader_Internal::frameCount() const
{
	return m_pFreeImage ? FreeImage_GetPageCount(m_pFreeImage) : 0;
}

Bitmap GifReader_Internal::frame(int index) const
{
	if(index <0 || index >= frameCount())
		NB_THROW_EXCEPTION("out of range.");

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
