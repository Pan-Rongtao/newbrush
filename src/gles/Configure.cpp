#include "gles/Configure.h"
#include "gles/Egl.h"
#include "core/Exception.h"
#include <EGL/egl.h>

using namespace nb::core;
using namespace nb::gl;

Configure::Configure(std::shared_ptr<Display> display, int *attributes)
	: m_handle(nullptr)
	, m_display(nullptr)
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
	eglChooseConfig(nb::gl::getDisplay()->handle(), attribs, &m_handle, 1, &numConfigs);
	if (!display)
		throw ArgumentNullException("display", __FILE__, __LINE__);
	m_display = display;
}

bool Configure::isNull() const
{
	return m_handle == nullptr;
}

int *Configure::attributes() const
{
	int *ret = nullptr;
	EGLBoolean b = eglGetConfigAttrib(m_display->handle(), m_handle, 0, ret);
	if(!b)
		NB_THROW_EXCEPTION("configure get attributes fail.");

	return ret;
}

void *Configure::handle() const
{
	return m_handle;
}

int Configure::systemRecommendMaxSupportCount(std::shared_ptr<Display> display)
{
	if (!display)
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLint count = 0;
	EGLBoolean b = eglGetConfigs(display->handle(), nullptr, 0, &count);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	return count;
}

Configure Configure::fromSystemRecommend(std::shared_ptr<Display> display, int index)
{
	int maxCount = systemRecommendMaxSupportCount(display);
	if(index < 0 || index >= maxCount)
		NB_THROW_EXCEPTION("index out bound.");

	EGLConfig *eglHandle = new EGLConfig[maxCount];
	int x = 0;
	EGLBoolean b = eglGetConfigs(display->handle(), eglHandle, maxCount, &x);
	if(!b)
		NB_THROW_EXCEPTION("get configs fail.");

	Configure conf;
	conf.m_handle = eglHandle[index];
	conf.m_display = display;
	delete []eglHandle;
	return conf;
}

Configure::Configure()
	: m_handle(nullptr)
	, m_display(nullptr)
{
}
