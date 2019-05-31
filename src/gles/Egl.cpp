#include "gles/Egl.h"
#include "gles/Display.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace nb::gl;

static std::shared_ptr<Display> g_display = nullptr;
static std::shared_ptr<Configure> g_configure = nullptr;
static std::shared_ptr<Camera> g_camera = std::make_shared<Camera>();
static std::shared_ptr<Projection> g_projection = std::make_shared<Projection>();
static std::shared_ptr<Surface> g_onScreenSurface = nullptr;
static std::shared_ptr<Surface> g_offScreenSurface = nullptr;
static std::shared_ptr<Context> g_context = nullptr;

std::string nb::gl::getVersion()
{
	if (!getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	return eglQueryString(getDisplay()->handle(), EGL_VERSION);
}

std::string nb::gl::getVendor()
{
	if (!getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	return eglQueryString(getDisplay()->handle(), EGL_VENDOR);
}

void nb::gl::initialize(std::shared_ptr<Display> display)
{
	if (g_display)
		return;

	int major = 0, minor = 0;
	if (!eglInitialize(display->handle(), &major, &minor))
		NB_THROW_EXCEPTION(std::runtime_error, "eglInitialize fail, eglGetError[%d].", eglGetError());

	g_display = display;
}

std::shared_ptr<Display> nb::gl::getDisplay()
{
	return g_display;
}

void nb::gl::setConfigure(std::shared_ptr<Configure> configure)
{
	g_configure = configure;
}

std::shared_ptr<Configure> nb::gl::getConfigure()
{
	return g_configure;
}

void nb::gl::setCamera(std::shared_ptr<Camera> camera)
{
	g_camera = camera;
}

std::shared_ptr<Camera> nb::gl::getCamera()
{
	return g_camera;
}

void nb::gl::setProjection(std::shared_ptr<Projection> projection)
{
	g_projection = projection;
}

std::shared_ptr<Projection> nb::gl::getProjection()
{
	return g_projection;
}

void nb::gl::makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context)
{
	if (!getDisplay())
		NB_THROW_EXCEPTION(std::logic_error, "gl init needed, use nb::gl::initialize to init.");

	if(!eglMakeCurrent(getDisplay()->handle(), onScreen->handle(), offScreen->handle(), context->handle()))
		NB_THROW_EXCEPTION(std::runtime_error, "eglMakeCurrent fail, glGetError[%d]", glGetError());

	g_onScreenSurface = onScreen;
	g_offScreenSurface = offScreen;
	g_context = context;
}

std::shared_ptr<Surface> nb::gl::getOnScreenSurface()
{
	return g_onScreenSurface;
}

NB_API std::shared_ptr<Surface> nb::gl::getOffScreenSurface()
{
	return g_offScreenSurface;
}

std::shared_ptr<Context> nb::gl::getContext()
{
	return g_context;
}

void nb::gl::swapBuffers(const Surface *surface)
{
	eglSwapBuffers(getDisplay()->handle(), surface->handle());
}

void nb::gl::viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}
