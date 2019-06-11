#include <assert.h>
#include "Bitmap_Internal.h"

using namespace nb::core;
using namespace nb::media;
static bool		g_bHasInitFreeImage;
Bitmap_Internal::Bitmap_Internal()
	: m_pFreeImage(nullptr)
{
	initFreeeImage();
}

Bitmap_Internal::Bitmap_Internal(const std::string &path)
	: m_pFreeImage(nullptr)
{
	initFreeeImage();
	load(path, 1);
}

Bitmap_Internal::Bitmap_Internal(int width, int height, Bitmap::PixelFormat format)
	: m_pFreeImage(nullptr)
{
	initFreeeImage();
	if(width < 0 || height < 0 || format == Bitmap::Format_Invalid)
		NB_THROW_EXCEPTION(std::invalid_argument, "invalid param");

	int bpp = 0, rMask = 0, gMask = 0, bMask = 0, pitch = 0;
	calcParam(width, height, format, bpp, rMask, gMask, bMask, pitch);
	m_pFreeImage = FreeImage_Allocate(width, height, bpp, rMask, gMask, bMask);
}

Bitmap_Internal::Bitmap_Internal(const char *buffer, int width, int height, Bitmap::PixelFormat format)
	: m_pFreeImage(nullptr)
{
	initFreeeImage();
	if(!buffer || format == Bitmap::Format_Invalid || width < 0 || height < 0)
		NB_THROW_EXCEPTION(std::invalid_argument, "invalid param");

	int bpp = 0, rMask = 0, gMask = 0, bMask = 0, pitch = 0;
	calcParam(width, height, format, bpp, rMask, gMask, bMask, pitch);
	m_pFreeImage = FreeImage_ConvertFromRawBits((BYTE *)buffer, width, height, pitch, bpp, rMask, gMask, bMask);
}

Bitmap_Internal::Bitmap_Internal(const Bitmap_Internal &other)
	: m_pFreeImage(nullptr)
{
	FreeImage_Unload(m_pFreeImage);
	m_pFreeImage = FreeImage_Clone(other.m_pFreeImage);
}

Bitmap_Internal::~Bitmap_Internal()
{
	FreeImage_Unload(m_pFreeImage);
}

void Bitmap_Internal::operator = (const Bitmap_Internal &other)
{
	FreeImage_Unload(m_pFreeImage);
	m_pFreeImage = FreeImage_Clone(other.m_pFreeImage);
}

void Bitmap_Internal::load(const std::string &path, int jpegNarrow)
{
	//文件不存在
	FreeImage_Unload(m_pFreeImage);
	m_pFreeImage = FreeImage_Load(FreeImage_GetFileType(path.data()), path.data(), 0, jpegNarrow);
}

void Bitmap_Internal::load(const char *data, int bytes)
{
	if (bytes < 0)
		NB_THROW_EXCEPTION(std::invalid_argument, "bytes < 0");

	FreeImage_Unload(m_pFreeImage);
	FIMEMORY *memory = FreeImage_OpenMemory((BYTE *)data, bytes);
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(memory);
	m_pFreeImage = FreeImage_LoadFromMemory(fif, memory);
	FreeImage_CloseMemory(memory);
}

const char *Bitmap_Internal::data() const
{
	return m_pFreeImage ? (const char *)FreeImage_GetBits(m_pFreeImage) : nullptr;
}

void Bitmap_Internal::fill(unsigned int rgba)
{
	
}

bool Bitmap_Internal::hasPixelData() const
{
	return m_pFreeImage && FreeImage_HasPixels(m_pFreeImage) != 0;
}

Bitmap::PixelFormat Bitmap_Internal::pixelFormat() const
{
	if(!m_pFreeImage)
		return Bitmap::Format_Invalid;

	int bpp = this->bpp();
	FREE_IMAGE_COLOR_TYPE ct = FreeImage_GetColorType(m_pFreeImage);
	Bitmap::PixelFormat format = Bitmap::Format_Invalid;
	switch(ct)
	{
	case FIC_MINISWHITE:
	case FIC_MINISBLACK:
	case FIC_PALETTE:	format = Bitmap::Format_Bpp8_Palette;	break;
	case FIC_RGB:
	{
		if (FreeImage_GetRedMask(m_pFreeImage) == FI16_555_RED_MASK && FreeImage_GetGreenMask(m_pFreeImage) == FI16_555_GREEN_MASK && FreeImage_GetBlueMask(m_pFreeImage) == FI16_555_BLUE_MASK)
			format = Bitmap::Format_Bpp16_Rgb555;
		else if (FreeImage_GetRedMask(m_pFreeImage) == FI16_565_RED_MASK && FreeImage_GetGreenMask(m_pFreeImage) == FI16_565_GREEN_MASK && FreeImage_GetBlueMask(m_pFreeImage) == FI16_565_BLUE_MASK)
			format = Bitmap::Format_Bpp16_Rgb565;
		else
			format = bpp == 24 ? Bitmap::Format_Bpp24_Rgb888 : Bitmap::Format_Bpp32_Rgba8888;
		break;
	}
	case FIC_RGBALPHA:	format = Bitmap::Format_Bpp32_Rgba8888;	break;
	default:													break;
	}
	return format;
}

int Bitmap_Internal::pixelWidth() const
{
	return m_pFreeImage ? FreeImage_GetWidth(m_pFreeImage) : 0;
}

int Bitmap_Internal::pixelHeight() const
{
	return m_pFreeImage ? FreeImage_GetHeight(m_pFreeImage) : 0;
}

