#include "media/Font.h"
#include "freetype/ft2build.h"
#include "freetype/ftglyph.h"
#include <freetype/ftbitmap.h>
#include FT_FREETYPE_H
#include "media/FontFamily.h"

using namespace nb::media;

Font::Font(const std::string &fontPath)
	: Font(fontPath, 30)
{
}

Font::Font(const std::string &fontPath, uint32_t fontSize)
	: m_fontSize(fontSize)
	, m_face(nullptr)
{
	auto x = FT_New_Face(FontFamily::getFT(), fontPath.data(), 0, &m_face);
	if (x != 0)
		nbThrowException(std::runtime_error, "FT_New_Face fail[%d]", x);
	setSize(fontSize);
}

Font::~Font()
{
	FT_Done_Face(m_face);
}

std::string Font::name() const
{
	return m_face->family_name;
}

void Font::setSize(uint32_t fontSize)
{
	if (fontSize < 8)
		nbThrowException(std::out_of_range, "fontSize[%d] is out of range[8, 72]", fontSize);

	auto x = FT_Set_Pixel_Sizes(m_face, 0, fontSize);	//0表示与另一个尺寸值相等
	m_fontSize = fontSize;
}

uint32_t Font::size() const
{
	return m_fontSize;
}

GlyphInfo Font::getGlyphInfo(wchar_t unicode)
{
	auto x = FT_Load_Char(m_face, unicode, FT_LOAD_DEFAULT);
	FT_Glyph glyph;
	FT_Get_Glyph(m_face->glyph, &glyph);
	FT_Glyph_To_Bitmap(&glyph, size() >= 16 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO, 0, 1);

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
	return GlyphInfo{ m_face->glyph->bitmap_left, m_face->glyph->bitmap_top, bmGlyph->root.advance.x, bmGlyph->root.advance.y, bmGlyph->bitmap.width, bmGlyph->bitmap.rows, bmGlyph->bitmap.pitch,  bmGlyph->bitmap.buffer };
}
