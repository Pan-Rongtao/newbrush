#include "media/FontFamily.h"
#include "freetype/ft2build.h"
#include FT_FREETYPE_H

using namespace nb::media;

FontFamily::FontFamily(const std::string & fontPath)
{
}

void FontFamily::setBaseline(int bl)
{
	m_baseline = bl;
}

int FontFamily::getBaseline() const
{
	return m_baseline;
}

void FontFamily::setLineSpacing(int ls)
{
	m_lineSpacing = ls;
}

int FontFamily::getLineSpacing() const
{
	return m_lineSpacing;
}

FT_LibraryRec_ *FontFamily::getFT()
{
	static FT_LibraryRec_ *ft = nullptr;
	if (!ft)
	{
		auto x = FT_Init_FreeType(&ft);
		if (x != 0)
			nbThrowException(std::runtime_error, "FT_Init_FreeType fail[%d]", x);
	}
	return ft;
}
