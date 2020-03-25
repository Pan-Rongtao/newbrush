#include <GLES2/gl2.h>
#include "newbrush/gles/TextureMipmap.h"

using namespace nb;

TextureMipmap::TextureMipmap(const Bitmap &bm)
{
	int glFormat;
	int glType;
	bitmapFormatToGlFormat(bm.channels(), glFormat, glType);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, glFormat, bm.width(), bm.height(), 0, glFormat, glType, bm.data());
	generate();
	unbind();
}

TextureMipmap::~TextureMipmap()
{

}

void TextureMipmap::generate()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}
