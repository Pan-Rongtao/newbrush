#include "WindowManager.h"
#include <vector>
#include <algorithm>

using namespace nb::gui;

static std::vector<Window *> g_Windows;
void WindowManager::Push(Window *window)
{
	g_Windows.push_back(window);
}

void WindowManager::Erease(Window *window)
{
	std::vector<Window *>::iterator iterFind = std::find(g_Windows.begin(), g_Windows.end(), window);
	if(iterFind != g_Windows.end())
	{
		g_Windows.erase(iterFind);
	}
}

int WindowManager::GetCount()
{
	return (int)g_Windows.size();
}

Window *WindowManager::At(int index)
{
	return (index >=0 && index < (int)g_Windows.size()) ? g_Windows[index] : NULL;
}