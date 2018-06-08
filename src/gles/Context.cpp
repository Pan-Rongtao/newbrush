#include "gles/Context.h"
#include <EGL/egl.h>
#include "gles/Egl.h"
#include "core/Exception.h"
#include "EglMaster.h"

using nb::gl::egl::Context;
using nb::gl::egl::Configure;

Context::Context(const Configure &configure)
{
	if(nb::gl::egl::GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLint contextAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
	m_Handle = eglCreateContext(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), configure.GetEGLHandle(), 0, contextAttr);

	nb::gl::egl::ContextMaster::Push(this);
}

Context::~Context()
{
	eglDestroyContext(nb::gl::egl::GetCurrentDisplay().GetEGLHandle(), m_Handle);
	nb::gl::egl::ContextMaster::Erease(this);
}

void *Context::GetEGLHandle() const
{
	return m_Handle;
}
