#include <GLES2/gl2.h>
#include "newbrush/gles/Texture2D.h"

using namespace nb;

Texture2D::Texture2D()
{
	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
}

Texture2D::Texture2D(uint32_t id)
{
	m_handle = id;
}

Texture2D::Texture2D(unsigned int width, unsigned int height)
	: m_width(width)
	, m_height(height)
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

unsigned int Texture2D::width() const
{
	return m_width;
}

unsigned int Texture2D::height() const
{
	return m_height;
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
