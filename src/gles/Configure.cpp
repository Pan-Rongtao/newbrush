#include "gles/Configure.h"
#include "gles/Egl.h"
#include "gles/Display.h"
#include <EGL/egl.h>

using namespace nb::core;
using namespace nb::gl;

Configure::Configure(std::shared_ptr<Display> display, const int *attributes)
	: m_handle(nullptr)
	, m_display(nullptr)
{
	if (!display)
		NB_THROW_EXCEPTION(std::invalid_argument, "display uses null as param.");

	EGLint numConfigs(0);
	if(!eglChooseConfig(display->handle(), attributes, &m_handle, 1, &numConfigs))
		NB_THROW_EXCEPTION(std::runtime_error, "eglChooseConfig fail, eglGetError[%d].", eglGetError());
	m_display = display;
}

int *Configure::attributes() const
{
	int *ret = nullptr;
	if(!eglGetConfigAttrib(m_display->handle(), m_handle, 0, ret))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigAttrib, eglGetError[%d].", eglGetError());

	return ret;
}

void *Configure::handle() const
{
	return m_handle;
}

uint32_t Configure::systemRecommendMaxSupportCount(std::shared_ptr<Display> display)
{
	if (!display)
		NB_THROW_EXCEPTION(std::invalid_argument, "display uses null as param.");

	EGLint count = 0;
	if(!eglGetConfigs(display->handle(), nullptr, 0, &count))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigs fail, eglGetError[%d].", eglGetError());

	return count;
}

Configure Configure::fromSystemRecommend(std::shared_ptr<Display> display, uint32_t index)
{
	if (!display)
		NB_THROW_EXCEPTION(std::invalid_argument, "display uses null as param.");

	auto maxCount = systemRecommendMaxSupportCount(display);
	if(index >= maxCount)
		NB_THROW_EXCEPTION(std::out_of_range, "param index[%d] out of [%d, %d).", index, 0, maxCount);

	EGLConfig *eglHandle = new EGLConfig[maxCount];
	int count = 0;
	if(!eglGetConfigs(display->handle(), eglHandle, maxCount, &count))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigs fail, eglGetError[%d].", eglGetError());

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
