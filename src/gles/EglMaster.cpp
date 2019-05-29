#include "EglMaster.h"
#include "gles/Window.h"
#include "gles/Context.h"
#include "gles/Surface.h"

using namespace nb::gl;

static std::vector<Window *> g_windows;
static std::vector<Context *> g_contexs;
static std::vector<WindowSurface *> g_windowSurfaces;

std::vector<Window *>& EglMaster::windows()
{
	return g_windows;
}

std::vector<Context *>& EglMaster::contexts()
{
	return g_contexs;
}

std::vector<WindowSurface *>& EglMaster::windowSurfaces()
{
	return g_windowSurfaces;
}
