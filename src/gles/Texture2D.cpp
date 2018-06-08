#include <GLES2/gl2.h>
#include "gles/Texture2D.h"

using nb::System::String;
using nb::gl::Gles::Texture;
using nb::gl::Gles::Texture2D; 
using nb::gl::Gles::TextureWrapping;
using nb::gl::Gles::TextureFilter;
using nb::Media::Bitmap;

Texture2D::Texture2D()
: m_nPixcelWidth(0)
, m_nPixcelHeight(0)
{
	SetTextureWrapping(TextureWrapping());
	SetTextureFilter(TextureFilter());
}

Texture2D::Texture2D(const nb::System::String &path)
: m_nPixcelWidth(0)
, m_nPixcelHeight(0)
{
	LoadFromPath(path);
	SetTextureWrapping(TextureWrapping());
	SetTextureFilter(TextureFilter());
}

Texture2D::Texture2D(const nb::System::String &path, const TextureFilter &filter)
: m_nPixcelWidth(0)
, m_nPixcelHeight(0)
{
	LoadFromPath(path);
	SetTextureWrapping(TextureWrapping());
	SetTextureFilter(filter);
}

Texture2D::Texture2D(const nb::System::String &path, const TextureWrapping &wrapping, const TextureFilter &filter)
: m_nPixcelWidth(0)
, m_nPixcelHeight(0)
{
	LoadFromPath(path);
	SetTextureWrapping(wrapping);
	SetTextureFilter(filter);
}

Texture2D::Texture2D(const char *data, int width, int height, Texture::PixelFormat format)
{
	LoadFromData(data, width, height, format);
}

Texture2D::~Texture2D()
{
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
}

void Texture2D::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetTextureWrapping(const TextureWrapping &wrapping)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapping::ToGlValue(wrapping.GetS()));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapping::ToGlValue(wrapping.GetT()));
	Unbind();
	m_Wrapping = wrapping;
}

void Texture2D::SetTextureFilter(const TextureFilter &filter)
{
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilter::ToGlValue(filter.GetMagnifyFilter()));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilter::ToGlValue(filter.GetNarrowFilter()));
	Unbind();
	m_Filter = filter;
}

void Texture2D::LoadFromPath(const String &path)
{
	Bitmap bm(path);
	int glFormat;
	int glType;
	BitmapFormatToGlFormat(bm.GetPixelFormat(), glFormat, glType);
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm.GetWidth(), bm.GetHeight(), 0, glFormat, glType, bm.GetData());
	Unbind();
	m_nPixcelWidth = bm.GetWidth();
	m_nPixcelHeight = bm.GetHeight();
}

void Texture2D::LoadFromData(const char *data, int width, int height, Texture::PixelFormat format)
{
	int glFormat = GL_RGBA;
	int glType = GL_UNSIGNED_BYTE;
	switch(format)
	{
	case Texture::Format_Bpp8_Alpha:		glFormat = GL_ALPHA;	glType = GL_UNSIGNED_BYTE; break;
	case Texture::Format_Bpp16_Rgb565:		glFormat = GL_RGB;		glType = GL_UNSIGNED_SHORT_5_6_5; break;
	case Texture::Format_Bpp24_Rgb888:		glFormat = GL_RGB;		glType = GL_UNSIGNED_BYTE; break;
	case Texture::Format_Bpp32_Rgb4444:		glFormat = GL_RGBA;		glType = GL_UNSIGNED_SHORT_4_4_4_4; break;
	case Texture::Format_Bpp32_Rgb5551:		glFormat = GL_RGBA;		glType = GL_UNSIGNED_SHORT_5_5_5_1; break;
	case Texture::Format_Bpp32_Rgba8888:	glFormat = GL_RGBA;		glType = GL_UNSIGNED_BYTE; break;
	}
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
	Unbind();
	m_nPixcelWidth = width;
	m_nPixcelHeight = height;
}

int Texture2D::GetPixcelWidth() const
{
	return m_nPixcelWidth;
}

int Texture2D::GetPixcelHeight() const
{
	return m_nPixcelHeight;
}

int Texture2D::MaxWidthSupported()
{
	int nRet = 0;
	glEnable(GL_TEXTURE_2D);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &nRet);
	return nRet;
}

int Texture2D::MaxHeightSupported()
{
	return MaxWidthSupported();
}
