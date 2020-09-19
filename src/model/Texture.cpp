#include "newbrush/model/Texture.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "newbrush/model/Log.h"

using namespace nb;

int TextureWrapping::glValue(TextureWrapping::WrappingModeE wrapping)
{
	GLint nGl = GL_REPEAT;
	switch (wrapping)
	{
	case WrappingModeE::Repeat:				nGl = GL_REPEAT;					break;
	case WrappingModeE::MirroredRepeat:		nGl = GL_MIRRORED_REPEAT;			break;
	case WrappingModeE::ClampToEdge:		nGl = GL_CLAMP_TO_EDGE;				break;
	case WrappingModeE::ClampToBorder:		Log::error("not supported in opengl es 2.0");	break;
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
	case FilterE::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT; Log::error("check if gpu supports");	break;
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

////////////////////
Texture2D::Texture2D()
{
	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture2D::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setWrapping(const TextureWrapping &wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapping::glValue(wrapping.s));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapping::glValue(wrapping.t));
	unbind();
	m_wrapping = wrapping;
}

void Texture2D::setFilter(const TextureFilter &filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilter::glValue(filter.magnifyFilter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilter::glValue(filter.narrowFilter));
	unbind();
	m_filter = filter;
}

void Texture2D::update(const unsigned char * data, int width, int height, int glFormat, int glType)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
	unbind();
}

int Texture2D::maxWidthSupported()
{
	int nRet = 0;
	glEnable(GL_TEXTURE_2D);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nRet);
	return nRet;
}

int Texture2D::maxHeightSupported()
{
	return maxWidthSupported();
}

/////////////////
TextureCubemap::TextureCubemap()
{
	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
}

void TextureCubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
}

void TextureCubemap::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCubemap::setWrapping(const TextureWrapping &wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, TextureWrapping::glValue(wrapping.s));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, TextureWrapping::glValue(wrapping.t));
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, TextureWrapping::glValue(wrapping.r()));
	unbind();
	m_wrapping = wrapping;
}

void TextureCubemap::setFilter(const TextureFilter &filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, TextureFilter::glValue(filter.magnifyFilter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, TextureFilter::glValue(filter.narrowFilter));
	unbind();
	m_filter = filter;
}

void TextureCubemap::update(unsigned int index, const unsigned char * data, int width, int height, int glFormat, int glType)
{
	if (index >= 6)
	{
		nbThrowException(std::out_of_range, "index[%d] is out of range[0, 6)", index);
	}

	bind();
	glTexImage2D(index, 0, glFormat, width, height, 0, glFormat, glType, data);
	unbind();
}

/////////////
void TextureMipmap::update(const unsigned char * data, int width, int height, int glFormat, int glType)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}