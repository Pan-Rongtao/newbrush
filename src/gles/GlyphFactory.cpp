#include "gles/GlyphFactory.h"
#include <map>
#include <vector>
#include "gles/Texture2D.h"
#include <opengl/GLES2/gl2.h>
#include <freetype/ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftbitmap.h>
#include "core/Log.h"
#include "media/Font.h"
#include FT_FREETYPE_H

using namespace nb::core;
using namespace nb::media;
using namespace nb::gl;

class TextureGlyphAtlas;
static std::vector<TextureGlyphAtlas *>	g_glyphAtlas;
constexpr int							GlyphAltasWidth		= 1024;
constexpr int							GlyphAltasHeight	= 1024;

class NB_API TextureGlyphAtlas : public Texture2D
{
public:
	//构建一个字形图集纹理，宽高为width, height，字形的尺寸为glypSize
	TextureGlyphAtlas(std::shared_ptr<nb::media::Font> font, const std::wstring &unicodeStr)
		: Texture2D(GlyphAltasWidth, GlyphAltasHeight) , m_x(0) , m_y(0) , m_font(font)
	{
		if ((width() != 0 && height() != 0) && (width() % m_font->size() != 0 || height() % m_font->size() != 0))
			nb::Log::warn("width or height mod glypSize != 0");

		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width(), height(), 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
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

	//获取一个字符的信息
	//如果存在返回存在的字形，否则新建一个新字形，并存储下来；倘若TextureGlyphAtlas已满则不允许新建，最终返回的Glyph.texureId为-1
	std::shared_ptr<Glyph> getGlyph(wchar_t ch)
	{
		auto iter = m_glyphs.find(ch);
		return (iter != m_glyphs.end()) ? iter->second : appendChar(ch);
	}

	//返回的Plyph的texureId=-1表示添加失败，已满
	std::shared_ptr<Glyph> appendChar(wchar_t ch)
	{
		if (m_glyphs.find(ch) != m_glyphs.end())
			return{ nullptr };

		auto glyph = GlyphMetrics::measureGlyp(font(), ch);
		//不再有空余
		if (m_x + glyph.bm_width > width() && m_y + m_font->size() > height())
			return{ nullptr };

		glm::vec2 uv[4];

		bind();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (m_x + glyph.bm_width <= width())
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, (int)m_x, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
			uv[0] = { m_x / width(), (m_y + glyph.bm_height) / height() };
			uv[1] = { (m_x + glyph.bm_width) / width(), (m_y + glyph.bm_height) / height() };
			uv[2] = { (m_x + glyph.bm_width) / width(), m_y / height() }; 
			uv[3] = { m_x / width(), m_y / height() };
			m_x += glyph.bm_width;
		}
		else
		{
			if (m_y + m_font->size() <= height())
			{
				m_x = static_cast<float>(glyph.bm_width);
				m_y += m_font->size();
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, (int)m_y, glyph.bm_width, glyph.bm_height, GL_ALPHA, GL_UNSIGNED_BYTE, glyph.bm_buffer);
				uv[0] = { 0.0, (m_y + glyph.bm_height) / height() };
				uv[1] = { glyph.bm_width / width(), (m_y + glyph.bm_height) / height() };
				uv[2] = { glyph.bm_width / width(), m_y / height() }; 
				uv[3] = { 0.0, m_y / height() };
			}
		}
		unbind();

		std::shared_ptr<Glyph> ret = std::make_shared<Glyph>();
		ret->texureId = m_handle;
		ret->info = glyph;
		ret->uv[0] = uv[0];
		ret->uv[1] = uv[1];
		ret->uv[2] = uv[2];
		ret->uv[3] = uv[3];
		m_glyphs.insert({ ch, ret });
		return ret;
	}

	void appendText(const std::wstring &unicodeStr)
	{
		for (auto const &ch : unicodeStr)
			appendChar(ch);
	}

private:
	float										m_x;
	float										m_y;
	std::map<wchar_t, std::shared_ptr<Glyph>>	m_glyphs;
	std::shared_ptr<Font>						m_font;
	friend class GlyphFactory;
};

std::shared_ptr<Glyph> GlyphFactory::getGlyph(std::shared_ptr<Font> font, wchar_t ch)
{
	std::shared_ptr<Glyph> ret;
	for (auto &atlas : g_glyphAtlas)
	{
		ret = atlas->getGlyph(ch);
		if (ret)
			return ret;
	}

	auto newAtlas = new TextureGlyphAtlas(font, L"");
	nb::Log::info("char[%d] at new TextureGlyphAtlas", ch);
	return newAtlas->getGlyph(ch);
}
