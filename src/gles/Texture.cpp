#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "gles/Texture.h"
#include "core/Exception.h"

using namespace nb::core;
using namespace nb::media;
using namespace nb::gl;

//class TexutreWrapping
TextureWrapping::TextureWrapping()
{
}

TextureWrapping::TextureWrapping(TextureWrapping::WrappingMode s, TextureWrapping::WrappingMode t)
	: m_s(s)
	, m_t(t)
	, m_BorderColor(0.0f, 0.0f, 0.0f, 1.0f)
{
}

TextureWrapping::TextureWrapping(TextureWrapping::WrappingMode s, TextureWrapping::WrappingMode t, const Vec4 &borderColor)
	: m_s(s)
	, m_t(t)
	, m_BorderColor(borderColor)
{
}

TextureWrapping::WrappingMode TextureWrapping::s() const
{
	return m_s;
}

TextureWrapping::WrappingMode TextureWrapping::t() const
{
	return m_t;
}

int TextureWrapping::glValue(TextureWrapping::WrappingMode wrapping)
{
	GLint nGl = GL_REPEAT;
	switch (wrapping)
	{
	case WrappingMode_Repeat:				nGl = GL_REPEAT;							break;
	case WrappingMode_Mirrored_Repeat:		nGl = GL_MIRRORED_REPEAT;					break;
	case WrappingMode_Clamp_To_Edge:		nGl = GL_CLAMP_TO_EDGE;						break;
	case WrappingMode_Clamp_To_Border:		printf("warning, not in opengl es 2.0");	break;
	default:																			break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nGl);
	return nGl;
}

//class TextureFilter
TextureFilter::TextureFilter()
	: m_MagnifyFilter(Point)
	, m_NarrowFilter(Point)
{
}

TextureFilter::TextureFilter(Filter uniformFilter)
	: m_MagnifyFilter(uniformFilter)
	, m_NarrowFilter(uniformFilter)
{
}

TextureFilter::TextureFilter(Filter magnify, Filter narrow)
	: m_MagnifyFilter(magnify)
	, m_NarrowFilter(narrow)
{
}

TextureFilter::Filter TextureFilter::magnifyFilter() const
{
	return m_MagnifyFilter;
}

TextureFilter::Filter TextureFilter::narrowFilter() const
{
	return m_NarrowFilter;
}

TextureFilter TextureFilter::defaultx()
{
	return Filter();
}

int TextureFilter::glValue(TextureFilter::Filter filter)
{
	GLint nGl = GL_NEAREST;
	switch (filter)
	{
	case TextureFilter::Point:			nGl = GL_NEAREST;																	break;
	case TextureFilter::Bilinear:		nGl = GL_LINEAR;																	break;
	case TextureFilter::Trilinear:		nGl = GL_LINEAR_MIPMAP_LINEAR;														break;
	case TextureFilter::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT;	printf("warning, check if gpu supports\n");	break;
	default:																												break;
	}
	return nGl;
}

//class Texture
Texture::Texture()
{
	glGenTextures(1, &m_handle);
	if (glGetError() == GL_INVALID_OPERATION)
		throw nb::core::LogicException(__FILE__, __LINE__);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}

TextureWrapping &Texture::wrapping()
{
	return m_wrapping;
}

const TextureWrapping &Texture::wrapping() const
{
	return m_wrapping;
}

TextureFilter &Texture::filter()
{
	return m_filter;
}

const TextureFilter &Texture::filter() const
{
	return m_filter;
}

void Texture::bitmapFormatToGlFormat(nb::media::Bitmap::PixelFormat bmFormat, int &glInteralFormat, int &glPixcelDepth) const
{
	switch(bmFormat)
	{
	case Bitmap::Format_Bpp8_Palette:	glInteralFormat = GL_ALPHA;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
	case Bitmap::Format_Bpp16_Rgb565:	glInteralFormat = GL_RGB;		glPixcelDepth = GL_UNSIGNED_SHORT_5_6_5;	break;
	case Bitmap::Format_Bpp24_Rgb888:	glInteralFormat = GL_RGB;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
//	case Bitmap::Format_Bpp16_Argb4444:	glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_SHORT_4_4_4_4;	break;
//	case Bitmap::Format_Bpp1_Mono:		glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_SHORT_5_5_5_1;	break;
	case Bitmap::Format_Bpp32_Rgba8888:	glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
	default:							glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
	}
}
