#include "gles/Cubemap.h"
#include <GLES2/gl2.h>
#include "media/Bitmap.h"

using namespace nb::gl;
using namespace nb::media;

Cubemap::Cubemap()
{
	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
}

Cubemap::~Cubemap()
{
 
}

void Cubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
}

void Cubemap::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::setWrapping(const TextureWrapping &wrapping)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, TextureWrapping::glValue(wrapping.s()));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, TextureWrapping::glValue(wrapping.t()));
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, TextureWrapping::glValue(wrapping.r()));
	unbind();
	m_wrapping = wrapping;
}

void Cubemap::setFilter(const TextureFilter &filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, TextureFilter::glValue(filter.magnifyFilter()));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, TextureFilter::glValue(filter.narrowFilter()));
	unbind();
	m_filter = filter;
}

void Cubemap::load(const std::vector<std::string> &paths)
{
	Bitmap bms[6];
	int glFormat[6];
	int glType[6];
	for (int i = 0; i != paths.size(); ++i)
	{
		bms[i].loadFile(paths[i].data());
		bitmapFormatToGlFormat(bms[i].pixelFormat(), glFormat[i], glType[i]);
	}

	bind();
	for (int i = 0; i != paths.size(); ++i)
	{
		int x = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(x, 0, glFormat[i], bms[i].width(), bms[i].height(), 0, glFormat[i], glType[i], bms[i].data());
	}
	unbind();
}