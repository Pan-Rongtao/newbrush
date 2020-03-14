#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "newbrush/gles/Texture.h"
#include "newbrush/core/Log.h"

using namespace nb;

int TextureWrapping::glValue(TextureWrapping::WrappingModeE wrapping)
{
	GLint nGl = GL_REPEAT;
	switch (wrapping)
	{
	case WrappingModeE::Repeat:				nGl = GL_REPEAT;					break;
	case WrappingModeE::MirroredRepeat:		nGl = GL_MIRRORED_REPEAT;			break;
	case WrappingModeE::ClampToEdge:		nGl = GL_CLAMP_TO_EDGE;				break;
	case WrappingModeE::ClampToBorder:		Log::warn("not in opengl es 2.0");	break;
	default:																	break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nGl);
	return nGl;
}

int TextureFilter::glValue(TextureFilter::FilterE filter)
{
	GLint nGl = GL_NEAREST;
	switch (filter)
	{
	case FilterE::Point:		nGl = GL_NEAREST;																break;
	case FilterE::Bilinear:		nGl = GL_LINEAR;																break;
	case FilterE::Trilinear:	nGl = GL_LINEAR_MIPMAP_LINEAR;													break;
	case FilterE::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT;	Log::warn("check if gpu supports\n");	break;
	default:																									break;
	}
	return nGl;
}

//class Texture
Texture::Texture()
	: m_samplerUnit(0)
{
	glGenTextures(1, &m_handle);
	if (glGetError() == GL_INVALID_OPERATION)
	{
		nbThrowException(std::logic_error, "gl configure has not set.");
	}
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

void Texture::setSamplerUnit(const uint8_t & unit)
{
	m_samplerUnit = unit;
}

uint8_t Texture::samplerUnit()
{
	return m_samplerUnit;
}

void Texture::bitmapFormatToGlFormat(int bmChannels, int &glInteralFormat, int &glPixcelDepth) const
{
	switch(bmChannels)
	{
	case 1:	glInteralFormat = GL_ALPHA;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
	case 2:	glInteralFormat = GL_RGB;		glPixcelDepth = GL_UNSIGNED_SHORT_5_6_5;	break;
	case 3:	glInteralFormat = GL_RGB;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
//	case Bitmap::Format_Bpp16_Argb4444:	glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_SHORT_4_4_4_4;	break;
//	case Bitmap::Format_Bpp1_Mono:		glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_SHORT_5_5_5_1;	break;
	case 4:	glInteralFormat = GL_RGBA;		glPixcelDepth = GL_UNSIGNED_BYTE;			break;
	default: nbThrowException(std::invalid_argument, "bmChannels[%d] is invalid", bmChannels);	break;
	}
}
