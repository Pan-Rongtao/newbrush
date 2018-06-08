#include <GLES2/gl2.h>
#include <assert.h>
#include "gles/TextureUnit.h"

using namespace nb::gl::Gles;

TextureUnit::TextureUnit()
: m_nAddress(GL_TEXTURE0)
{
}

TextureUnit::TextureUnit(int index)
{
	//rewrite when define assert
	assert(index >= 0 && index <= MaxCount());
	m_nAddress = GL_TEXTURE0 + index;	//假如GL_TEXTURE0并不连续，此句会有问题
}

TextureUnit::~TextureUnit()
{
}

int TextureUnit::GetIndex() const
{
	return m_nAddress - GL_TEXTURE0;	//假如GL_TEXTURE0并不连续，此句会有问题
}

int TextureUnit::GlAddress() const
{
	return m_nAddress;
}

void TextureUnit::Activate()
{
	glActiveTexture(m_nAddress);
}

int TextureUnit::MaxCount()
{
	int nRet = -1;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nRet);
	return nRet;
}

TextureUnit TextureUnit::Default()
{
	return TextureUnit();
}

TextureUnit TextureUnit::Activated()
{
	int nRet = 0;
	glGetIntegerv(GL_ACTIVE_TEXTURE, &nRet);
	return TextureUnit(nRet);
}

TextureUnit TextureUnit::FromIndex(int index)
{
	return TextureUnit(index);
}

TextureUnit TextureUnit::FromGlAddress(int glEnumUnitAddress)
{
	return TextureUnit(glEnumUnitAddress - GL_TEXTURE0);	//假如GL_TEXTURE0并不连续，此句会有问题
}
