#include "gles/Egl.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace nb::gl;

static std::shared_ptr<Camera>		g_camera			= std::make_shared<Camera>();
static std::shared_ptr<Projection>	g_projection		= std::make_shared<Projection>();
static std::shared_ptr<Context>		g_context			= nullptr;

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

void nb::gl::viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}
