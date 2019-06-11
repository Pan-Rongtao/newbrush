#pragma once
#include "../core/Def.h"
#include "glm/glm.hpp"
#include <map>
#include <vector>
#include <string>
#include "Texture2D.h"
#include "../media/Font.h"

namespace nb{ namespace gl{

struct Glyph
{
	int					texureId;	//字形所在纹理
	glm::vec2			uv[4];		//纹理坐标
	media::GlyphInfo	info;		//字形信息
};

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//构建一个字形图集纹理，宽高为width, height，字形的尺寸为glypSize
	TextureGlyphAtlas(std::shared_ptr<nb::media::Font> font, const std::wstring &unicodeStr);
	~TextureGlyphAtlas();

	//font
	std::shared_ptr<media::Font> font();

	//追加文本，返回实际追加的长度（超过的长度被忽略）
	//返回的Plyph的texureId=-1表示添加失败，已满
	Glyph appendChar(wchar_t unicode);
	void appendText(const std::wstring &unicodeStr);

	//获取一个字符的信息
	Glyph getGlyph(wchar_t ch);
	
private:
	float						m_x;
	float						m_y;
	std::map<wchar_t, Glyph>	m_glyphs;
	bool						m_full;
	std::shared_ptr<media::Font>m_font;
};

class NB_API GlyphFactory
{
public:
	static Glyph getGlyph(wchar_t ch);

private:
	static std::vector<TextureGlyphAtlas *>	m_glyphAtlas;
	friend class TextureGlyphAtlas;
};

}}