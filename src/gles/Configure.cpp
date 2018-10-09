#include "gles/Configure.h"
#include "gles/Egl.h"
#include "core/Exception.h"
#include <EGL/egl.h>

using namespace nb::gl;

Configure::Configure()
: m_handle(nullptr)
{
}

Configure::Configure(int *attributes)
: m_handle(nullptr)
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
	EGLint	numConfigs(0);
	eglChooseConfig(nb::gl::getCurrentDisplay().handle(), attribs, &m_handle, 1, &numConfigs);
}

bool Configure::isNull() const
{
	return m_handle == nullptr;
}

int *Configure::attributes() const
{
	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	int *ret = nullptr;
	EGLBoolean b = eglGetConfigAttrib(nb::gl::getCurrentDisplay().handle(), m_handle, 0, ret);
	if(!b)
		NB_THROW_EXCEPTION("configure get attributes fail.");

	return ret;
}

void *Configure::handle() const
{
	return m_handle;
}

int Configure::systemRecommendMaxSupportCount()
{
	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLint count = 0;
	EGLBoolean b = eglGetConfigs(nb::gl::getCurrentDisplay().handle(), nullptr, 0, &count);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	return count;
}

Configure Configure::fromSystemRecommend(int index)
{
	int maxCount = systemRecommendMaxSupportCount();
	if(index < 0 || index >= maxCount)
		NB_THROW_EXCEPTION("index out bound.");

	if(nb::gl::getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLConfig *eglHandle = new EGLConfig[maxCount];
	int x = 0;
	EGLBoolean b = eglGetConfigs(nb::gl::getCurrentDisplay().handle(), eglHandle, maxCount, &x);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	Configure ret;
	ret.m_handle = eglHandle[index];
	delete []eglHandle;
	return ret;
}
