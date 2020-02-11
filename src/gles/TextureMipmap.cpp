#include <GLES2/gl2.h>
#include "newbrush/gles/TextureMipmap.h"

using namespace nb;

TextureMipmap::TextureMipmap()
{

}

TextureMipmap::~TextureMipmap()
{

}

void TextureMipmap::generate()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}
