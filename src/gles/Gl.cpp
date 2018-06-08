#include "gles/Gl.h"
#include <GLES2/gl2.h>

void nb::gl::Viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}
