#pragma once
#include "core/Object.h"
#include "gles/TTFConfig.h"
#include "FontFreeType.h"
#include "FontGlesProgramState.h"
#include "GlesProgramState.h"
#include "GlesProgramCache.h"
#include "Shader_Font.frag"
#include "Shader_Font.vert"
#include "GlesProgram.h"

namespace nb{ namespace gl{ namespace Gles{


static const int m_textureWidth = 512;
static const int m_textureHeight = 512;

class TextureFont;
typedef nbObjectPtrDerive<TextureFont, Core::RefObjectPtr> TextureFontPtr;
class FontLetterDefinition
{
public:
	FontLetterDefinition()
	{
		m_x0 = 0;
		m_y0 = 0;
		m_x1 = 0;
		m_y1 = 0;
		m_offsetX = 0;
		m_offsetY = 0;
	}
	unsigned int m_x0;
	unsigned int m_y0;
	unsigned int m_x1;
	unsigned int m_y1;
	unsigned int m_offsetX;
	unsigned int m_offsetY;
	//unsigned int m_textureID;
	Core::RefObjectWeatPtrT<TextureFont> m_texture;
};


class TextureFont: public Core::RefObject
{
public:
	TextureFont(int fontSize);
	~TextureFont();
	bool Init();
	bool UpdateData(FontLetterDefinition& letterDefine, const FT_BitmapGlyph bimapGlyph);
    int	m_texture;
	int m_yStart;
	int	m_xStart;
	int m_fontPixelY;
	int m_fontSize;
	FontGlesProgramStatePtr m_program;
};


class FontFreeType;
class FontAtlasCache;
class FontAtlas : public Core::RefObject
{
public:
	friend class FontAtlasCache;

	bool PrepareLetterDefinitions(const std::wstring & utf16Text);

	const FontLetterDefinition * GetLetterDefinition(wchar_t letter);

protected:
	FontAtlas(const TTFConfig* config);
	~FontAtlas(void);
	void FindNewCharacters(const std::wstring& u16Text, std::wstring & OutNewCharCodeMap);
private:
	int m_fontSize;
	FontFreeTypePtr m_pfontFreetype;
	std::map<unsigned int, TextureFontPtr> m_atlasTextures;
	std::map<wchar_t, FontLetterDefinition> m_letterDefinitions;
	void RenderBimapToTexture(FontLetterDefinition & letterDefine, const FT_BitmapGlyph bimapGlyph);
	unsigned int m_currentPage;
};

typedef nbObjectPtrDerive<FontAtlas, Core::RefObjectPtr> FontAtlasPtr;


}}}
