#include <GLES2/gl2.h>
#include "gles/TextureWrapping.h"

using nb::gl::Gles::TextureWrapping;

TextureWrapping::TextureWrapping()
{
}

TextureWrapping::TextureWrapping(TextureWrapping::WrappingMode s, TextureWrapping::WrappingMode t)
: m_s(s)
, m_t(t)
, m_BorderColor(0.0f, 0.0f, 0.0f, 1.0f)
{
}

TextureWrapping::TextureWrapping(TextureWrapping::WrappingMode s, TextureWrapping::WrappingMode t, const nb::Math::Vec4 &borderColor)
: m_s(s)
, m_t(t)
, m_BorderColor(borderColor)
{
}

TextureWrapping::WrappingMode TextureWrapping::GetS() const
{
	return m_s;
}

TextureWrapping::WrappingMode TextureWrapping::GetT() const
{
	return m_t;
}

int TextureWrapping::ToGlValue(TextureWrapping::WrappingMode wrapping)
{
	GLint nGl = GL_REPEAT;
	switch(wrapping)
	{
	case WrappingMode_Repeat:				nGl = GL_REPEAT;							break;
	case WrappingMode_Mirrored_Repeat:		nGl = GL_MIRRORED_REPEAT;					break;
	case WrappingMode_Clamp_To_Edge:		nGl = GL_CLAMP_TO_EDGE;						break;
	case WrappingMode_Clamp_To_Border:		printf("warning, not in opengl es 2.0");	break;
	default:																			break;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, nGl);
	return nGl;
}
