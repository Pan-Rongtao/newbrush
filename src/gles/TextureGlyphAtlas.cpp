#include "gles/TextureGlyphAtlas.h"
#include <opengl/GLES2/gl2.h>
#include <freetype/ft2build.h>
#include <freetype/ftglyph.h>
#include <freetype/ftbitmap.h>
#include "media/FontFamily.h"
#include FT_FREETYPE_H

using namespace nb::gl;

TextureGlyphAtlas::TextureGlyphAtlas(uint32_t width, uint32_t height, uint32_t glypSize)
	: Texture2D(width, height)
	, m_glypSize(glypSize)
	, m_x(0)
	, m_y(0)
	, m_face("../../../resource/STKAITI.TTF")
{
	if ((width != 0 && height != 0 && glypSize != 0) && (width % glypSize != 0 || height % glypSize != 0))
		printf("warning: width or height mod glypSize != 0\n");

	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_width, m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	unbind();
	m_face.setFontSize(glypSize);
}

uint32_t TextureGlyphAtlas::appendChar(wchar_t unicode)
{
	return appendText(std::wstring(unicode, 1));
}
#include "media/Bitmap.h"
uint32_t TextureGlyphAtlas::appendText(const std::wstring & unicodeStr)
{
	bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	size_t i = 0;
/*	for (; i != unicodeStr.size(); ++i)
	{
		auto ch = unicodeStr[i];
		m_face.loadChar(ch);
		if (m_x + m_face.get()->glyph->bitmap.width <= m_width)
		{
			glTexSubImage2D(GL_TEXTURE_2D, 0, m_x, m_y, m_face.get()->glyph->bitmap.width, m_face.get()->glyph->bitmap.rows,
				GL_ALPHA, GL_UNSIGNED_BYTE, m_face.get()->glyph->bitmap.buffer);
			m_x += m_face.get()->glyph->bitmap.width;
		}
		else
		{
			m_x = 0;
			m_y += m_glypSize;
			glTexSubImage2D(GL_TEXTURE_2D, 0, m_x, m_y, m_face.get()->glyph->bitmap.width, m_face.get()->glyph->bitmap.rows,
				GL_ALPHA, GL_UNSIGNED_BYTE, m_face.get()->glyph->bitmap.buffer);
		}
	};*/
	auto bmGlyph = m_face.loadChar(unicodeStr[0]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, bmGlyph->bitmap.width, bmGlyph->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, bmGlyph->bitmap.buffer);


	unbind();
	return i;
}
