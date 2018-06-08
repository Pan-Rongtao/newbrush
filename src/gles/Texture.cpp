#include <GLES2/gl2.h>
#include "gles/Texture.h"

using nb::Media::Bitmap;
using nb::gl::Gles::Texture;
using nb::gl::Gles::TextureWrapping;
using nb::gl::Gles::TextureFilter;

Texture::Texture()
{
	glGenTextures(1, &m_TextureHandle);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureHandle);
}

TextureWrapping &Texture::GetTextureWrapping()
{
	return m_Wrapping;
}

const TextureWrapping &Texture::GetTextureWrapping() const
{
	return m_Wrapping;
}

TextureFilter &Texture::GetTexureFilter()
{
	return m_Filter;
}

const TextureFilter &Texture::GetTexureFilter() const
{
	return m_Filter;
}

void Texture::BitmapFormatToGlFormat(nb::Media::Bitmap::PixelFormat bmFormat, int &glInteralFormat, int &glPixcelDepth) const
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
