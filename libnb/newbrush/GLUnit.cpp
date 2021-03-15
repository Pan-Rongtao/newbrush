#include "GLUnit.h"

using namespace nb;

void GLUnit::viewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}
