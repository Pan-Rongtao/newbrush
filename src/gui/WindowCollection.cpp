#include "newbrush/gui/WindowCollection.h"

using namespace nb;

void WindowCollection::push(Window * w)
{
	if (m_windows.empty())
		m_mainWindow = w;
	m_windows.push_back(w);
}

void WindowCollection::erase(Window * w)
{
	auto iter = std::find(m_windows.begin(), m_windows.end(), w);
	if (iter != m_windows.end())
	{
		auto isMainWindow = *iter == m_mainWindow;
		m_windows.erase(iter);
		WindowClosed.invoke({ isMainWindow });
	}
}

std::vector<Window*>& WindowCollection::windows()
{
	return m_windows;
}

void WindowCollection::setMainWindow(Window * w)
{
	m_mainWindow = w;
}

Window * WindowCollection::mainWindow()
{
	return m_mainWindow;
}
