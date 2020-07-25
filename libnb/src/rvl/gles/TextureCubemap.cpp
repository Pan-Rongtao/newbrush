#include "newbrush/rvl/gles/TextureCubemap.h"
#include <GLES2/gl2.h>

using namespace nb;

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
