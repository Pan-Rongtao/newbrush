#include "EglMaster.h"
#include "gles/Window.h"
#include "gles/Context.h"
#include "gles/Surface.h"

using namespace nb::gl;

std::vector<Window *>& EglMaster::windows()
{
	static std::vector<Window *> g_windows;
	return g_windows;
}

std::vector<Context *>& EglMaster::contexts()
{
	static std::vector<Context *> g_contexs;
	return g_contexs;
}

std::vector<WindowSurface *>& EglMaster::windowSurfaces()
{
	static std::vector<WindowSurface *> g_windowSurfaces;
	return g_windowSurfaces;
}
