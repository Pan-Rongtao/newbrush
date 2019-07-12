#include "media/GlyphMetrics.h"
#include <codecvt>
#include <freetype/ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftbitmap.h>
#include FT_FREETYPE_H
#include "media/Font.h"

using namespace nb::core;
using namespace nb::media;

GlyphInfo GlyphMetrics::measureGlyp(std::shared_ptr<Font> font, wchar_t ch)
{
	auto x = FT_Load_Char(font->m_face, ch, FT_LOAD_DEFAULT);
	FT_Glyph glyph;
	FT_Get_Glyph(font->m_face->glyph, &glyph);
	FT_Glyph_To_Bitmap(&glyph, font->size() >= 16 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_MONO, 0, 1);

	FT_BitmapGlyph bmGlyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap bm;
	FT_Bitmap_New(&bm);
	if (bmGlyph->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
	{
		if (FT_Bitmap_Convert(Font::getFT(), &bmGlyph->bitmap, &bm, 1) == 0)
		{
			for (unsigned char* p = bm.buffer, *endP = p + bm.width * bm.rows; p != endP; ++p)
			{
				*p ^= -*p ^ *p;
			}
		}
	}
	FT_Bitmap_Done(Font::getFT(), &bm);
	return GlyphInfo{ bmGlyph->left, bmGlyph->top, bmGlyph->root.advance.x,
		bmGlyph->root.advance.y, bmGlyph->bitmap.width, bmGlyph->bitmap.rows, bmGlyph->bitmap.pitch,  bmGlyph->bitmap.buffer };
}

nb::core::Size GlyphMetrics::measureGlyphAltas(std::shared_ptr<Font> font, const std::string & text, float charSpacing, float lineHeight, TextWrappingE tw, float widthMax)
{
	if (!font)
		nbThrowException(std::invalid_argument, "font is nullptr");

	if (text.empty() || (tw == TextWrappingE::Wrap && widthMax <= 0.0f))
		return Size(0.0f, 0.0f);

	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring unicodeStr = cvt.from_bytes(text);
	switch (tw)
	{
	case TextWrappingE::NoWrap:
	{
		float x = 0.0f;
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = measureGlyp(font, unicodeStr[i]);
			x += glyph.bm_width + charSpacing;
		}
		return Size(x - charSpacing, lineHeight);
	}
	case TextWrappingE::Wrap:
	{
		float x = 0.0f, y = 0.0f;
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = measureGlyp(font, unicodeStr[i]);
			if (x + glyph.bm_width + charSpacing <= widthMax)
			{
				x += glyph.bm_width + charSpacing;
			}
			else
			{
				y += lineHeight;
				x = glyph.bm_width + charSpacing;
			}
		}
		return Size(widthMax, y + lineHeight);
	}
	default:
		return Size(0.0f, 0.0f);
	}
}
