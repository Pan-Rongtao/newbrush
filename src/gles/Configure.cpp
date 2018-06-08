#include "gles/Configure.h"
#include "gles/Egl.h"
#include "core/Exception.h"
#include <EGL/egl.h>

using nb::gl::egl::Configure;

Configure::Configure()
: m_Handle(NULL)
{

}

Configure::Configure(int *attributes)
: m_Handle(NULL)
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
	eglChooseConfig(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), attribs, &m_Handle, 1, &numConfigs);
}

Configure::Configure(void *eglHandle)
{
	m_Handle = eglHandle;
}

bool Configure::IsNull() const
{
	return m_Handle == NULL;
}

int *Configure::GetAttributes() const
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	int *ret = NULL;
	EGLBoolean b = eglGetConfigAttrib(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), m_Handle, 0, ret);
	if(!b)
		NB_THROW_EXCEPTION("configure get attributes fail.");

	return ret;
}

void *Configure::GetEGLHandle() const
{
	return m_Handle;
}

int Configure::SystemRecommendMaxSupportCount()
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLint count = 0;
	EGLBoolean b = eglGetConfigs(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), NULL, 0, &count);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	return count;
}

Configure Configure::FromSystemRecommend(int index)
{
	int maxCount = SystemRecommendMaxSupportCount();
	if(index < 0 || index >= maxCount)
		NB_THROW_EXCEPTION("index out bound.");

	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLConfig *eglHandle = new EGLConfig[maxCount];
	int x = 0;
	EGLBoolean b = eglGetConfigs(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), eglHandle, maxCount, &x);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	Configure ret = Configure(eglHandle[index]);
	delete []eglHandle;
	return ret;
}
