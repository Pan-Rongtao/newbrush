#include "media/GlyphMetrics.h"
#include <codecvt>
#include "media/Font.h"

using namespace nb::core;
using namespace nb::media;

nb::core::Size GlyphMetrics::measureGlyphAltas(std::shared_ptr<Font> font, const std::string & text, float charSpacing, float lineHeight, TextWrapping tw, float widthMax)
{
	if (!font)
		nbThrowException(std::invalid_argument, "font is nullptr");
	if (text.empty() || (tw == TextWrapping::Wrap && widthMax <= 0.0f))
		return Size(0.0f, 0.0f);

	std::wstring_convert<std::codecvt_utf8<wchar_t>> cvt;
	std::wstring unicodeStr = cvt.from_bytes(text);
	switch (tw)
	{
	case TextWrapping::NoWrap:
	{
		float x = 0.0f;
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = font->getGlyphInfo(unicodeStr[i]);
			x += glyph.bm_width + charSpacing;
		}
		return Size(x - charSpacing, lineHeight);
	}
	case TextWrapping::Wrap:
	{
		float x = 0.0f, y = 0.0f;
		for (int i = 0; i != unicodeStr.size(); ++i)
		{
			auto glyph = font->getGlyphInfo(unicodeStr[i]);
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
