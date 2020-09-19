#include "newbrush/rvl/gles/Texture.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

using namespace nb;

int TextureWrapping::glValue(TextureWrapping::WrappingModeE wrapping)
{
	GLint nGl = GL_REPEAT;
	switch (wrapping)
	{
	case WrappingModeE::Repeat:				nGl = GL_REPEAT;					break;
	case WrappingModeE::MirroredRepeat:		nGl = GL_MIRRORED_REPEAT;			break;
	case WrappingModeE::ClampToEdge:		nGl = GL_CLAMP_TO_EDGE;				break;
	case WrappingModeE::ClampToBorder:		printf("not in opengl es 2.0\n");	break;
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
	case FilterE::Point:		nGl = GL_NEAREST;															break;
	case FilterE::Bilinear:		nGl = GL_LINEAR;															break;
	case FilterE::Trilinear:	nGl = GL_LINEAR_MIPMAP_LINEAR;												break;
	case FilterE::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT;	printf("check if gpu supports\n");	break;
	default:																								break;
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

void Texture::setSamplerUnit(int unit)
{
	m_samplerUnit = unit;
}

int Texture::samplerUnit()
{
	return m_samplerUnit;
}

void Texture::active()
{
	glActiveTexture(m_samplerUnit);
}

std::pair<int, int> Texture::getGlFormatAndType(int bmChannels)
{
	switch (bmChannels)
	{
	case 1:	return{ GL_LUMINANCE, GL_UNSIGNED_BYTE };
	case 2:	return{ GL_RGB, GL_UNSIGNED_SHORT_5_6_5 };
	case 3:	return{ GL_RGB, GL_UNSIGNED_BYTE };
	case 4:	return{ GL_RGBA, GL_UNSIGNED_BYTE };
	default: nbThrowException(std::invalid_argument, "bmChannels[%d] is invalid", bmChannels);	break;
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}
