#include "gles/Egl.h"
#include "gles/Display.h"
#include "core/Exception.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using nb::System::String;
using nb::gl::egl::Configure;
using nb::gl::egl::Display;
using nb::gl::egl::Surface;
using nb::gl::egl::Context;

nb::gl::egl::Display	m_Display;
nb::gl::egl::Configure	m_Configure;

nb::System::String nb::gl::egl::GetVersion()
{
	if(GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	std::string s = eglQueryString(GetCurrentDisplay().GetEGLHandle(), EGL_VERSION);
	return String::FromAscii(s.data());
}

nb::System::String nb::gl::egl::GetVendor()
{
	if(GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	std::string s = eglQueryString(GetCurrentDisplay().GetEGLHandle(), EGL_VENDOR);
	return String::FromAscii(s.data());
}

void nb::gl::egl::Initialize(const Display &display)
{
	m_Display = display;
}

const nb::gl::egl::Display &nb::gl::egl::GetCurrentDisplay()
{
	return m_Display;
}

void nb::gl::egl::SetConfigure(const Configure &configure)
{
	if(GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	m_Configure = configure;
}

const Configure &nb::gl::egl::GetCurrentConfigure()
{
	return m_Configure;
}

void nb::gl::egl::MakeCurrent(const Surface *onScreen, const Surface *offScreen, const Context *context)
{
	if(onScreen == NULL || offScreen == NULL || context == NULL)
		NB_THROW_EXCEPTION("null param");
	if(GetCurrentDisplay().IsNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLBoolean b = eglMakeCurrent(GetCurrentDisplay().GetEGLHandle(), onScreen->GetEGLHandle(), offScreen->GetEGLHandle(), context->GetEGLHandle());
	if(!b)
	{
		char info[100] = {0};
		sprintf(info, "Egl::SetCurrent fail. error code[%d]", eglGetError());
		NB_THROW_EXCEPTION(info);
	}
}

void nb::gl::egl::SwapBuffers(const Surface *surface)
{
	eglSwapBuffers(GetCurrentDisplay().GetEGLHandle(), surface->GetEGLHandle());
}
