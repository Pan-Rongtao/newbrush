#include "newbrush/gui/WindowCollection.h"

using namespace nb;

void nb::WindowCollection::push(gui::Window * w)
{
	if (m_windows.empty())
		m_mainWindow = w;
	m_windows.push_back(w);
}

void nb::WindowCollection::erase(gui::Window * w)
{
	auto iter = std::find(m_windows.begin(), m_windows.end(), w);
	if (iter != m_windows.end())
	{
		auto isMainWindow = *iter == m_mainWindow;
		m_windows.erase(iter);
		WindowClosed.invoke({ isMainWindow });
	}
}

std::vector<gui::Window*>& nb::WindowCollection::windows()
{
	return m_windows;
}

void WindowCollection::setMainWindow(gui::Window * w)
{
	m_mainWindow = w;
}

gui::Window * WindowCollection::mainWindow()
{
	return m_mainWindow;
}
