#include <assert.h>
#include "Bitmap_Internal.h"
#include "core/Exception.h"

using namespace nb::Media;
bool			g_bHasInitFreeImage;
Bitmap_Internal::Bitmap_Internal()
: m_pFreeImage(NULL)
{
	InitFreeeImage();
}

Bitmap_Internal::Bitmap_Internal(const char *pFilePath)
: m_pFreeImage(NULL)
{
	//文件不存在异常
	//if()
	InitFreeeImage();
	LoadFile(pFilePath);
}

Bitmap_Internal::Bitmap_Internal(int width, int height, Bitmap::PixelFormat format)
: m_pFreeImage(NULL)
{
	InitFreeeImage();
	if(width < 0 || height < 0 || format == Bitmap::Format_Invalid)
		NB_THROW_EXCEPTION("invalid param");

	int bpp = 0;
	int rMask = 0;
	int gMask = 0;
	int bMask = 0;
	int pitch = 0;
	switch(format)
	{
	case Bitmap::Format_Bpp1_Palette:	
		bpp = 1; rMask = 0, gMask = 0; bMask = 0; pitch = width / 8;
		break;
	case Bitmap::Format_Bpp4_Palette:
		bpp = 4; rMask = 0, gMask = 0; bMask = 0; pitch = width / 2;
		break;
	case Bitmap::Format_Bpp8_Palette:
		bpp = 8; rMask = 0, gMask = 0; bMask = 0; pitch = width * 1;
		break;
	case Bitmap::Format_Bpp16_Rgb555:
		bpp = 16; rMask = FI16_555_RED_MASK; gMask = FI16_555_GREEN_MASK; bMask = FI16_555_BLUE_MASK; pitch = width * 2;
		break;
	case Bitmap::Format_Bpp16_Rgb565:
		bpp = 16; rMask = FI16_565_RED_MASK; gMask = FI16_565_GREEN_MASK; bMask = FI16_565_BLUE_MASK; pitch = width * 2;
		break;
	case Bitmap::Format_Bpp24_Rgb888:
		bpp = 24; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 3;
		break;
	case Bitmap::Format_Bpp32_Rgba8888:
		bpp = 32; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 4;
		break;
	default:
		break;
	}
	m_pFreeImage = FreeImage_Allocate(width, height, bpp, rMask, gMask, bMask);
}

Bitmap_Internal::Bitmap_Internal(const unsigned char *buffer, int width, int height, Bitmap::PixelFormat format)
: m_pFreeImage(NULL)
{
	InitFreeeImage();
	if(!buffer || format == Bitmap::Format_Invalid)
		return;

	if(width < 0 || height < 0)
		NB_THROW_EXCEPTION("invalid param");

	int bpp = 0;
	int rMask = 0;
	int gMask = 0;
	int bMask = 0;
	int pitch = 0;
	switch(format)
	{
	case Bitmap::Format_Bpp1_Palette:	
		bpp = 1; rMask = 0, gMask = 0; bMask = 0; pitch = width / 8;
		break;
	case Bitmap::Format_Bpp4_Palette:
		bpp = 4; rMask = 0, gMask = 0; bMask = 0; pitch = width / 2;
		break;
	case Bitmap::Format_Bpp8_Palette:
		bpp = 8; rMask = 0, gMask = 0; bMask = 0; pitch = width * 1;
		break;
	case Bitmap::Format_Bpp16_Rgb555:
		bpp = 16; rMask = FI16_555_RED_MASK; gMask = FI16_555_GREEN_MASK; bMask = FI16_555_BLUE_MASK; pitch = width * 2;
		break;
	case Bitmap::Format_Bpp16_Rgb565:
		bpp = 16; rMask = FI16_565_RED_MASK; gMask = FI16_565_GREEN_MASK; bMask = FI16_565_BLUE_MASK; pitch = width * 2;
		break;
	case Bitmap::Format_Bpp24_Rgb888:
		bpp = 24; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 3;
		break;
	case Bitmap::Format_Bpp32_Rgba8888:
		bpp = 32; rMask = FI_RGBA_RED_MASK; gMask = FI_RGBA_GREEN_MASK; bMask = FI_RGBA_BLUE_MASK; pitch = width * 4;
		break;
	default:
		break;
	}
	//保持四字节对齐，不然数据会斜
	if(pitch % 4 != 0)
		pitch = (pitch + 4) / 4 * 4;
	m_pFreeImage = FreeImage_ConvertFromRawBits((BYTE *)buffer, width, height, pitch, bpp, rMask, gMask, bMask);
}

Bitmap_Internal::Bitmap_Internal(const Bitmap_Internal &other)
: m_pFreeImage(NULL)
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

void Bitmap_Internal::LoadFile(const char *pFilePath)
{
	//文件不存在
	//assert(1);
	FreeImage_Unload(m_pFreeImage);
	m_pFreeImage = FreeImage_Load(FreeImage_GetFileType(pFilePath), pFilePath);
}

