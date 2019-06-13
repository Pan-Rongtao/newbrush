#include "gles/GlyphFactory.h"
#include <map>
#include <vector>
#include "gles/Texture2D.h"
#include <opengl/GLES2/gl2.h>
#include <freetype/ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftbitmap.h>
#include "media/FontFamily.h"
#include FT_FREETYPE_H

using namespace nb::core;
using namespace nb::media;
using namespace nb::gl;

constexpr int GlyphAltasWidth = 512;
constexpr int GlyphAltasHeight = 512;
class TextureGlyphAtlas;
static std::vector<TextureGlyphAtlas *>	g_glyphAtlas;

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//构建一个字形图集纹理，宽高为width, height，字形的尺寸为glypSize
	TextureGlyphAtlas(std::shared_ptr<nb::media::Font> font, const std::wstring &unicodeStr)
		: Texture2D(GlyphAltasWidth, GlyphAltasHeight) , m_x(0) , m_y(0) , m_font(font)
	{
		if ((m_width != 0 && m_height != 0) && (m_width % m_font->size() != 0 || m_height % m_font->size() != 0))
			printf("warning: width or height mod glypSize != 0\n");

		setWrapping(TextureWrapping());
		setFilter(TextureFilter());
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_width, m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
		unbind();
		appendText(unicodeStr);
		g_glyphAtlas.push_back(this);
	}

	~TextureGlyphAtlas()
	{
		auto iter = std::find(g_glyphAtlas.begin(), g_glyphAtlas.end(), this);
		if (iter != g_glyphAtlas.end())
			g_glyphAtlas.erase(iter);
	}

	//font
	std::shared_ptr<Font> font()
	{
		return m_font;
	}

	//追加文本，返回实际追加的长度（超过的长度被忽略）
	//返回的Plyph的texureId=-1表示添加失败，已满
	Glyph appendChar(wchar_t ch)
	{
		if (m_glyphs.find(ch) != m_glyphs.end())
			return{ -1 };

		auto glyph = m_font->getGlyphInfo(ch);
		//不再有空余
		if (m_x + glyph.bm_width > m_width && m_y + m_font->size() > m_height)
			return{ -1 };

		glm::vec2 uv[4];

		bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (m_x + glyph.bm_width <= m_width)
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, (int)m_x, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
			uv[0] = { (float)(m_x / width()), (float)(m_y + glyph.bm_height) / height() };
			uv[1] = { (float)(m_x + glyph.bm_width) / width(), (float)(m_y + glyph.bm_height) / height() };
			uv[2] = { (float)(m_x + glyph.bm_width) / width(), (float)m_y / height() }; 
			uv[3] = { (float)m_x / width(), (float)m_y / height() };
			m_x += glyph.bm_width;
		}
		else
		{
			if (m_y + m_font->size() <= m_height)
			{
				m_x = (float)glyph.bm_width;
				m_y += m_font->size();
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
				uv[0] = { 0.0, (float)(m_y + glyph.bm_height) / height() };
				uv[1] = { (float)glyph.bm_width / width(), (float)(m_y + glyph.bm_height) / height() };
				uv[2] = { (float)glyph.bm_width / width(), (float)m_y / height() }; 
				uv[3] = { 0.0, (float)m_y / height() };
			}
		}
		unbind();

		Glyph ret = { (int)m_handle,{ uv[0], uv[1], uv[2], uv[3] }, glyph };
		m_glyphs.insert({ ch, ret });
		return ret;
	}

	void appendText(const std::wstring &unicodeStr)
	{
		for (auto const &ch : unicodeStr)
			appendChar(ch);
	}

	//获取一个字符的信息
	//如果存在返回存在的字形，否则新建一个新字形，并存储下来；倘若TextureGlyphAtlas已满则不允许新建
	//最终返回的Glyph.texureId为-1
	Glyph getGlyph(wchar_t ch)
	{
		auto iter = m_glyphs.find(ch);
		return (iter != m_glyphs.end()) ? iter->second : appendChar(ch);
	}

private:
	float						m_x;
	float						m_y;
	std::map<wchar_t, Glyph>	m_glyphs;
	std::shared_ptr<Font>		m_font;
};

constexpr wchar_t highFrequencyWhars[] = {
	'a', 'b', '\0'
};

Glyph GlyphFactory::getGlyph(wchar_t ch)
{
	if (g_glyphAtlas.empty())
	{
		auto font = std::make_shared<Font>("../../resource/STKAITI.TTF", 130);
		auto firstTextureGlyphAtlas = new TextureGlyphAtlas(font, highFrequencyWhars);
	}

	Glyph ret;
	for (auto &atlas : g_glyphAtlas)
	{
		ret = atlas->getGlyph(ch);
		if (ret.texureId != -1)
			return ret;
	}

	auto newAtlas = new TextureGlyphAtlas(g_glyphAtlas[0]->font(), L"");
	return newAtlas->getGlyph(ch);
}
