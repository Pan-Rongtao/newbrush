#include "newbrush/model/Texture.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "newbrush/model/Log.h"

using namespace nb;

int glWrapping(TextureWrappingE wrapping)
{
	GLint nGl = GL_REPEAT;
	switch (wrapping)
	{
	case TextureWrappingE::Repeat:			nGl = GL_REPEAT;					break;
	case TextureWrappingE::MirroredRepeat:	nGl = GL_MIRRORED_REPEAT;			break;
	case TextureWrappingE::ClampToEdge:		nGl = GL_CLAMP_TO_EDGE;				break;
	case TextureWrappingE::ClampToBorder:	Log::error("not supported in opengl es 2.0");	break;
	default:																	break;
	}
	return nGl;
}

int glFilter(TextureFilterE filter)
{
	GLint nGl = GL_NEAREST;
	switch (filter)
	{
	case TextureFilterE::Point:			nGl = GL_NEAREST;															break;
	case TextureFilterE::Bilinear:		nGl = GL_LINEAR;															break;
	case TextureFilterE::Trilinear:		nGl = GL_LINEAR_MIPMAP_LINEAR;												break;
	case TextureFilterE::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT; Log::error("check if gpu supports");	break;
	default:																										break;
	}
	return nGl;
}

Texture::Texture(TextureTypeE type)
	: m_wrappingS(TextureWrappingE::Repeat)
	, m_wrappingT(TextureWrappingE::Repeat)
	, m_magnifyFilter(TextureFilterE::Point)
	, m_narrowFilter(TextureFilterE::Point)
	, m_samplerUnit(0)
	, m_type(type)
{
	glGenTextures(1, &m_handle);
	auto err = glGetError();
	if (err != GL_NO_ERROR)
	{
		nbThrowException(std::logic_error, "glGenTextures fail, error=%d", err);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_handle);
}

void Texture::active()
{
	glActiveTexture(m_samplerUnit);
}

void Texture::bind()
{
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glBindTexture(GL_TEXTURE_2D, m_handle);									break;
	case TextureTypeE::TextureCubemap:	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);							break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type); break;
	}
}

void Texture::unbind()
{
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glBindTexture(GL_TEXTURE_2D, 0);										break;
	case TextureTypeE::TextureCubemap:	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);									break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type); break;
	}
}

void Texture::setWrappingS(TextureWrappingE wrapping)
{
	bind();
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapping(wrapping));		break;
	case TextureTypeE::TextureCubemap:	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, glWrapping(wrapping));	break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type);			break;
	}
	unbind();
	m_wrappingS = wrapping;
}

void Texture::setWrappingT(TextureWrappingE wrapping)
{
	bind();
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapping(wrapping));		break;
	case TextureTypeE::TextureCubemap:	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, glWrapping(wrapping));	break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type);			break;
	}
	unbind();
	m_wrappingT = wrapping;
}

TextureWrappingE Texture::wrappingS() const
{
	return m_wrappingS;
}

TextureWrappingE Texture::wrappingT() const
{
	return m_wrappingT;
}

void Texture::setMagnifyFilter(TextureFilterE filter)
{
	bind();
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFilter(filter));		break;
	case TextureTypeE::TextureCubemap:	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, glFilter(filter));	break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type);			break;
	}
	unbind(); 
}

void Texture::setNarrowFilter(TextureFilterE filter)
{
	bind();
	switch (m_type)
	{
	case TextureTypeE::Texture2D:		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFilter(filter));		break;
	case TextureTypeE::TextureCubemap:	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, glFilter(filter));	break;
	default:							nbThrowException(std::logic_error, "unknown texture type[%d]", m_type);			break;
	}
	unbind();
}

TextureFilterE Texture::magnifyFilter() const
{
	return m_magnifyFilter;
}

TextureFilterE Texture::narrowFilter() const
{
	return m_narrowFilter;
}

void Texture::setSamplerUnit(int unit)
{
	m_samplerUnit = unit;
}

int Texture::samplerUnit()
{
	return m_samplerUnit;
}

void Texture::update(uint32_t index, const unsigned char * data, int width, int height, int glFormat, int glType)
{
	bind();
	switch (m_type)
	{
	case TextureTypeE::Texture2D:
	{
		glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
		break;
	}
	case TextureTypeE::TextureCubemap:
	{
		if (index >= 6)
		{
			nbThrowException(std::out_of_range, "index[%d] is out of range[0, 6)", index);
		}
		glTexImage2D(index, 0, glFormat, width, height, 0, glFormat, glType, data);
		break;
	}
	default:	nbThrowException(std::logic_error, "unknown texture type[%d]", m_type); break;
	}
	unbind();
}

void Texture::genMipmap()
{
	if (m_type != TextureTypeE::Texture2D)
	{
		nbThrowException(std::logic_error, "not a texture2d type");
	}
	bind();
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}

std::pair<int, int> Texture::getGlFormatAndType(int channels)
{
	switch (channels)
	{
	case 1:	return{ GL_LUMINANCE, GL_UNSIGNED_BYTE };
	case 2:	return{ GL_RGB, GL_UNSIGNED_SHORT_5_6_5 };
	case 3:	return{ GL_RGB, GL_UNSIGNED_BYTE };
	case 4:	return{ GL_RGBA, GL_UNSIGNED_BYTE };
	default: nbThrowException(std::invalid_argument, "channels[%d] is invalid", channels);	break;
	}
}
