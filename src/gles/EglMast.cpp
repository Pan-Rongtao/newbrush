#include "EglMaster.h"
#include "gles/Window.h"
#include "gles/Context.h"
#include "gles/Surface.h"
#include <vector>
#include <algorithm>

using namespace nb::gl;

static std::vector<Window *> g_Windows;
void WindowMaster::push(Window *window)
{
	g_Windows.push_back(window);
}

void WindowMaster::erease(Window *window)
{
	std::vector<Window *>::iterator iterFind = std::find(g_Windows.begin(), g_Windows.end(), window);
	if(iterFind != g_Windows.end())
	{
		g_Windows.erase(iterFind);
	}
}

int WindowMaster::count()
{
	return (int)g_Windows.size();
}

Window *WindowMaster::at(int index)
{
	return (index >=0 && index < (int)g_Windows.size()) ? g_Windows[index] : nullptr;
}

//////////////////////////////////
static std::vector<Context *> g_Contexs;
void ContextMaster::push(Context *contex)
{
	g_Contexs.push_back(contex);
}

void ContextMaster::erease(Context *contex)
{
	std::vector<Context *>::iterator iterFind = std::find(g_Contexs.begin(), g_Contexs.end(), contex);
	if(iterFind != g_Contexs.end())
	{
		g_Contexs.erase(iterFind);
	}
}

int ContextMaster::count()
{
	return (int)g_Contexs.size();
}

Context *ContextMaster::at(int index)
{
	return (index >=0 && index < (int)g_Contexs.size()) ? g_Contexs[index] : nullptr;
}

///////////////////////////////////
static std::vector<WindowSurface *> g_WindowSurfaces;
void SurfacesMaster::push(WindowSurface *surface)
{
	g_WindowSurfaces.push_back(surface);
}

void SurfacesMaster::erease(WindowSurface *surface)
{
	std::vector<WindowSurface *>::iterator iterFind = std::find(g_WindowSurfaces.begin(), g_WindowSurfaces.end(), surface);
	if(iterFind != g_WindowSurfaces.end())
	{
		g_WindowSurfaces.erase(iterFind);
	}
}

int SurfacesMaster::count()
{
	return (int)g_WindowSurfaces.size();
}

WindowSurface *SurfacesMaster::at(int index)
{
	return (index >=0 && index < (int)g_WindowSurfaces.size()) ? g_WindowSurfaces[index] : nullptr;
}
