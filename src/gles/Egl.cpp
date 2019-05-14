#include "gles/Egl.h"
#include "gles/Display.h"
#include "core/Exception.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace nb::gl;

nb::gl::Display	m_Display;
nb::gl::Configure	m_Configure;

std::string nb::gl::getVersion()
{
	if(getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	return eglQueryString(getCurrentDisplay().handle(), EGL_VERSION);
}

std::string nb::gl::getVendor()
{
	if(getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	return eglQueryString(getCurrentDisplay().handle(), EGL_VENDOR);
}

void nb::gl::initialize(const Display &display)
{
	m_Display = display;
}

const nb::gl::Display &nb::gl::getCurrentDisplay()
{
	return m_Display;
}

void nb::gl::setConfigure(const Configure &configure)
{
	if(getCurrentDisplay().isNull())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	m_Configure = configure;
}

const Configure &nb::gl::getCurrentConfigure()
{
	return m_Configure;
}

void nb::gl::makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context)
{
	if(onScreen == nullptr || offScreen == nullptr || context == nullptr)	NB_THROW_EXCEPTION("null param");
	if(getCurrentDisplay().isNull())	NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	EGLBoolean b = eglMakeCurrent(getCurrentDisplay().handle(), onScreen->handle(), offScreen->handle(), context->handle());
	if(!b)
		NB_THROW_EXCEPTION("eglMakeCurrent fail");
}

void nb::gl::swapBuffers(const Surface *surface)
{
	eglSwapBuffers(getCurrentDisplay().handle(), surface->handle());
}

void nb::gl::Viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}
