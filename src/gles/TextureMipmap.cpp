#include <GLES2/gl2.h>
#include "newbrush/gles/TextureMipmap.h"

using namespace nb;

void TextureMipmap::update(const unsigned char * data, int width, int height, int glFormat, int glType)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, width, height, 0, glFormat, glType, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	unbind();
}