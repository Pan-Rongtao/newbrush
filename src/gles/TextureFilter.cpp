#include <assert.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include "gles/TextureFilter.h"

using namespace nb::gl::Gles;

TextureFilter::TextureFilter()
: m_MagnifyFilter(Point)
, m_NarrowFilter(Point)
{
}

TextureFilter::TextureFilter(Filter uniformFilter)
: m_MagnifyFilter(uniformFilter)
, m_NarrowFilter(uniformFilter)
{
}

TextureFilter::TextureFilter(Filter magnify, Filter narrow)
: m_MagnifyFilter(magnify)
, m_NarrowFilter(narrow)
{
}

TextureFilter::Filter TextureFilter::GetMagnifyFilter() const
{
	return m_MagnifyFilter;
}

TextureFilter::Filter TextureFilter::GetNarrowFilter() const
{
	return m_NarrowFilter;
}

TextureFilter TextureFilter::Default()
{
	return Filter();
}

int TextureFilter::ToGlValue(TextureFilter::Filter filter)
{
	GLint nGl = GL_NEAREST;
	switch(filter)
	{
	case TextureFilter::Point:			nGl = GL_NEAREST;																	break;
	case TextureFilter::Bilinear:		nGl = GL_LINEAR;																	break;
	case TextureFilter::Trilinear:		nGl = GL_LINEAR_MIPMAP_LINEAR;														break;
	case TextureFilter::Anisotropic:	nGl = GL_TEXTURE_MAX_ANISOTROPY_EXT;	printf("warning, check if gpu supports\n");	break;
	default:																												break;
	}
	return nGl;
}
