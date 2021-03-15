#pragma once
#include "newbrush/Core.h"
#if NB_OS == NB_OS_ANDROID
#include <GLES3/gl3.h>
#else
#include "glad/glad.h"
#endif

namespace nb
{

class NB_API GLUnit
{
public:
	static void viewport(int x, int y, int width, int height);
};

}