#include "newbrush/media/Font.h"
#include "freetype/ft2build.h"
#include "freetype/ftglyph.h"
#include <freetype/ftbitmap.h>
#include FT_FREETYPE_H

using namespace nb;

Font::Font(const std::string &path)
	: Font(path, 32)
{
}

Font::Font(const std::string &path, uint32_t fontSize)
	: m_fontSize(fontSize)
	, m_path(path)
	, m_face(nullptr)
{
	auto x = FT_New_Face(getFT(), path.data(), 0, &m_face);
	if (x != 0)
		nbThrowException(std::runtime_error, "FT_New_Face fail[%d]", x);
	setSize(fontSize);
}

Font::~Font()
{
	FT_Done_Face(m_face);
}

std::string Font::path() const
{
	return m_path;
}

std::string Font::familyName() const
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

FT_LibraryRec_ *Font::getFT()
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

//system fonts
////////////////////////
std::map<std::string, std::shared_ptr<Font>> Fonts::s_systemFonts;

std::shared_ptr<Font> Fonts::getFont(const std::string &name)
{
	initSystemFonts();
	auto iter = s_systemFonts.find(name);
	return iter != s_systemFonts.end() ? iter->second : nullptr;
}

std::map<std::string, std::shared_ptr<Font>> Fonts::systemFonts()
{
	initSystemFonts();
	return s_systemFonts;
}

void Fonts::initSystemFonts()
{
	auto loadSystemFonts = [](const std::string &path)->std::shared_ptr<Font>
	{
		std::shared_ptr<Font> font;
		try {
			font = std::make_shared<Font>(path);
		}
		catch (...) {
			printf("load font [%s] fail.\n", font->path().data());
			return nullptr;
		}
		s_systemFonts.insert({ font->familyName(), font });
		return font;
	};

	static bool systemFontsInit = false;
	if (!systemFontsInit)
	{
#ifdef NB_OS_FAMILY_WINDOWS
		loadSystemFonts("C:/Windows/Fonts/msyh.ttf");
#else
#if NB_OS == NB_OS_LINUX
#endif
#endif
		systemFontsInit = true;
	}
}
