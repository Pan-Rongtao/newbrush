#include "EglMaster.h"
#include "gles/Window.h"
#include "gles/Context.h"
#include "gles/Surface.h"
#include <vector>
#include <algorithm>

using nb::gl::egl::Window;
using nb::gl::egl::WindowMaster;
using nb::gl::egl::Context;
using nb::gl::egl::ContextMaster;
using nb::gl::egl::WindowSurface;
using nb::gl::egl::SurfacesMaster;

static std::vector<Window *> g_Windows;
void WindowMaster::Push(nb::gl::egl::Window *window)
{
	g_Windows.push_back(window);
}

void WindowMaster::Erease(Window *window)
{
	std::vector<Window *>::iterator iterFind = std::find(g_Windows.begin(), g_Windows.end(), window);
	if(iterFind != g_Windows.end())
	{
		g_Windows.erase(iterFind);
	}
}

int WindowMaster::GetCount()
{
	return (int)g_Windows.size();
}

Window *WindowMaster::At(int index)
{
	return (index >=0 && index < (int)g_Windows.size()) ? g_Windows[index] : NULL;
}

//////////////////////////////////
static std::vector<Context *> g_Contexs;
void ContextMaster::Push(Context *contex)
{
	g_Contexs.push_back(contex);
}

void ContextMaster::Erease(Context *contex)
{
	std::vector<Context *>::iterator iterFind = std::find(g_Contexs.begin(), g_Contexs.end(), contex);
	if(iterFind != g_Contexs.end())
	{
		g_Contexs.erase(iterFind);
	}
}

int ContextMaster::GetCount()
{
	return (int)g_Contexs.size();
}

Context *ContextMaster::At(int index)
{
	return (index >=0 && index < (int)g_Contexs.size()) ? g_Contexs[index] : NULL;
}

///////////////////////////////////
static std::vector<WindowSurface *> g_WindowSurfaces;
void SurfacesMaster::Push(WindowSurface *surface)
{
	g_WindowSurfaces.push_back(surface);
}

void SurfacesMaster::Erease(WindowSurface *surface)
{
	std::vector<WindowSurface *>::iterator iterFind = std::find(g_WindowSurfaces.begin(), g_WindowSurfaces.end(), surface);
	if(iterFind != g_WindowSurfaces.end())
	{
		g_WindowSurfaces.erase(iterFind);
	}
}

int SurfacesMaster::GetCount()
{
	return (int)g_WindowSurfaces.size();
}

WindowSurface *SurfacesMaster::At(int index)
{
	return (index >=0 && index < (int)g_WindowSurfaces.size()) ? g_WindowSurfaces[index] : NULL;
}
