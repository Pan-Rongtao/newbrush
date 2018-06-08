#include <GLES2/gl2.h>
#include "gles/TextureMipmap.h"

using nb::gl::Gles::TextureMipmap;

TextureMipmap::TextureMipmap()
{

}

TextureMipmap::~TextureMipmap()
{

}

void TextureMipmap::Generate()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}