int Bitmap_Internal::bpp() const
{
	return m_pFreeImage ? FreeImage_GetBPP(m_pFreeImage) : 0;
}

int Bitmap_Internal::bytes() const
{
	return m_pFreeImage ? FreeImage_GetDIBSize(m_pFreeImage) - sizeof(BITMAPINFOHEADER) : 0;	//纯数据字节数=FreeImage_GetDIBSize减去FreeImage的头部
}

int Bitmap_Internal::bytesPerLine() const
{
	return m_pFreeImage ? FreeImage_GetLine(m_pFreeImage) : 0;
}

char *Bitmap_Internal::scanLine(int lineIndex)
{
	return m_pFreeImage ? (char *)FreeImage_GetScanLine(m_pFreeImage, lineIndex) : nullptr;
}

unsigned int Bitmap_Internal::pixel(int x, int y) const
{
	return 0;
}

void Bitmap_Internal::setPixel(int x, int y, unsigned int rgba)
{
	if (!m_pFreeImage)
		return;

	Color c = Color::fromIntegerArgb(rgba);
	RGBQUAD quad{ c.red(), c.green(), c.blue(), c.alpha() };
	FreeImage_SetPixelColor(m_pFreeImage, x, y, &quad);
}

Bitmap_Internal Bitmap_Internal::scale(int width, int height) const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

 	FIBITMAP *pScale = FreeImage_Rescale(m_pFreeImage, width, height, FILTER_BOX);
 	Bitmap_Internal bm;
	bm.m_pFreeImage = pScale;
 	return bm;
}

Bitmap_Internal Bitmap_Internal::copy(int x, int y, int width, int height) const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

	FIBITMAP *p = FreeImage_Copy(m_pFreeImage, x, y, x + width, y + height);
	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

Bitmap_Internal Bitmap_Internal::gray() const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

	FIBITMAP *p = FreeImage_ConvertToGreyscale(m_pFreeImage);
	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

Bitmap_Internal Bitmap_Internal::convert(Bitmap::PixelFormat toFormat)
{
	if(toFormat == Bitmap::Format_Invalid)
		NB_THROW_EXCEPTION(std::invalid_argument, "invalid param");

	if (!m_pFreeImage)
		return Bitmap_Internal();

	FIBITMAP *p = NULL;
	switch(toFormat)
	{
	case Bitmap::Format_Bpp1_Palette:	p = FreeImage_ConvertTo4Bits(m_pFreeImage);		break;
	case Bitmap::Format_Bpp4_Palette:	p = FreeImage_ConvertTo4Bits(m_pFreeImage);		break;
	case Bitmap::Format_Bpp8_Palette:	p = FreeImage_ConvertTo8Bits(m_pFreeImage);		break;
	case Bitmap::Format_Bpp16_Rgb555:	p = FreeImage_ConvertTo16Bits555(m_pFreeImage);	break;
	case Bitmap::Format_Bpp16_Rgb565:	p = FreeImage_ConvertTo16Bits565(m_pFreeImage);	break;
	case Bitmap::Format_Bpp24_Rgb888:	p = FreeImage_ConvertTo24Bits(m_pFreeImage);	break;
	case Bitmap::Format_Bpp32_Rgba8888:	p = FreeImage_ConvertTo32Bits(m_pFreeImage);	break;
	default:																			break;
	}

	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

void Bitmap_Internal::save(const std::string &path) const
{
	//assert(pfilepath);
	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(path.data());
	if(format == FIF_UNKNOWN)
		format = FIF_BMP;
	bool b = FreeImage_Save(format, m_pFreeImage, path.data()) != 0;
}

//注意，此函数必须保证第一次在主线程中调用，也就是FreeImage_Initialise();必须在主线程中第一次被执行，否则只会FreeImage的加载都将失败
//此问题在为已知问题。
void Bitmap_Internal::initFreeeImage()
{
	if(g_bHasInitFreeImage)
		return;
	FreeImage_Initialise();
	g_bHasInitFreeImage = true;
}

void Bitmap_Internal::calcParam(int width, int height, Bitmap::PixelFormat format, int & bpp, int & rMask, int & gMask, int & bMask, int pitch)
{
	switch (format)
	{
	case Bitmap::Format_Bpp1_Palette:	bpp = 1; rMask = 0, gMask = 0; bMask = 0; pitch = width / 8;														break;
	case Bitmap::Format_Bpp4_Palette:	bpp = 4; rMask = 0, gMask = 0; bMask = 0; pitch = width / 2;														break;
	case Bitmap::Format_Bpp8_Palette:	bpp = 8; rMask = 0, gMask = 0; bMask = 0; pitch = width * 1;														break;
	case Bitmap::Format_Bpp16_Rgb555:	bpp = 16; rMask = FI16_555_RED_MASK; gMask = FI16_555_GREEN_MASK; bMask = FI16_555_BLUE_MASK; pitch = width * 2;	break;
	case Bitmap::Format_Bpp16_Rgb565:	bpp = 16; rMask = FI16_565_RED_MASK; gMask = FI16_565_GREEN_MASK; bMask = FI16_565_BLUE_MASK; pitch = width * 2;	break;
	case Bitmap::Format_Bpp24_Rgb888:	bpp = 24; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 3;		break;
	case Bitmap::Format_Bpp32_Rgba8888:	bpp = 32; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 4;		break;
	default:																																				break;
	}
	if (pitch % 4 != 0)
		pitch = (pitch + 4) / 4 * 4;
}
