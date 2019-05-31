#include <GLES2/gl2.h>
#include "gles/Texture2D.h"
#include "gles/Egl.h"

using namespace nb::media;
using namespace nb::gl;

Texture2D::Texture2D()
{
	setWrapping(TextureWrapping());
	setFilter(TextureFilter());
}

Texture2D::Texture2D(const std::string &path)
	: Texture2D(path, TextureWrapping(), TextureFilter())
{
}

Texture2D::Texture2D(const std::string &path, const TextureFilter &filter)
	: Texture2D(path, TextureWrapping(), filter)
{
}

Texture2D::Texture2D(const std::string &path, const TextureWrapping &wrapping, const TextureFilter &filter)
{
	loadFromPath(path);
	setWrapping(wrapping);
	setFilter(filter);
}

Texture2D::Texture2D(const nb::media::Bitmap &bm)
	: Texture2D()
{
	int glFormat;
	int glType;
	bitmapFormatToGlFormat(bm.pixelFormat(), glFormat, glType);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm.width(), bm.height(), 0, glFormat, glType, bm.data());
	unbind();
	m_nPixcelWidth = bm.width();
	m_nPixcelHeight = bm.height();
}

Texture2D::~Texture2D()
{
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapping::glValue(wrapping.s()));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapping::glValue(wrapping.t()));
	unbind();
	m_wrapping = wrapping;
}

void Texture2D::setFilter(const TextureFilter &filter)
{
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilter::glValue(filter.magnifyFilter()));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilter::glValue(filter.narrowFilter()));
	unbind();
	m_filter = filter;
}

void Texture2D::loadFromPath(const std::string &path)
{
	Bitmap bm(path.data());
	int glFormat;
	int glType;
	bitmapFormatToGlFormat(bm.pixelFormat(), glFormat, glType);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm.width(), bm.height(), 0, glFormat, glType, bm.data());
	unbind();
	m_nPixcelWidth = bm.width();
	m_nPixcelHeight = bm.height();
}

void Texture2D::loadFromData(const char *data, int width, int height, Texture::PixelFormat format)
{
	int glFormat = GL_RGBA;
	int glType = GL_UNSIGNED_BYTE;
	switch(format)
	{
	case PixelFormat::Bpp8_Alpha:		glFormat = GL_ALPHA;	glType = GL_UNSIGNED_BYTE;			break;
	case PixelFormat::Bpp16_Rgb565:		glFormat = GL_RGB;		glType = GL_UNSIGNED_SHORT_5_6_5;	break;
	case PixelFormat::Bpp24_Rgb888:		glFormat = GL_RGB;		glType = GL_UNSIGNED_BYTE;			break;
	case PixelFormat::Bpp32_Rgb4444:	glFormat = GL_RGBA;		glType = GL_UNSIGNED_SHORT_4_4_4_4; break;
	case PixelFormat::Bpp32_Rgb5551:	glFormat = GL_RGBA;		glType = GL_UNSIGNED_SHORT_5_5_5_1; break;
	case PixelFormat::Bpp32_Rgba8888:	glFormat = GL_RGBA;		glType = GL_UNSIGNED_BYTE;			break;
	}
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
	unbind();
	m_nPixcelWidth = width;
	m_nPixcelHeight = height;
}

int Texture2D::pixcelWidth() const
{
	return m_nPixcelWidth;
}

int Texture2D::pixcelHeight() const
{
	return m_nPixcelHeight;
}

int Texture2D::maxWidthSupported()
{
	if (!nb::gl::getContext())
		NB_THROW_EXCEPTION(std::logic_error, "context not set, use nb::gl::makeCurrent to set Context");

	int nRet = 0;
	glEnable(GL_TEXTURE_2D);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nRet);
	return nRet;
}

int Texture2D::maxHeightSupported()
{
	return maxWidthSupported();
}