void Bitmap_Internal::LoadFileNarrowed(const nb::System::String &filePath, int jpegNarrow)
{
	FreeImage_Unload(m_pFreeImage);
	std::string s = filePath.ToUtf8().GetData();
	m_pFreeImage = FreeImage_Load(FreeImage_GetFileType(s.data()), s.data(), 0, jpegNarrow);
}

void Bitmap_Internal::LoadData(const unsigned char *data, int nLengthBytes)
{
	//assert
	assert(nLengthBytes >= 0);
	FreeImage_Unload(m_pFreeImage);
	FIMEMORY *memory = FreeImage_OpenMemory((BYTE *)data, nLengthBytes);
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(memory);
	m_pFreeImage = FreeImage_LoadFromMemory(fif, memory);
	FreeImage_CloseMemory(memory);
}

const unsigned char *Bitmap_Internal::GetData() const
{
	return m_pFreeImage == NULL ? NULL : FreeImage_GetBits(m_pFreeImage);
}

void Bitmap_Internal::Fill(unsigned int rgba)
{
	
}

bool Bitmap_Internal::HasPixelData() const
{
	return m_pFreeImage && (bool)FreeImage_HasPixels(m_pFreeImage);
}

bool Bitmap_Internal::IsNull() const
{
	return m_pFreeImage != NULL;
}

Bitmap::PixelFormat Bitmap_Internal::GetPixelFormat() const
{
	if(m_pFreeImage == NULL) 
	{
		return Bitmap::Format_Invalid;
	}
	else
	{
		int bpp = GetBpp();
		FREE_IMAGE_COLOR_TYPE ct = FreeImage_GetColorType(m_pFreeImage);
		Bitmap::PixelFormat format = Bitmap::Format_Invalid;
		switch(ct)
		{
		case FIC_MINISWHITE:
		case FIC_MINISBLACK:
		case FIC_PALETTE:
			format = Bitmap::Format_Bpp8_Palette;//bpp == 1 ? Bitmap::Format_Bpp1_Palette : (bpp == 4 ? Bitmap::Format_Bpp4_Palette : Bitmap::Format_Bpp8_Palette);
			break;
		case FIC_RGB:
			if(FreeImage_GetRedMask(m_pFreeImage) == FI16_555_RED_MASK && FreeImage_GetGreenMask(m_pFreeImage) == FI16_555_GREEN_MASK && FreeImage_GetBlueMask(m_pFreeImage) == FI16_555_BLUE_MASK)
				format = Bitmap::Format_Bpp16_Rgb555;
			else if(FreeImage_GetRedMask(m_pFreeImage) == FI16_565_RED_MASK && FreeImage_GetGreenMask(m_pFreeImage) == FI16_565_GREEN_MASK && FreeImage_GetBlueMask(m_pFreeImage) == FI16_565_BLUE_MASK)
				format = Bitmap::Format_Bpp16_Rgb565;
			else
				format = bpp == 24 ? Bitmap::Format_Bpp24_Rgb888 : Bitmap::Format_Bpp32_Rgba8888;
			break;
		case FIC_RGBALPHA:
			format = Bitmap::Format_Bpp32_Rgba8888; 
			break;
		}
		return format;
	}
}

int Bitmap_Internal::GetPixelWidth() const
{
	return m_pFreeImage == NULL ? 0 : FreeImage_GetWidth(m_pFreeImage);
}

int Bitmap_Internal::GetPixelHeight() const
{
	return m_pFreeImage == NULL ? 0 : FreeImage_GetHeight(m_pFreeImage);
}

int Bitmap_Internal::GetBpp() const
{
	return m_pFreeImage == NULL ? 0 : FreeImage_GetBPP(m_pFreeImage);
}

int Bitmap_Internal::GetBytesCount() const
{
	return m_pFreeImage == NULL ? 0 : FreeImage_GetDIBSize(m_pFreeImage) - sizeof(BITMAPINFOHEADER);	//纯数据字节数=FreeImage_GetDIBSize减去FreeImage的头部
}

int Bitmap_Internal::GetBytesCountPerLine() const
{
	return m_pFreeImage == NULL ? 0 : FreeImage_GetLine(m_pFreeImage);
}

unsigned char *Bitmap_Internal::GetScanLine(int lineIndex)
{
	return m_pFreeImage == NULL ? NULL : FreeImage_GetScanLine(m_pFreeImage, lineIndex);
}

unsigned int Bitmap_Internal::GetPixel(int x, int y) const
{
	return 0;
}

void Bitmap_Internal::SetPixel(int x, int y, unsigned int rgba)
{

}

Bitmap_Internal Bitmap_Internal::Scale(int width, int height) const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

 	FIBITMAP *pScale = FreeImage_Rescale(m_pFreeImage, width, height, FILTER_BOX);
 	Bitmap_Internal bm;
	bm.m_pFreeImage = pScale;
 	return bm;
}

