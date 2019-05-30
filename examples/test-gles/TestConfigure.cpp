#include "TestConfigure.h"
#include <opengl/EGL/egl.h>

void TestConfigure::test()
{
	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE,24,
		EGL_SAMPLE_BUFFERS, 1,
		EGL_SAMPLES, 4,
		EGL_NONE
	};

	Configure c(nullptr, attribs);
}
