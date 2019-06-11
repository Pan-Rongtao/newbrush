#include "gles/Configure.h"
#include "gles/Egl.h"
#include "gles/Display.h"
#include <EGL/egl.h>

using namespace nb::gl;

Configure::Configure(const int *attributes)
	: m_handle(nullptr)
{
	if (!gl::getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	EGLint numConfigs(0);
	if(!eglChooseConfig(gl::getDisplay()->handle(), attributes, &m_handle, 1, &numConfigs))
		NB_THROW_EXCEPTION(std::runtime_error, "eglChooseConfig fail, eglGetError[%d].", eglGetError());
}

int *Configure::attributes() const
{
	int *ret = nullptr;
	if(!eglGetConfigAttrib(gl::getDisplay()->handle(), m_handle, 0, ret))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigAttrib, eglGetError[%d].", eglGetError());

	return ret;
}

void *Configure::handle() const
{
	return m_handle;
}

uint32_t Configure::systemRecommendMaxSupportCount()
{
	if (!gl::getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	EGLint count = 0;
	if(!eglGetConfigs(gl::getDisplay()->handle(), nullptr, 0, &count))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigs fail, eglGetError[%d].", eglGetError());

	return count;
}

Configure Configure::fromSystemRecommend(uint32_t index)
{
	if (!gl::getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	auto maxCount = systemRecommendMaxSupportCount();
	if(index >= maxCount)
		NB_THROW_EXCEPTION(std::out_of_range, "param index[%d] out of [%d, %d).", index, 0, maxCount);

	EGLConfig *eglHandle = new EGLConfig[maxCount];
	int count = 0;
	if(!eglGetConfigs(gl::getDisplay()->handle(), eglHandle, maxCount, &count))
		NB_THROW_EXCEPTION(std::runtime_error, "eglGetConfigs fail, eglGetError[%d].", eglGetError());

	Configure conf;
	conf.m_handle = eglHandle[index];
	delete []eglHandle;
	return conf;
}

Configure::Configure()
	: m_handle(nullptr)
{
}
