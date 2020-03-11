#include "newbrush/gles/TextureCubemap.h"
#include <GLES2/gl2.h>
#include "newbrush/media/Bitmap.h"

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

void TextureCubemap::load(const std::vector<std::string> &paths)
{
	Bitmap bms[6];
	int glFormat[6] = { 0 };
	int glType[6] = { 0 };
	for (int i = 0; i != paths.size(); ++i)
	{
		bms[i].load(paths[i].data());
		bitmapFormatToGlFormat(bms[i].channels(), glFormat[i], glType[i]);
	}

	bind();
	for (int i = 0; i != paths.size(); ++i)
	{
		int x = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(x, 0, glFormat[i], bms[i].width(), bms[i].height(), 0, glFormat[i], glType[i], bms[i].data());
	}
	unbind();
}