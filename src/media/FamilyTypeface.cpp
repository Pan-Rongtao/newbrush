#include "media/FamilyTypeface.h"
#include "freetype/ft2build.h"
#include "freetype/ftglyph.h"
#include <freetype/ftbitmap.h>
#include FT_FREETYPE_H
#include "media/FontFamily.h"

using namespace nb::media;

FamilyTypeface::FamilyTypeface(const std::string &fontPath)
	: m_fontSize(0)
	, m_face(nullptr)
{
	auto ft = FontFamily::getFT();
	auto x = FT_New_Face(ft, fontPath.data(), 0, &m_face);
	if (x != 0)
		NB_THROW_EXCEPTION(std::runtime_error, "FT_New_Face fail[%d]", x);
}

FamilyTypeface::~FamilyTypeface()
{
	FT_Done_Face(m_face);
}

std::string FamilyTypeface::getFontName() const
{
	return m_face->family_name;
}

void FamilyTypeface::setFontSize(uint32_t fontSize)
{
	if (fontSize < 8)
		NB_THROW_EXCEPTION(std::out_of_range, "fontSize[%d] is out of range[8, 72]", fontSize);

	auto x = FT_Set_Pixel_Sizes(m_face, 0, fontSize);	//0表示与另一个尺寸值相等
	m_fontSize = fontSize;
}

int FamilyTypeface::getFontSize() const
{
	return m_fontSize;
}

FT_BitmapGlyphRec_ *FamilyTypeface::loadChar(wchar_t unicode)
{
	auto x = FT_Load_Char(m_face, unicode, FT_LOAD_DEFAULT);
	FT_Glyph glyph;
	FT_Get_Glyph(m_face->glyph, &glyph);
	FT_Glyph_To_Bitmap(&glyph, getFontSize() >= 16 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO, 0, 1);

	FT_BitmapGlyph bmGlyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap bm;
	FT_Bitmap_New(&bm);
	if (bmGlyph->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
	{
		if (FT_Bitmap_Convert(media::FontFamily::getFT(), &bmGlyph->bitmap, &bm, 1) == 0)
		{
			for (unsigned char* p = bm.buffer, *endP = p + bm.width * bm.rows; p != endP; ++p)
			{
				*p ^= -*p ^ *p;
			}
		}
	}
	FT_Bitmap_Done(media::FontFamily::getFT(), &bm);
	return bmGlyph;
}

FT_FaceRec_ *FamilyTypeface::get()
{
	return m_face;
}