Bitmap_Internal Bitmap_Internal::ScaleWidth(int width) const
{
	return Scale(width, GetPixelHeight());
}

Bitmap_Internal Bitmap_Internal::ScaleHeight(int height) const
{
	return Scale(GetPixelWidth(), height);
}

Bitmap_Internal Bitmap_Internal::Copy(int x, int y, int width, int height) const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

	FIBITMAP *p = FreeImage_Copy(m_pFreeImage, x, y, x + width, y + height);
	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

Bitmap_Internal Bitmap_Internal::ToGray() const
{
	if(!m_pFreeImage)
		return Bitmap_Internal();

	FIBITMAP *p = FreeImage_ConvertToGreyscale(m_pFreeImage);
	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

Bitmap_Internal Bitmap_Internal::ConverToFormat(Bitmap::PixelFormat format)
{
	if(!m_pFreeImage)
		return Bitmap_Internal();
	if(format == Bitmap::Format_Invalid)
		NB_THROW_EXCEPTION("invalid param");

	FIBITMAP *p = NULL;
	switch(format)
	{
	case Bitmap::Format_Bpp1_Palette:	
		p = FreeImage_ConvertTo4Bits(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp4_Palette:
		p = FreeImage_ConvertTo4Bits(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp8_Palette:
		p = FreeImage_ConvertTo8Bits(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp16_Rgb555:
		p = FreeImage_ConvertTo16Bits555(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp16_Rgb565:
		p = FreeImage_ConvertTo16Bits565(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp24_Rgb888:
		p = FreeImage_ConvertTo24Bits(m_pFreeImage);
		break;
	case Bitmap::Format_Bpp32_Rgba8888:
		p = FreeImage_ConvertTo32Bits(m_pFreeImage);
		break;
	default:
		break;
	}

	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	return bm;
}

void Bitmap_Internal::SaveAsFile(const char *pFilePath) const
{
	//assert(pfilepath);
	FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(pFilePath);
	if(format == FIF_UNKNOWN)
		format = FIF_BMP;
	bool b = FreeImage_Save(format, m_pFreeImage, pFilePath);
}

//注意，此函数必须保证第一次在主线程中调用，也就是FreeImage_Initialise();必须在主线程中第一次被执行，否则只会FreeImage的加载都将失败
//此问题在为已知问题。
void Bitmap_Internal::InitFreeeImage()
{
	if(g_bHasInitFreeImage)
		return;
	FreeImage_Initialise();
	g_bHasInitFreeImage = true;
}

Bitmap_Internal Bitmap_Internal::BgrToRgb() const
{
	return *this;
	BYTE *pixels = (BYTE*)FreeImage_GetBits(m_pFreeImage);
	if(pixels == NULL)
		return Bitmap_Internal();

	int width = GetPixelWidth();
	int height = GetPixelHeight();

	BYTE *bits = NULL;
	int pitch = FreeImage_GetPitch(m_pFreeImage);
	int pb = GetBpp() / 8;
	switch(GetBpp())
	{
	case 1:
	case 4:
	case 8:
	case 16:
		{
			return *this;
		}
		break;
	case 24:
		{
			bits = new BYTE[pitch * height];
			for(int i = 0; i < height; ++i ) 
			{
				for(int j = 0; j < width; ++j ) 
				{
					bits[pitch * i + j * pb + 0] = pixels[i * pitch + j * pb + 2];
					bits[pitch * i + j * pb + 1] = pixels[i * pitch + j * pb + 1];
					bits[pitch * i + j * pb + 2] = pixels[i * pitch + j * pb + 0];
				}
			}
		}
		break;
	case 32:
		{
			FREE_IMAGE_COLOR_TYPE ct = FreeImage_GetColorType(m_pFreeImage);
			if(ct == FIC_RGBALPHA)
			{
				bits = new BYTE[pitch * height];
				for(int i = 0; i < height; ++i ) 
				{
					for(int j = 0; j < width; ++j ) 
					{
						bits[pitch * i + j * pb + 0] = pixels[i * pitch + j * pb + 2];
						bits[pitch * i + j * pb + 1] = pixels[i * pitch + j * pb + 1];
						bits[pitch * i + j * pb + 2] = pixels[i * pitch + j * pb + 0];
						bits[pitch * i + j * pb + 3] = pixels[i * pitch + j * pb + 3];
					}
				}
			}
			else
			{
				return *this;
			}
		}
		break;
	default:
		return *this;
		break;
	}

	int rMask = FreeImage_GetRedMask(m_pFreeImage);
	int gMask = FreeImage_GetGreenMask(m_pFreeImage);
	int bMask = FreeImage_GetBlueMask(m_pFreeImage);
	
	FIBITMAP *p = FreeImage_ConvertFromRawBits((BYTE *)bits, width, height, pitch, GetBpp(), rMask, gMask, bMask);
	Bitmap_Internal bm;
	bm.m_pFreeImage = p;
	delete []bits;
	return bm;
}
