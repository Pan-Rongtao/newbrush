#include "FontFreeType.h"
#include <assert.h>
using namespace nb::gl::Gles;

FT_Library FontFreeType::m_ftLibrary;
bool FontFreeType::m_bftInitialized = false;

std::map<std::string, FontFreeType::DataRef> FontFreeType::m_fontDataMap;

FontFreeType::FontFreeType()
: m_fontsize(0.0f)
{
}

FontFreeType::~FontFreeType(void)
{
	m_fontDataMap[m_fontName].m_referenceCount -= 1;
    if (m_fontDataMap[m_fontName].m_referenceCount == 0)
    {
        m_fontDataMap.erase(m_fontName);
    }
    if (m_fontFace)
    {
        FT_Done_Face(m_fontFace);
    }
}

FontFreeTypePtr FontFreeType::Create(const std::string &fontName,float fontSize)
{
	FontFreeType* tmpFont = new FontFreeType();
	if(!tmpFont->CreateFontObject(fontName,fontSize))
	{
		delete tmpFont;
		return NULL;
	}
	return tmpFont;
}

bool FontFreeType::InitFreeType()
{
    if (m_bftInitialized == false)
    {
        if(FT_Init_FreeType(&m_ftLibrary))
		{
		    return false;
		}
        m_bftInitialized = true;
    }
    return  m_bftInitialized;
}

FT_Library FontFreeType::GetFTLibrary()
{
	InitFreeType();
	return m_ftLibrary;
}

#include <iostream>
std::pair<unsigned char *,unsigned long> FontFreeType::ReadFile(const std::string & fileName)
{
	std::cout<<"filesname is:"<<fileName.c_str()<<std::endl;
	FILE*   pFile = fopen(fileName.c_str(), "rb");
	//Data ret;
	std::pair<unsigned char *,unsigned long> ret;
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		ret.second = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		unsigned char* buffer = new unsigned char[ret.second + 1];
		fread(buffer, 1, ret.second, pFile);
		buffer[ret.second] = 0;
		fclose(pFile);
		ret.first = buffer;
		return  ret;
	}
	else
	{
		char    buffer[256];
		sprintf(buffer, "read %s  failed", fileName.c_str());
		assert(pFile != 0 && buffer);
	}
	return  ret;
}

bool FontFreeType::CreateFontObject(const std::string &fontName, float fontSize)
{
	FT_Face face;
    m_fontName = fontName;
	m_fontsize = fontSize;
	std::map<std::string, DataRef>::iterator itor = m_fontDataMap.find(fontName);
    if (itor != m_fontDataMap.end())
    {
        (*itor).second.m_referenceCount += 1;
    }
    else
    {
        m_fontDataMap[fontName].m_referenceCount = 1;
		std::pair<unsigned char *,unsigned long> ret = ReadFile(fontName);
		m_fontDataMap[fontName].m_data.m_bytes = ret.first;
		m_fontDataMap[fontName].m_data.m_size = ret.second;

        if (m_fontDataMap[fontName].m_data.IsNull())
        {
            return false;
        }
    }

    if (FT_New_Memory_Face(GetFTLibrary(), m_fontDataMap[fontName].m_data.m_bytes, m_fontDataMap[fontName].m_data.m_size, 0, &face ))
        return false;

	m_fontFace = face;
    int dpi = 72;
    int fontSizePoints = (int)(64.f * fontSize);
    if (FT_Set_Char_Size(face, fontSizePoints, fontSizePoints, dpi, dpi))
	{
		return false;
	}
    return true;
}

const FT_BitmapGlyph FontFreeType::GetGlyphBimap(wchar_t theChar)
{
	FT_Load_Glyph(m_fontFace, FT_Get_Char_Index(m_fontFace, theChar), FT_LOAD_DEFAULT);
	FT_Glyph glyph;
	FT_Get_Glyph(m_fontFace->glyph, &glyph);

	if (m_fontsize >= 16)
	{
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	}
	else
	{
		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_mono, 0, 1);
	}

	FT_BitmapGlyph  bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap ftBitmap;
	FT_Bitmap_New(&ftBitmap);

	if (bitmap_glyph->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
	{
		if (FT_Bitmap_Convert(m_ftLibrary, &bitmap_glyph->bitmap, &ftBitmap, 1) == 0)
		{
			for (unsigned char* p = ftBitmap.buffer, *endP = p + ftBitmap.width * ftBitmap.rows; p != endP; ++p)
			{
				*p ^= -*p ^ *p;
			}
		}
	}
	
	FT_Bitmap_Done(m_ftLibrary, &ftBitmap);
	return bitmap_glyph;
}